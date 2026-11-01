/* Stage-2 native technical slice. All rectangles below are diagnostic artwork. */
#include <Quickdraw.h>
#include <Windows.h>
#include <Menus.h>
#include <Fonts.h>
#include <TextEdit.h>
#include <Dialogs.h>
#include <Events.h>
#include <Memory.h>
#include <string.h>
#include "engine.h"
#include "font_mac.h"
#include "content.h"

enum { BOX_NONE, BOX_DESK, BOX_WORKSHOP, BOX_CHEST, BOX_FLOREK, BOX_FISHER,
       BOX_SEW, BOX_JOURNAL, BOX_HINT, BOX_HELP, BOX_HISTORY, BOX_MESSAGE };
typedef struct { short l,t,r,b; enum ProchTarget target; const char *name; } Hotspot;
static const Hotspot yard[] = {{12,65,106,188,FLOREK,T_FLOREK_QUOTE},
    {128,35,235,178,TARGET_NONE,T_GATE},{252,45,348,192,BIKE_TOPIC,T_BIKE}};
static const Hotspot room[] = {{10,3,170,24,ROOM_DOOR,T_DOOR},
    {10,28,170,104,DESK,T_DESK},{190,28,350,104,ROOM_WINDOW,T_WINDOW},
    {10,119,170,199,BED,T_BED},{190,119,350,199,TARGET_NONE,T_LACE}};
static const Hotspot hall[] = {{12,65,106,188,ROOM_DOOR,T_DOOR},
    {128,35,235,178,ROOM_WINDOW,T_WINDOW},{252,45,348,192,TARGET_NONE,T_SHADOW}};
static const Hotspot workshop[] = {{10,28,170,104,TABLE,T_TABLE},
    {190,28,350,104,TARGET_NONE,T_ROPE},{10,119,170,199,TARGET_NONE,T_HOOK},
    {190,119,350,199,TARGET_NONE,T_LAMP}};
static const Hotspot vats[] = {{12,65,106,188,TARGET_NONE,T_VAT},
    {128,35,235,178,TARGET_NONE,T_PIPE},{252,45,348,192,TARGET_NONE,T_TRACES}};
static const Hotspot hut[] = {{12,65,106,188,FISHER,T_FISHER},
    {128,35,235,178,TABLE,T_TABLE},{252,45,348,192,CHEST,T_CHEST}};
static const char *const verbs[] = {T_LOOK,T_OPEN,T_CLOSE,T_USE,T_TALK,T_GO,T_HIT,T_EAT};
static WindowPtr window;
static ProchState state;
static enum ProchVerb verb;
static unsigned char selected, box, running = 1, pressed, pressed_from_box;
static short history_page;
static const char *hero_history[HERO_COUNT][32];
static unsigned char hero_history_count[HERO_COUNT];
#define history (hero_history[state.active])
#define history_count (hero_history_count[state.active])
static Point down_point;
static const char *hint;
static const char *detail_start, *detail_current, *detail_next;

static void rect(Rect *r, short x, short y, short w, short h) { SetRect(r,x,y,x+w,y+h); }
static int inside(Point p,short x,short y,short w,short h)
{ return p.h>=x && p.h<x+w && p.v>=y && p.v<y+h; }
static void invalidate(void) { SetPort(window); InvalRect(&window->portRect); }
static void invalidate_area(short x,short y,short w,short h)
{ Rect r;rect(&r,x,y,w,h);InvalRect(&r); }
static void damage(const ProchState *previous,unsigned char old_box,enum ProchVerb old_verb,unsigned char old_selected)
{
    unsigned hero=state.active;
    int items_changed=memcmp(previous->item_location,state.item_location,sizeof(state.item_location))!=0;
    if(previous->active!=hero || previous->hero[hero].location!=state.hero[hero].location) {
        invalidate();return;
    }
    /* Input feedback and selection do not invalidate the whole screen. */
    invalidate_area(4,253,504,43);
    if(old_box || box)invalidate_area(20,52,472,197);
    if(old_verb!=verb)invalidate_area(4,300,504,40);
    if(old_selected!=selected || items_changed || previous->hero[hero].tab!=state.hero[hero].tab ||
       previous->quest[8].status!=state.quest[8].status)invalidate_area(372,129,136,120);
    if(items_changed || previous->q12_bits!=state.q12_bits)invalidate_area(6,39,360,208);
    if(previous->disguise!=state.disguise)invalidate_area(372,23,136,102);
}
static void narrate(const char *s)
{
    if (!s || !*s) return;
    if (history_count && history[history_count-1] == s) return;
    if (history_count == 32) { memmove(history,history+1,31*sizeof(history[0])); --history_count; }
    history[history_count++] = s;
}
static void respond(enum ProchReply r) { narrate(reply_texts[r]); }
static void open_box(unsigned char value) { box=value; state.switch_locked=1; }
static void close_box(void) { box=0; state.switch_locked=0; }

static const char *layout(short x,short baseline,short columns,short lines,const char *s,int paint)
{
    char line[80];
    while (*s && lines-- > 0) {
        short n=0,last_space=-1,i;
        while (s[n] && s[n]!='\n' && n<columns) { if(s[n]==' ')last_space=n; ++n; }
        if (s[n] && s[n]!='\n' && last_space>0) n=last_space;
        for(i=0;i<n;++i)line[i]=s[i];
        line[n]=0;
        if(paint)proch_text(x,baseline,line);
        baseline+=12;s+=n;
        while(*s==' ' || *s=='\n')++s;
    }
    return s;
}
static const char *wrapped(short x,short y,short cols,short lines,const char *s)
{ return layout(x,y,cols,lines,s,1); }
static void message(const char *s)
{ detail_start=detail_current=s;detail_next=s;open_box(BOX_MESSAGE); }

static void button(short x,short y,short w,short h,const char *label,int chosen)
{
    Rect r;
    rect(&r,x,y,w,h); FrameRect(&r); proch_text(x+4,y+12,label);
    if(chosen)InvertRect(&r);
}

static unsigned scene_hotspots(const Hotspot **spots)
{
    switch(state.hero[state.active].location) {
        case 11:*spots=yard;return 3; case 12:*spots=hall;return 3;
        case 13:*spots=room;return 5; case 14:*spots=vats;return 3;
        case 15:*spots=workshop;return 4; case 33:*spots=hut;return 3;
    }
    *spots=0;return 0;
}
static int visible_spot(unsigned index)
{
    return !(state.hero[state.active].location==13 && index==4 && state.item_location[19]!=13);
}
static const Hotspot *hit_spot(Point p)
{
    const Hotspot *spots;
    unsigned i,n=scene_hotspots(&spots);
    p.h-=6;p.v-=39;
    for(i=0;i<n;++i)
        if(visible_spot(i) && inside(p,spots[i].l,spots[i].t,spots[i].r-spots[i].l,spots[i].b-spots[i].t))return &spots[i];
    return 0;
}
static unsigned exits(unsigned char *dest)
{
    switch(state.hero[state.active].location) {
        case 11: dest[0]=12;
            if(state.quest[8].status==2){dest[1]=14;dest[2]=15;return 3;}return 1;
        case 12: dest[0]=11;dest[1]=13;return 2;
        case 13: dest[0]=12;return 1;
        case 14: dest[0]=11;dest[1]=15;return 2;
        case 15: dest[0]=11;dest[1]=14;return 2;
    }
    return 0;
}
static void icon(unsigned item,short x,short y,int chosen)
{
    char label[4]={'I',(char)('0'+item/10),(char)('0'+item%10),0};
    button(x,y,24,24,label,chosen);
}
static unsigned inventory(unsigned char *items)
{
    unsigned i,n=0;
    for(i=1;i<=ITEM_COUNT;++i)if(proch_has(&state,i))items[n++]=i;
    return n;
}
static unsigned container_items(unsigned char *items)
{
    unsigned i,n=0;
    for(i=1;i<=ITEM_COUNT;++i)
        if((box==BOX_DESK && (i==12 || i==13 || i==14)) ||
           (box==BOX_WORKSHOP && i>=16 && i<=18) || (box==BOX_CHEST && (i==24 || i==25)))
            if(proch_can_take(&state,i))items[n++]=i;
    return n;
}
static unsigned hit_item(Point p,int from_box)
{
    unsigned char items[ITEM_COUNT];
    unsigned i,n;
    if(from_box) {
        if(box!=BOX_DESK && box!=BOX_WORKSHOP && box!=BOX_CHEST)return 0;
        n=container_items(items);
        for(i=0;i<n;++i)if(inside(p,42+(short)i*110,116,24,24))return items[i];
    } else if(!state.hero[state.active].tab) {
        n=inventory(items);
        for(i=0;i<n && i<9;++i)
            if(inside(p,378+(i%3)*36,153+(i/3)*36,24,24))return items[i];
    }
    return 0;
}

static void modal(void)
{
    Rect r;
    unsigned i,n;
    unsigned char items[ITEM_COUNT];
    const char *title=T_CONTENTS;
    rect(&r,20,52,472,197);EraseRect(&r);FrameRect(&r);
    if(box==BOX_FLOREK)title="Florek";
    if(box==BOX_FISHER)title=T_FISHER;
    if(box==BOX_SEW)title=T_SEW_TITLE;
    if(box==BOX_JOURNAL)title=T_JOURNAL;
    if(box==BOX_HINT)title=T_HINT;
    if(box==BOX_HELP)title=T_HELP_TITLE;
    if(box==BOX_HISTORY)title=T_HISTORY;
    if(box==BOX_MESSAGE)title=T_HISTORY;
    proch_text(28,68,title);
    if(box==BOX_FLOREK || box==BOX_FISHER)button(328,226,154,18,T_END_TALK,0);
    else button(406,226,76,18,T_END_WINDOW,0);
    switch(box) {
        case BOX_DESK:case BOX_WORKSHOP:case BOX_CHEST:
            n=container_items(items);
            for(i=0;i<n;++i){ icon(items[i],42+i*110,116,0);wrapped(42+i*110,154,14,3,item_names[items[i]]); }
            if(box==BOX_DESK)button(30,82,280,20,state.drawer_open?T_CLOSE:T_DRAWER,0);
            wrapped(30,202,63,2,T_TAKE_HELP);break;
        case BOX_FLOREK:
            button(30,82,420,20,T_ROOM_TOPIC,0);button(30,108,420,20,T_BIKE_TOPIC,0);
            wrapped(30,154,62,4,T_FLOREK_QUOTE);break;
        case BOX_FISHER:
            button(30,82,420,20,T_FISHER_TOPIC,0);wrapped(30,124,62,5,T_FISHER_QUOTE);break;
        case BOX_SEW:
            button(30,82,420,20,T_SIMPLE_CUT,state.cut);
            button(30,108,420,20,T_MARK_LENGTH,state.measured);
            button(30,134,420,20,T_SEW,state.item_location[26]!=0);break;
        case BOX_JOURNAL:
            n=0;proch_text(300,68,state.active==HERO_M?T_M_NAME:T_K_NAME);
            for(i=0;i<QUEST_COUNT;++i)
                if(state.hero[state.active].journal[i/32]&((uint32_t)1<<(i%32))) {
                    proch_text(30,90+24*n,T_COMPLETE);proch_text(114,90+24*n,quest_names[i+1]);++n;
                }
            if(!n)wrapped(30,94,62,4,T_NO_JOURNAL);
            break;
        case BOX_HINT:wrapped(30,94,62,9,hint);break;
        case BOX_HELP:wrapped(30,94,62,10,T_HELP);break;
        case BOX_HISTORY:
            n=0;
            for(i=history_page;i<history_count && n<4;++i,++n)wrapped(30,90+n*30,62,2,history[i]);
            button(30,226,100,18,T_PREVIOUS,0);button(140,226,100,18,T_NEXT,0);break;
        case BOX_MESSAGE:
            detail_next=wrapped(30,90,62,10,detail_current);
            button(30,226,100,18,T_PREVIOUS,0);button(140,226,100,18,T_NEXT,0);break;
    }
}

static void draw(void)
{
    Rect r;
    const Hotspot *spots;
    unsigned i,n;
    unsigned char items[ITEM_COUNT],dest[8];
    SetPort(window);EraseRect(&window->portRect);
    rect(&r,4,23,364,226);FrameRect(&r);
    proch_text(8,34,scene_names[state.hero[state.active].location]);
    rect(&r,6,39,360,208);FrameRect(&r);
    n=scene_hotspots(&spots);
    for(i=0;i<n;++i)if(visible_spot(i)) {
        rect(&r,6+spots[i].l,39+spots[i].t,spots[i].r-spots[i].l,spots[i].b-spots[i].t);FrameRect(&r);
        if(spots[i].target==FLOREK)proch_text(r.left+3,r.top+12,"Florek");
        else wrapped(r.left+3,r.top+12,(r.right-r.left-6)/7,3,spots[i].name);
    }
    proch_text(12,151,T_TEST_ART);
    rect(&r,372,23,136,102);FrameRect(&r);
    rect(&r,378,42,48,48);FrameRect(&r);
    proch_text(397,70,state.active==HERO_M?"M":"K");
    proch_text(432,52,state.active==HERO_M?T_M_NAME:T_K_NAME);
    proch_text(432,66,state.active==HERO_M?T_M_SURNAME:T_K_SURNAME);
    if(state.active==HERO_K && state.disguise)proch_text(432,82,"Suknia");
    button(378,96,124,20,T_SWITCH,0);
    rect(&r,372,129,136,120);FrameRect(&r);
    button(373,130,67,18,T_INVENTORY,!state.hero[state.active].tab);
    button(440,130,67,18,T_EXITS,state.hero[state.active].tab);
    if(!state.hero[state.active].tab) {
        n=inventory(items);
        for(i=0;i<n && i<9;++i)icon(items[i],378+(i%3)*36,153+(i/3)*36,selected==items[i]);
    } else {
        n=exits(dest);
        for(i=0;i<n;++i) {
            rect(&r,376,150+i*32,128,30);FrameRect(&r);
            wrapped(r.left+3,r.top+12,17,2,scene_names[dest[i]]);
        }
        if(!n)wrapped(378,163,17,6,T_NO_EXITS);
    }
    rect(&r,4,253,504,43);FrameRect(&r);
    if(history_count)wrapped(9,266,70,3,history[history_count-1]);
    for(i=0;i<8;++i)button(4+(i%4)*128,300+(i/4)*22,120,18,verbs[i],verb==i);
    if(box)modal();
}

static void action(enum ProchVerb v,enum ProchTarget t,unsigned item)
{ respond(proch_action(&state,v,t,item)); }
static void switch_hero(void)
{
    if(box){narrate(T_CLOSE_FIRST);return;}
    selected=0;respond(proch_switch(&state));narrate(scene_names[state.hero[state.active].location]);
}
static void hotspot(const Hotspot *spot)
{
    unsigned loc=state.hero[state.active].location;
    if(!spot){narrate(reply_texts[REPLY_NO_EFFECT]);return;}
    if(loc==13 && spot==room+4) {
        if(verb==LOOK)narrate(reply_texts[REPLY_LACE]);
        else action(TAKE,TARGET_NONE,19);
    } else if(spot->target==DESK && loc==13) {
        if(verb==USE && selected)action(USE,DRAWER,selected);
        else if(verb==OPEN)open_box(BOX_DESK);
        else if(verb==CLOSE)action(CLOSE,DRAWER,0);
        else narrate(T_DESK);
    } else if(spot->target==TABLE && loc==15 && verb==OPEN)open_box(BOX_WORKSHOP);
    else if(spot->target==CHEST && verb==OPEN) {
        action(OPEN,CHEST,0);if(state.chest_open)open_box(BOX_CHEST);
    } else if(spot->target==TABLE && loc==33 && verb==USE && !selected)open_box(BOX_SEW);
    else if(spot->target==FLOREK && verb==TALK)open_box(BOX_FLOREK);
    else if(spot->target==FISHER && verb==TALK)open_box(BOX_FISHER);
    else action(verb,spot->target,verb==USE?selected:0);
    if(verb==USE)selected=0;
}
static void modal_click(Point p)
{
    if((box==BOX_FLOREK || box==BOX_FISHER) ? inside(p,328,226,154,18) : inside(p,406,226,76,18)) {
        close_box();return;
    }
    switch(box) {
        case BOX_DESK:
            if(inside(p,30,82,280,20)) {
                if(verb==USE && selected){action(USE,DRAWER,selected);selected=0;}
                else action(state.drawer_open?CLOSE:OPEN,DRAWER,0);
            }break;
        case BOX_FLOREK:
            if(inside(p,30,82,420,20)){action(TALK,ROOM_TOPIC,0);close_box();}
            else if(inside(p,30,108,420,20)){action(TALK,BIKE_TOPIC,0);close_box();}
            break;
        case BOX_FISHER:
            if(inside(p,30,82,420,20)){action(TALK,FISHER,0);close_box();}break;
        case BOX_SEW:
            if(inside(p,30,82,420,20))action(USE,SIMPLE_CUT,0);
            if(inside(p,30,108,420,20))action(USE,MARK_LENGTH,0);
            if(inside(p,30,134,420,20))action(USE,SEW,0);
            break;
        case BOX_HISTORY:
            if(inside(p,30,226,100,18))history_page=history_page>=4?history_page-4:0;
            if(inside(p,140,226,100,18) && history_page+4<history_count)history_page+=4;
            if(inside(p,30,78,440,120)) {
                unsigned index=history_page+(p.v-78)/30;
                if(index<history_count)message(history[index]);
            }
            break;
        case BOX_MESSAGE:
            if(inside(p,140,226,100,18) && *detail_next)detail_current=detail_next;
            if(inside(p,30,226,100,18) && detail_current!=detail_start) {
                const char *previous=detail_start,*scan=detail_start;
                while(scan<detail_current && *scan) {
                    previous=scan;scan=layout(0,0,62,10,scan,0);
                }
                detail_current=previous;
            }
            break;
    }
}
static void click(Point p)
{
    unsigned i,n;
    unsigned char dest[8];
    if(box){modal_click(p);return;}
    if(inside(p,378,96,124,20)){switch_hero();return;}
    if(inside(p,373,130,67,18)){state.hero[state.active].tab=0;return;}
    if(inside(p,440,130,67,18)){state.hero[state.active].tab=1;return;}
    if(inside(p,4,253,504,43)){history_page=history_count>4?history_count-4:0;open_box(BOX_HISTORY);return;}
    for(i=0;i<8;++i)if(inside(p,4+(i%4)*128,300+(i/4)*22,120,18)) {
        verb=(enum ProchVerb)i;selected=0;return;
    }
    if(state.hero[state.active].tab) {
        n=exits(dest);
        for(i=0;i<n;++i)if(inside(p,376,150+i*32,128,30)) {
            respond(proch_move(&state,dest[i]));selected=0;
            narrate(scene_names[state.hero[state.active].location]);return;
        }
    }
    if(inside(p,378,42,48,48) && selected){action(USE,PORTRAIT,selected);selected=0;return;}
    if(inside(p,6,39,360,208))hotspot(hit_spot(p));
}
static void mouse_down(Point global)
{
    SetPort(window);GlobalToLocal(&global);down_point=global;
    pressed_from_box=box!=0;pressed=hit_item(global,pressed_from_box);
}
static void mouse_up(Point global)
{
    ProchState previous_state=state;
    unsigned char old_box=box,old_selected=selected;
    enum ProchVerb old_verb=verb;
    SetPort(window);GlobalToLocal(&global);
    if(pressed) {
        if(pressed_from_box) {
            if(inside(global,372,129,136,120) || hit_item(global,1)==pressed) {
                if(pressed==14 && !inside(global,372,129,136,120))action(LOOK,BIBLE,0);
                else { action(TAKE,TARGET_NONE,pressed); narrate(item_names[pressed]); }
            }
        } else if(inside(global,6,39,360,208) &&
                  (global.h!=down_point.h || global.v!=down_point.v)) {
            selected=pressed;enum ProchVerb previous=verb;verb=USE;hotspot(hit_spot(global));verb=previous;
        } else if(inside(global,378,42,48,48))action(USE,PORTRAIT,pressed);
        else if(verb==USE){selected=pressed;narrate(item_prompts[pressed]);}
        else if(pressed==14)action(LOOK,BIBLE,0);
        else narrate(item_descriptions[pressed]);
        pressed=0;
    } else click(global);
    damage(&previous_state,old_box,old_verb,old_selected);
}
static void menu_command(long value)
{
    ProchState previous_state=state;
    unsigned char old_box=box,old_selected=selected;
    enum ProchVerb old_verb=verb;
    short menu=value>>16,item=value&0xffff;
    if(menu==128 && item==1) {
        close_box();selected=0;verb=LOOK;memset(hero_history_count,0,sizeof(hero_history_count));
        proch_demo_init(&state);narrate(T_START);
    }
    if(menu==128 && item==6)running=0;
    if(menu==129 && item==1)open_box(BOX_JOURNAL);
    if(menu==129 && item==2) {
        unsigned q=state.active==HERO_K?21:(state.quest[8].status==2?12:9);
        unsigned level=state.quest[q-1].hint_level;
        hint=state.quest[q-1].status==2?T_NO_HINT:quest_hints[q][level];
        if(level<2)++state.quest[q-1].hint_level;
        open_box(BOX_HINT);
    }
    if(menu==130 && item==1)open_box(BOX_HELP);
    HiliteMenu(0);damage(&previous_state,old_box,old_verb,old_selected);
}
int main(void)
{
    Rect bounds;
    MenuHandle m;
    MaxApplZone();InitGraf(&qd.thePort);InitFonts();InitWindows();InitMenus();TEInit();InitDialogs(NULL);InitCursor();
    m=NewMenu(128,(ConstStringPtr)"\pPlik");
    AppendMenu(m,(ConstStringPtr)"\pNowa demonstracja;Wczytaj/O;Zapisz/S;Zapisz jako;-;Wyjscie/Q");
    DisableItem(m,2);DisableItem(m,3);DisableItem(m,4);InsertMenu(m,0);
    m=NewMenu(129,(ConstStringPtr)"\pGra");AppendMenu(m,(ConstStringPtr)"\pDziennik/J;Podpowiedz/H");InsertMenu(m,0);
    m=NewMenu(130,(ConstStringPtr)"\pPomoc");AppendMenu(m,(ConstStringPtr)"\pSterowanie");InsertMenu(m,0);DrawMenuBar();
    SetRect(&bounds,0,20,512,342);
    window=NewWindow(NULL,&bounds,(ConstStringPtr)"\pPROCH",true,plainDBox,(WindowPtr)-1L,false,0);
    if(!window)return 1;
    SetPort(window);SetOrigin(0,20);proch_demo_init(&state);narrate(T_START);invalidate();
    while(running) {
        EventRecord e;WindowPtr hit;
        if(!WaitNextEvent(everyEvent,&e,6,NULL))continue;
        switch(e.what) {
            case updateEvt:if((WindowPtr)e.message==window){BeginUpdate(window);draw();EndUpdate(window);}break;
            case mouseDown:
                switch(FindWindow(e.where,&hit)) {
                    case inMenuBar:menu_command(MenuSelect(e.where));break;
                    case inContent:if(hit==window){SelectWindow(window);mouse_down(e.where);}break;
                }break;
            case mouseUp:mouse_up(e.where);break;
            case keyDown:
                if(e.modifiers&cmdKey)menu_command(MenuKey(e.message&charCodeMask));
                else {
                    ProchState previous_state=state;
                    unsigned char old_box=box,old_selected=selected;
                    enum ProchVerb old_verb=verb;
                    if((e.message&charCodeMask)==9)switch_hero();
                    else if((e.message&charCodeMask)==27){close_box();selected=0;pressed=0;}
                    damage(&previous_state,old_box,old_verb,old_selected);
                }
                break;
        }
    }
    DisposeWindow(window);return 0;
}
