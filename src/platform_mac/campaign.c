/* Native campaign UI. Rectangles are explicitly marked stage-3 test artwork. */
#include <Quickdraw.h>
#include <Windows.h>
#include <Menus.h>
#include <Fonts.h>
#include <TextEdit.h>
#include <Dialogs.h>
#include <Events.h>
#include <Memory.h>
#include <string.h>
#include "campaign/rules.h"
#include "campaign_data.h"
#include "font_mac.h"

enum { BOX_NONE,BOX_DIALOG,BOX_CONTAINER,BOX_DOCUMENT,BOX_JOURNAL,BOX_HINT,BOX_HISTORY };
typedef struct { uint16_t target,text;short x,w; } Extra;
static WindowPtr window;
static PrGame game;
static PrState previous;
static unsigned char running=1,verb=PR_LOOK,selected,box,pressed,pressed_in_box;
static unsigned char history_count[2],page;
static uint16_t modal_target;
static const char *history[2][64],*document_start,*document_current,*document_next;
static Point down_point;
#define S (game.current)
#define HERO (S.hero[S.active])
#define T(name) pr_texts[PR_TEXT_##name]

static void rect(Rect *r,short x,short y,short w,short h) {SetRect(r,x,y,x+w,y+h);}
static int inside(Point p,short x,short y,short w,short h)
{return p.h>=x && p.h<x+w && p.v>=y && p.v<y+h;}
static void invalidate(void) {SetPort(window);InvalRect(&window->portRect);}
static void area(short x,short y,short w,short h) {Rect r;rect(&r,x,y,w,h);InvalRect(&r);}
static void damage(unsigned old_box,unsigned old_verb,unsigned old_selected)
{
    if(previous.active!=S.active || previous.hero[S.active].location!=HERO.location) {invalidate();return;}
    area(4,253,504,43);
    if(old_box || box)area(20,52,472,197);
    if(old_verb!=verb)area(4,300,504,40);
    if(old_selected!=selected || memcmp(&previous.world,&S.world,sizeof(S.world)) ||
       memcmp(&previous.hero[S.active],&HERO,sizeof(HERO)) ||
       memcmp(previous.quest,S.quest,sizeof(S.quest))) {
        area(372,129,136,120);area(6,39,360,208);
    }
}
static const char *layout(short x,short y,short cols,short lines,const char *s,int paint)
{
    char line[80];
    while(s && *s && lines-->0) {
        short n=0,last=-1,i;
        while(s[n] && s[n]!='\n' && n<cols) {if(s[n]==' ')last=n;++n;}
        if(s[n] && s[n]!='\n' && last>0)n=last;
        for(i=0;i<n;++i)line[i]=s[i];
        line[n]=0;
        if(paint)proch_text(x,y,line);
        s+=n;while(*s==' ' || *s=='\n')++s;y+=12;
    }
    return s;
}
static void wrapped(short x,short y,short cols,short lines,const char *s) {layout(x,y,cols,lines,s,1);}
static void button(short x,short y,short w,short h,const char *label,int chosen)
{Rect r;rect(&r,x,y,w,h);FrameRect(&r);proch_text(x+4,y+12,label);if(chosen)InvertRect(&r);}
static void narrate(const char *s)
{
    unsigned h=S.active,n=history_count[h];
    if(!s || !*s || (n && history[h][n-1]==s))return;
    if(n==64) {memmove(history[h],history[h]+1,63*sizeof(history[h][0]));--n;}
    history[h][n++]=s;history_count[h]=n;
}
static void close_box(void) {box=BOX_NONE;S.locks&=~PR_MODAL;pressed=0;}
static void open_box(unsigned kind,unsigned target)
{box=kind;modal_target=target;page=0;S.locks|=PR_MODAL;}
static void document(const char *s)
{document_start=document_current=document_next=s;open_box(BOX_DOCUMENT,0);}
static void feedback(PrFeedback f)
{
    narrate(pr_texts[f.text]);
    if(f.result!=PR_OK)return;
    if(f.presentation==PR_DIALOG)open_box(BOX_DIALOG,f.target);
    else if(f.presentation==PR_CONTAINER)open_box(BOX_CONTAINER,f.target);
    else if(f.presentation==PR_DOCUMENT)document(pr_texts[f.text]);
}
static void act(unsigned v,unsigned source,unsigned target)
{PrAction a;a.verb=v;a.source=source;a.target=target;feedback(pr_act(&game,a));}
static unsigned inventory(unsigned char *items)
{
    unsigned i,n=0;
    for(i=1;i<=PR_ITEMS;++i)if(pr_has_item(&S,S.active,i))items[n++]=i;
    return n;
}
static unsigned contents(unsigned char *items)
{
    unsigned i,n=0;
    for(i=1;i<=PR_ITEMS;++i) {
        unsigned pos=S.world.item_position[i];
        if((modal_target==PR_HOTSPOT(3,1) && (i==6 || i==7) && pos==3) ||
           (modal_target==PR_HOTSPOT(7,3) && (i==4 || i==5) && pos==7) ||
           (modal_target==PR_HOTSPOT(25,1) && (i==10 || i==11) && pos==25) ||
           (modal_target==PR_ITEM(8) && pos==PR_CONTAINER_BASE+8))items[n++]=i;
    }
    return n;
}
static unsigned exits(unsigned char *dest)
{
    unsigned i,n=0,from=HERO.location;
    if(S.phase!=PR_A)return 0;
    for(i=1;i<=PR_SCENES;++i)if(pr_local_edge(from,i) && pr_scene_allowed(&S,i)) {
        if(S.active==PR_M && ((from==5 && i==6) || (from==6 && i==5) ||
           (from==6 && i==7 && !pr_done(&S,3)) || (from==8 && i==9) || from==9))continue;
        if(S.active==PR_K && from==2 && i==4)continue;
        dest[n++]=i;
    }
    if(S.active==PR_M && from==6 && pr_done(&S,4))dest[n++]=8;
    return n;
}
static unsigned extras(Extra *out)
{
    unsigned n=0,scene=HERO.location;
#define ADD(target_id,label) do {if(pr_target_here(&S,target_id)) {out[n].target=target_id;out[n].text=PR_TEXT_##label;out[n].x=12+118*n;out[n].w=112;++n;}}while(0)
    if(scene==3 || scene==25)ADD(PR_DEPARTURE,UI_DEPARTURE);
    if(scene==25)ADD(PR_LETTER_DESK,UI_WRITE);
    if(scene==7) {ADD(PR_VALVE,UI_VALVE);ADD(PR_COMPRESSOR_BODY,UI_BODY);}
    if(scene==9) {ADD(PR_FACTORY_GATE,UI_GATE);ADD(PR_TAVERN_APPROACH,UI_TAVERN);}
    if(scene==26)ADD(PR_OPENED_ENVELOPE,UI_ENVELOPE);
#undef ADD
    return n;
}
static unsigned hit_target(Point p)
{
    Extra e[3];
    unsigned i,n=extras(e),scene=HERO.location;
    for(i=0;i<n;++i)if(inside(p,e[i].x,230,e[i].w,17))return e[i].target;
    for(i=0;i<pr_hotspot_count[scene];++i) {
        const PrHotspotMeta *h=&pr_hotspots[scene][i];
        if(inside(p,6+h->l,39+h->t,h->r-h->l,h->b-h->t))return h->target;
    }
    return 0;
}
static void icon(unsigned item,short x,short y,int chosen)
{char name[4]={'I','0'+item/10,'0'+item%10,0};button(x,y,24,24,name,chosen);}
static unsigned hit_item(Point p,int in_box)
{
    unsigned char items[PR_ITEMS];unsigned i,n,start;
    if(in_box) {
        if(box!=BOX_CONTAINER)return 0;
        n=contents(items);
        for(i=0;i<n;++i)if(inside(p,40+(i%4)*108,90+(i/4)*62,24,24))return items[i];
    } else if(!HERO.tab) {
        n=inventory(items);start=HERO.inventory_scroll*9;
        for(i=0;i<9 && start+i<n;++i)if(inside(p,378+(i%3)*36,153+(i/3)*26,24,24))return items[start+i];
    }
    return 0;
}
static const char *entry_text(unsigned entry)
{
    unsigned quest;
    if(entry<PR_FACTS)return pr_fact_texts[entry]?pr_fact_texts[entry]:T(NO_KNOWLEDGE);
    quest=entry-1024-S.active*PR_QUESTS;
    return quest>=1 && quest<=PR_QUESTS?pr_quest_names[quest]:T(NO_KNOWLEDGE);
}
static void modal(void)
{
    Rect r;unsigned i,n,start;unsigned char items[PR_ITEMS];PrTopic topics[8];
    const char *title=T(UI_HISTORY);
    if(box==BOX_DIALOG)title=T(CHOOSE_TOPIC);
    if(box==BOX_CONTAINER)title=T(CONTENTS);
    if(box==BOX_JOURNAL)title=T(UI_JOURNAL);
    if(box==BOX_HINT)title=T(UI_HINT);
    rect(&r,20,52,472,197);EraseRect(&r);FrameRect(&r);proch_text(28,68,title);
    button(354,226,128,18,box==BOX_DIALOG?T(UI_END_TALK):T(UI_END_WINDOW),0);
    if(box==BOX_DIALOG) {
        n=pr_topics(&S,modal_target,topics,8);start=page*4;
        for(i=0;i<4 && start+i<n && start+i<8;++i) {
            rect(&r,30,78+i*34,446,32);FrameRect(&r);
            wrapped(34,90+i*34,62,2,pr_texts[topics[start+i].text]);
        }
        if(n>4) {button(30,226,96,18,T(UI_PREVIOUS),0);button(140,226,96,18,T(UI_NEXT),0);}
    } else if(box==BOX_CONTAINER) {
        n=contents(items);
        for(i=0;i<n;++i) {icon(items[i],40+(i%4)*108,90+(i/4)*62,0);wrapped(40+(i%4)*108,126+(i/4)*62,14,2,pr_item_names[items[i]]);}
        wrapped(30,202,63,2,T(UI_TAKE_HELP));
    } else if(box==BOX_DOCUMENT || box==BOX_HINT) {
        document_next=layout(30,90,62,10,document_current,1);
        button(30,226,96,18,T(UI_PREVIOUS),0);button(140,226,96,18,T(UI_NEXT),0);
    } else if(box==BOX_JOURNAL) {
        start=page*3;n=HERO.journal_count;
        for(i=0;i<3 && start+i<n;++i) {
            unsigned entry=HERO.journal[start+i];
            const char *prefix=T(UI_COMPLETE);
            if(entry<PR_FACTS)prefix=HERO.confidence[entry]==PR_KNOWN?T(UI_KNOWN):
                HERO.confidence[entry]==PR_HEARD?T(UI_HEARD):T(UI_SUSPECT);
            proch_text(30,86+i*44,prefix);wrapped(30,98+i*44,62,2,entry_text(entry));
        }
        if(!n)wrapped(30,90,62,4,T(UI_EMPTY_JOURNAL));
        button(30,226,96,18,T(UI_PREVIOUS),0);button(140,226,96,18,T(UI_NEXT),0);
    } else if(box==BOX_HISTORY) {
        start=page*3;n=history_count[S.active];
        for(i=0;i<3 && start+i<n;++i)wrapped(30,90+i*44,62,3,history[S.active][start+i]);
        button(30,226,96,18,T(UI_PREVIOUS),0);button(140,226,96,18,T(UI_NEXT),0);
    }
}
static void draw(void)
{
    Rect r;unsigned i,n,start,scene=HERO.location;unsigned char items[PR_ITEMS],dest[PR_SCENES];Extra e[3];
    SetPort(window);EraseRect(&window->portRect);
    rect(&r,4,23,364,226);FrameRect(&r);proch_text(8,34,pr_scene_names[scene]);
    rect(&r,6,39,360,208);FrameRect(&r);
    for(i=0;i<pr_hotspot_count[scene];++i) {
        const PrHotspotMeta *h=&pr_hotspots[scene][i];
        rect(&r,6+h->l,39+h->t,h->r-h->l,h->b-h->t);FrameRect(&r);
        wrapped(r.left+3,r.top+12,(r.right-r.left-6)/7,3,h->name);
    }
    proch_text(12,151,T(UI_TEST_ART));n=extras(e);
    for(i=0;i<n;++i)button(e[i].x,230,e[i].w,17,pr_texts[e[i].text],0);
    rect(&r,372,23,136,102);FrameRect(&r);rect(&r,378,42,48,48);FrameRect(&r);
    proch_text(397,70,S.active==PR_M?"M":"K");
    proch_text(432,52,S.active==PR_M?T(UI_M_NAME):T(UI_K_NAME));
    proch_text(432,66,S.active==PR_M?T(UI_M_SURNAME):T(UI_K_SURNAME));
    button(378,96,124,20,T(UI_SWITCH),0);
    rect(&r,372,129,136,120);FrameRect(&r);
    button(373,130,67,18,T(UI_INVENTORY),!HERO.tab);button(440,130,67,18,T(UI_EXITS),HERO.tab);
    if(!HERO.tab) {
        n=inventory(items);start=HERO.inventory_scroll*9;
        for(i=0;i<9 && start+i<n;++i)icon(items[start+i],378+(i%3)*36,153+(i/3)*26,selected==items[start+i]);
    } else {
        n=exits(dest);start=HERO.map_scroll*3;
        for(i=0;i<3 && start+i<n;++i) {rect(&r,376,150+i*26,128,25);FrameRect(&r);wrapped(379,162+i*26,17,2,pr_scene_names[dest[start+i]]);}
    }
    button(376,232,60,15,"<",0);button(442,232,60,15,">",0);
    rect(&r,4,253,504,43);FrameRect(&r);
    if(history_count[S.active])wrapped(9,266,70,3,history[S.active][history_count[S.active]-1]);
    for(i=0;i<8;++i)button(4+(i%4)*128,300+(i/4)*22,120,18,pr_texts[PR_TEXT_UI_LOOK+i],verb==i);
    if(box)modal();
}
static void switch_hero(void)
{
    unsigned before=S.active;
    selected=0;act(PR_SWITCH,0,0);
    if(S.active!=before) {
        if(!history_count[S.active]) {narrate(S.active==PR_K?T(OPENING_K):T(OPENING_M));document(history[S.active][0]);}
        else narrate(pr_scene_names[HERO.location]);
    }
}
static void target_click(unsigned target)
{
    if(!target) {narrate(T(NO_EFFECT));return;}
    if(target==PR_DEPARTURE || target==PR_LETTER_DESK)act(PR_TALK,0,target);
    else if(target==PR_TAVERN_APPROACH && verb==PR_GO)act(PR_GO,0,target);
    else act(verb,verb==PR_USE?selected:0,target);
    if(verb==PR_USE)selected=0;
}
static void modal_click(Point p)
{
    unsigned i,n;PrTopic topics[8];
    if(inside(p,354,226,128,18)) {close_box();return;}
    if(box==BOX_DOCUMENT || box==BOX_HINT) {
        if(inside(p,140,226,96,18) && *document_next)document_current=document_next;
        if(inside(p,30,226,96,18) && document_current!=document_start) {
            const char *scan=document_start,*last=scan;
            while(scan<document_current && *scan) {last=scan;scan=layout(0,0,62,10,scan,0);}
            document_current=last;
        }
        return;
    }
    if(box==BOX_DIALOG) {
        n=pr_topics(&S,modal_target,topics,8);
        for(i=0;i<4 && page*4+i<n && page*4+i<8;++i)if(inside(p,30,78+i*34,446,32)) {
            unsigned target=modal_target,choice=topics[page*4+i].id;
            close_box();act(PR_CHOOSE,target,choice);return;
        }
        if(inside(p,30,226,96,18) && page)--page;
        if(inside(p,140,226,96,18) && (page+1u)*4<n)++page;
    } else if(box==BOX_JOURNAL || box==BOX_HISTORY) {
        n=box==BOX_JOURNAL?HERO.journal_count:history_count[S.active];
        if(inside(p,30,226,96,18) && page)--page;
        if(inside(p,140,226,96,18) && (page+1u)*3<n)++page;
        for(i=0;i<3 && page*3+i<n;++i)if(inside(p,30,76+i*44,446,44)) {
            const char *s=box==BOX_JOURNAL?entry_text(HERO.journal[page*3+i]):history[S.active][page*3+i];
            document(s);return;
        }
    }
}
static void click(Point p)
{
    unsigned i,n;unsigned char dest[PR_SCENES];
    if(box) {modal_click(p);return;}
    if(inside(p,378,96,124,20)) {switch_hero();return;}
    if(inside(p,373,130,67,18)) {HERO.tab=0;return;}
    if(inside(p,440,130,67,18)) {HERO.tab=1;return;}
    if(inside(p,376,232,60,15)) {if(HERO.tab) {if(HERO.map_scroll)--HERO.map_scroll;}else if(HERO.inventory_scroll)--HERO.inventory_scroll;return;}
    if(inside(p,442,232,60,15)) {
        if(HERO.tab) {n=exits(dest);if((HERO.map_scroll+1u)*3<n)++HERO.map_scroll;}
        else {unsigned char items[PR_ITEMS];n=inventory(items);if((HERO.inventory_scroll+1u)*9<n)++HERO.inventory_scroll;}return;
    }
    if(inside(p,4,253,504,43)) {open_box(BOX_HISTORY,0);page=history_count[S.active]?(history_count[S.active]-1)/3:0;return;}
    for(i=0;i<8;++i)if(inside(p,4+(i%4)*128,300+(i/4)*22,120,18)) {verb=i;selected=0;return;}
    if(HERO.tab) {
        n=exits(dest);
        for(i=0;i<3 && HERO.map_scroll*3+i<n;++i)if(inside(p,376,150+i*26,128,25)) {
            act(PR_GO,0,dest[HERO.map_scroll*3+i]);selected=0;
            if(S.phase!=PR_A)narrate(T(UI_STAGE_LIMIT));
            return;
        }
    }
    if(inside(p,6,39,360,208))target_click(hit_target(p));
}
static void mouse_down(Point p)
{SetPort(window);GlobalToLocal(&p);down_point=p;pressed_in_box=box!=0;pressed=hit_item(p,pressed_in_box);}
static void mouse_up(Point p)
{
    unsigned old_box=box,old_verb=verb,old_selected=selected;
    previous=S;SetPort(window);GlobalToLocal(&p);
    if(pressed) {
        unsigned item=pressed;pressed=0;
        if(pressed_in_box) {
            if(inside(p,372,129,136,120))act(PR_TAKE,0,PR_ITEM(item));
            else if(hit_item(p,1)==item) {act(PR_LOOK,0,PR_ITEM(item));document(pr_item_look[item]);}
        } else if(inside(p,6,39,360,208) && (p.h!=down_point.h || p.v!=down_point.v)) {
            act(PR_USE,item,hit_target(p));selected=0;
        } else if(verb==PR_USE) {
            if(selected && selected!=item) {act(PR_USE,selected,PR_ITEM(item));selected=0;}
            else {selected=item;narrate(pr_item_names[item]);narrate(T(UI_CHOOSE_TARGET));}
        } else if(verb==PR_OPEN && item==8)act(PR_OPEN,0,PR_ITEM(8));
        else {act(PR_LOOK,0,PR_ITEM(item));document(pr_item_look[item]);}
    } else click(p);
    damage(old_box,old_verb,old_selected);
}
static void new_game(void)
{close_box();pr_new_game(&game);memset(history_count,0,sizeof(history_count));selected=0;verb=PR_LOOK;narrate(T(OPENING_M));document(T(OPENING_M));invalidate();}
static void menu_command(long value)
{
    unsigned old_box=box,old_verb=verb,old_selected=selected,q;
    short menu=value>>16,item=value&0xffff;
    previous=S;
    if(menu==128 && item==1)new_game();
    if(menu==128 && item==6)running=0;
    if(menu==129 && item==1)open_box(BOX_JOURNAL,0);
    if(menu==129 && item==2) {
        unsigned level;
        if(S.active==PR_M) {q=1;while(q<=5 && (q==2 || pr_done(&S,q)))++q;}
        else {q=6;while(q<=8 && pr_done(&S,q))++q;}
        if(S.phase!=PR_A || q>8 || (S.active==PR_M && q>5))document(T(UI_NO_HINT));
        else {level=S.quest[q-1].hint_level;document(pr_quest_hints[q][level]);box=BOX_HINT;if(level<2)++S.quest[q-1].hint_level;}
    }
    if(menu==130 && item==1)document(T(UI_HELP));
    HiliteMenu(0);damage(old_box,old_verb,old_selected);
}
int main(void)
{
    Rect bounds;MenuHandle m;
    MaxApplZone();InitGraf(&qd.thePort);InitFonts();InitWindows();InitMenus();TEInit();InitDialogs(NULL);InitCursor();
    m=NewMenu(128,(ConstStringPtr)"\pPlik");AppendMenu(m,(ConstStringPtr)"\pNowa gra;Wczytaj/O;Zapisz/S;Zapisz jako;-;Wyjscie/Q");
    DisableItem(m,2);DisableItem(m,3);DisableItem(m,4);InsertMenu(m,0);
    m=NewMenu(129,(ConstStringPtr)"\pGra");AppendMenu(m,(ConstStringPtr)"\pDziennik/J;Podpowiedz/H");InsertMenu(m,0);
    m=NewMenu(130,(ConstStringPtr)"\pPomoc");AppendMenu(m,(ConstStringPtr)"\pSterowanie");InsertMenu(m,0);DrawMenuBar();
    SetRect(&bounds,0,20,512,342);window=NewWindow(NULL,&bounds,(ConstStringPtr)"\pPROCH",true,plainDBox,(WindowPtr)-1L,false,0);
    if(!window)return 1;
    SetPort(window);SetOrigin(0,20);new_game();
    while(running) {
        EventRecord e;WindowPtr hit;
        if(!WaitNextEvent(everyEvent,&e,6,NULL))continue;
        switch(e.what) {
        case updateEvt:if((WindowPtr)e.message==window) {BeginUpdate(window);draw();EndUpdate(window);}break;
        case mouseDown:switch(FindWindow(e.where,&hit)) {
            case inMenuBar:menu_command(MenuSelect(e.where));break;
            case inContent:if(hit==window) {SelectWindow(window);mouse_down(e.where);}break;
            }break;
        case mouseUp:mouse_up(e.where);break;
        case keyDown:
            if(e.modifiers&cmdKey)menu_command(MenuKey(e.message&charCodeMask));
            else {
                unsigned old_box=box,old_verb=verb,old_selected=selected;previous=S;
                if((e.message&charCodeMask)==9)switch_hero();
                if((e.message&charCodeMask)==27) {close_box();selected=0;}
                damage(old_box,old_verb,old_selected);
            }break;
        }
    }
    DisposeWindow(window);return 0;
}
