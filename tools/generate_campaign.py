#!/usr/bin/env python3
"""Compile map metadata and the editorial dependency graph; not prose rules."""
from pathlib import Path
import json
import sys

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
    header='''/* Generated: authorship stays in the root JSON. */
#ifndef PROCH_CAMPAIGN_DATA_H
#define PROCH_CAMPAIGN_DATA_H
#include <stdint.h>
typedef struct { uint8_t actors,phases,region; } PrSceneMeta;
extern const PrSceneMeta pr_scenes[44];
extern const uint8_t pr_edges[44][44];
extern const uint8_t pr_quest_steps[41];
extern const uint8_t pr_dependencies[41][5];
#endif
'''
    source='#include "campaign_data.h"\nconst PrSceneMeta pr_scenes[44]={\n'
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
    (out/'campaign_data.h').write_text(header)
    (out/'campaign_data.c').write_text(source)


if __name__=='__main__':generate(sys.argv[1] if len(sys.argv)>1 else ROOT/'build/generated')
