#!/usr/bin/env python3
"""Compile map metadata and the editorial dependency graph; not prose rules."""
from pathlib import Path
import json
import sys
from generate_content import literal

ROOT=Path(__file__).resolve().parents[1]


def region(scene):
    if scene in [1,2,3,4,5,36,37,41,42]: return 1
    if scene in [6,7]: return 2
    if scene in list(range(8,24))+[38,39,40,43]: return 3
    if scene==24:return 4
    if 25<=scene<=29:return 5
    if 30<=scene<=35:return 6
    raise ValueError(scene)


def generate(directory):
    out=Path(directory);out.mkdir(parents=True,exist_ok=True)
    scenes=json.loads((ROOT/'scenes.json').read_text())
    quests=json.loads((ROOT/'quests.json').read_text())
    meta=[(0,0,0)]*44
    edges=[[0]*44 for _ in range(44)]
    for row in scenes:
        i=int(row['id'][1:])
        actors=(1 if 'M' in row['hero'] else 0)|(2 if 'K' in row['hero'] else 0)
        phases=sum(1<<('ABCDEF'.index(p)) for p in row['phase'].split(','))
        meta[i]=(actors,phases,region(i))
        for link in row['links']:
            j=int(link[1:])
            if region(i)==region(j):edges[i][j]=edges[j][i]=1
    texts=json.loads((ROOT/'content/campaign_texts.json').read_text())
    header='''/* Generated: authorship stays in the root JSON. */
#ifndef PROCH_CAMPAIGN_DATA_H
#define PROCH_CAMPAIGN_DATA_H
#include <stdint.h>
typedef struct { uint8_t actors,phases,region; } PrSceneMeta;
extern const PrSceneMeta pr_scenes[44];
extern const uint8_t pr_edges[44][44];
extern const uint8_t pr_quest_steps[41];
extern const uint8_t pr_dependencies[41][5];
typedef struct { uint16_t target;int16_t l,t,r,b;const char *name,*look; } PrHotspotMeta;
extern const PrHotspotMeta pr_hotspots[44][8];
extern const uint8_t pr_hotspot_count[44];
extern const char *const pr_scene_names[44],*const pr_item_names[46],*const pr_item_look[46];
extern const char *const pr_quest_names[41],*const pr_quest_hints[41][3];
extern const char *const pr_fact_texts[256];
'''
    header+='enum PrText {\n'+',\n'.join('PR_TEXT_'+name for name in texts)+',\nPR_TEXT_COUNT};\n'
    header+='extern const char *const pr_texts[PR_TEXT_COUNT];\n#endif\n'
    source='#include "campaign_data.h"\nconst PrSceneMeta pr_scenes[44]={\n'
    source='#include "model.h"\n'+source
    source+=',\n'.join('{'+','.join(map(str,row))+'}' for row in meta)+'\n};\n'
    source+='const uint8_t pr_edges[44][44]={\n'
    source+=',\n'.join('{'+','.join(map(str,row))+'}' for row in edges)+'\n};\n'
    ordered=sorted(quests,key=lambda q:q['id'])
    source+='const uint8_t pr_quest_steps[41]={0,'+','.join(str(len(q['steps'])) for q in ordered)+'};\n'
    source+='const uint8_t pr_dependencies[41][5]={{0},\n'
    for q in ordered:
        deps=[int(v[1:]) for v in q['requires']]
        if len(deps)>4:raise ValueError('Increase the explicit dependency capacity')
        source+='{'+','.join(map(str,[len(deps)]+deps))+'},\n'
    source+='};\n'
    source+='const char *const pr_texts[PR_TEXT_COUNT]={\n'
    source+=',\n'.join('[PR_TEXT_'+k+']='+literal(v) for k,v in texts.items())+'\n};\n'
    source+='const PrHotspotMeta pr_hotspots[44][8]={{{0}},\n'
    for scene in sorted(scenes,key=lambda row:row['id']):
        i=int(scene['id'][1:])
        if len(scene['hotspots'])>8:raise ValueError('Too many hotspots')
        source+='{'+','.join('{'+','.join([str(i*8+n),*map(str,h['rect']),literal(h['name']),literal(h['examine'])])+'}'
                             for n,h in enumerate(scene['hotspots']))+'},\n'
    source+='};\nconst uint8_t pr_hotspot_count[44]={0,'+','.join(str(len(s['hotspots'])) for s in sorted(scenes,key=lambda row:row['id']))+'};\n'
    items=sorted(json.loads((ROOT/'items.json').read_text()),key=lambda row:row['id'])
    for name,rows,key in [('pr_scene_names',sorted(scenes,key=lambda row:row['id']),'name'),
                          ('pr_item_names',items,'name'),('pr_item_look',items,'look'),
                          ('pr_quest_names',ordered,'title')]:
        source+='const char *const '+name+'[]={"",'+','.join(literal(r[key]) for r in rows)+'};\n'
    source+='const char *const pr_quest_hints[41][3]={{"","",""},\n'
    source+=',\n'.join('{'+','.join(literal(h) for h in q['hints'])+'}' for q in ordered)+'};\n'
    facts=json.loads((ROOT/'content/campaign_facts.json').read_text())
    source+='const char *const pr_fact_texts[256]={\n'
    source+=',\n'.join('[PR_FACT_'+k+']='+literal(v) for k,v in facts.items())+'};\n'
    (out/'campaign_data.h').write_text(header)
    (out/'campaign_data.c').write_text(source)


if __name__=='__main__':generate(sys.argv[1] if len(sys.argv)>1 else ROOT/'build/generated')
