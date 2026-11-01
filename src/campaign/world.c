#include "model.h"
#include "campaign_data.h"

int pr_local_edge(unsigned from,unsigned to)
{ return from>=1 && from<=PR_SCENES && to>=1 && to<=PR_SCENES && pr_edges[from][to]; }

int pr_scene_allowed(const PrState *s,unsigned scene)
{
    unsigned actor=s->active,phase=s->phase;
    int override=0;
    if(actor>=PR_HEROES || phase>PR_F || scene<1 || scene>PR_SCENES)return 0;
    if(actor==PR_M) {
        if(phase==PR_E || (phase==PR_F && !pr_flag(s,PR_M_FREE)))
            return scene==s->hero[PR_M].location && (scene==17 || scene==38);
        if(phase==PR_F && (scene==11 || scene==13 || scene==15 || scene==19 ||
                          scene==20 || scene==22 || scene==23))override=1;
        if(phase==PR_A && scene==9 && pr_done(s,4))override=1;
        if((scene==6 || scene==7) && pr_done(s,5))return 0;
        if(scene==14 || scene==15)if(!pr_done(s,9))return 0;
        if(scene==20 && !pr_done(s,16))return 0;
        if(scene==19 && !pr_done(s,16))return 0;
        if(scene==21 && !pr_done(s,19))return 0;
        if((scene==22 || scene==23) && !pr_done(s,18))return 0;
        if(scene==24 && !(s->locks&PR_VISION))return 0;
        if(scene==43 && (!pr_done(s,40) || !s->ending))return 0;
    } else {
        /* K waits at Opoczno for the shared C -> D transition. */
        if(scene>=9 && scene<=24 && phase<PR_D)return 0;
        if(scene==13) {
            if(phase!=PR_D || !pr_done(s,25) || pr_done(s,28) || s->crisis_substep)return 0;
            override=1; /* The deposit-only Q29 rule is the sole entry. */
        }
        if(scene==20) {
            if(phase!=PR_F || !pr_done(s,35) || s->krystyna_alive!=PR_YES)return 0;
            override=1;
        }
        if(scene==21 && !pr_done(s,25))return 0;
        if(scene==23 && phase!=PR_F && !(s->locks&PR_RESCUE))return 0;
        if(scene==8 && phase==PR_D)override=1;
        if(phase==PR_F && scene>=32 && scene<=35) {
            if(!pr_done(s,39))return 0;
            override=1;
        }
        if(scene==30 && pr_done(s,14))return 0;
    }
    if(scene>=25 && scene<=29 && phase!=PR_A)return 0;
    if(!override && (!(pr_scenes[scene].actors&(1u<<actor)) || !(pr_scenes[scene].phases&(1u<<phase))))return 0;
    return 1;
}

enum PrResult pr_move_local(PrState *s,unsigned scene)
{
    unsigned from=s->hero[s->active].location;
    if(s->player_dead || s->ending || (s->locks&(PR_MODAL|PR_RESCUE|PR_TRANSITION)))return PR_DENIED;
    if(!pr_local_edge(from,scene) || !pr_scene_allowed(s,scene))return PR_DENIED;
    s->hero[s->active].location=(uint8_t)scene;
    s->hero[s->active].map_scroll=0;
    if(!(s->locks&(PR_VISION|PR_SHADOW)))s->hero[s->active].last_safe_location=(uint8_t)scene;
    return PR_OK;
}
