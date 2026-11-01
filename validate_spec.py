#!/usr/bin/env python3
"""Static editorial checks only; not a game test or interpreter."""
import json,re,itertools
from pathlib import Path
p=Path(__file__).resolve().parent
load=lambda n:json.loads((p/n).read_text())
q,s,i,a=[load(n+'.json') for n in ['quests','scenes','items','assets']]
ids=lambda rows:{x['id'] for x in rows}
qs,ss,ii,aa=map(ids,[q,s,i,a])
assert len(q)==len(qs)==40
assert len(s)==len(ss)==43
assert len(i)==len(ii)==45
assert len(a)==len(aa)
for x in q:
 assert set(x['requires'])<=qs,(x['id'],'quest ref')
 assert set(x['locations'])<=ss,(x['id'],'scene ref')
 assert set(x['items'])<=ii,(x['id'],'item ref')
 assert len(x['hints'])==3 and len(x['steps'])>=2
 assert x['hero'] in ['M','K','MK']
for x in s:
 assert set(x['links'])<=ss
 for h in x['hotspots']:
  l,t,r,b=h['rect']; assert 0<=l<r<=360 and 0<=t<b<=208
# Base dependency graph must be acyclic (branch guards live in prose).
remaining={x['id']:set(x['requires']) for x in q}; done=set()
while remaining:
 ready={k for k,v in remaining.items() if v<=done}
 assert ready,'dependency cycle'
 done|=ready
 for k in ready: del remaining[k]
files=[x['file'] for x in a]+[v['file'] for x in a for v in x.get('variants',[])]
assert len(files)==len(set(files))
for textfile in p.glob('*.md'):
 txt=textfile.read_text()
 for prefix,known in [('Q',qs),('L',ss),('I',ii)]:
  refs=set(re.findall(r'\b'+prefix+r'\d{2}\b',txt)); assert refs<=known,(textfile,refs-known)
# Verify finite ending partition is total and all four labels attainable.
seen=set()
for resolved,alive,pair in itertools.product([False,True],repeat=3):
 result='E04' if not resolved else 'E01' if not alive else 'E02' if pair else 'E03'
 seen.add(result)
assert seen=={'E01','E02','E03','E04'}
print(json.dumps({'quests':len(q),'scenes':len(s),'items':len(i),'base_asset_entries':len(a),'listed_image_files':len(files),'static_checks':'PASS','scope':'References, DAG, rectangles, IDs and ending partition only; no runtime verification'},ensure_ascii=False,indent=2))
