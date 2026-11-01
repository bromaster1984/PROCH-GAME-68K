#!/usr/bin/env python3
"""Play chapter A through native mouse/key events; never set engine flags."""
import argparse
import json
from pathlib import Path
from test_native_demo import Driver


class CampaignDriver(Driver):
    def verb(self,index):
        self.click(60+(index%4)*128,309+(index//4)*22)

    def spot(self,index):
        # Root scene hotspots in the editorial JSON (the 4th is not used here).
        self.click([50,190,300][index-1],[145,120,120][index-1])

    def inspect(self,index):
        self.verb(0);self.spot(index)

    def talk(self,index,topic=0):
        self.verb(4);self.spot(index);self.click(100,90+34*topic)

    def go(self,slot,title):
        self.click(470,138);self.click(420,162+26*slot);self.expect(title)

    def inventory(self):
        self.click(400,138)

    def source(self,index):
        self.inventory();self.verb(3);self.click(390+(index%3)*36,165+(index//3)*26)

    def use(self,index,target):
        self.source(index);self.spot(target)

    def open(self,index):
        self.verb(1);self.spot(index)

    def take_first(self):
        self.execute('xdotool','mousemove','--window',self.args.window,50,100,
                     'mousedown',1,'sleep',0.16,'mousemove','--window',self.args.window,
                     390,210,'sleep',0.16,'mouseup',1,'sleep',0.3)

    def journal_title(self,title,page,index):
        self.key('alt+j')
        for _ in range(page):self.click(180,235)
        self.expect(title,30,98+44*index)
        self.capture('campaign-a-'+title.split()[0])
        self.key('Escape')

    def run(self):
        self.expect('Gabinet Koreckiego');self.key('Escape')
        self.inspect(2);self.expect('Zatrudnienie w gorzelni w Wąglanach.',30,90);self.key('Escape')
        self.talk(1);self.talk(1,1)
        self.go(0,'Przedpokój Koreckich');self.talk(1)
        self.journal_title('Cena obietnicy',0,2)
        self.go(1,'Redakcja Izydora');self.use(0,1);self.talk(1);self.talk(1,1)
        self.go(1,'Dworzec warszawski');self.inspect(2);self.use(1,3)
        self.expect('Przedział pociągu');self.talk(1);self.talk(2)
        self.go(0,'Postój przy parowozie');self.talk(1)
        self.inspect(2);self.key('Escape');self.verb(0);self.click(50,238)
        self.talk(1,1);self.open(3)
        self.key('Tab');self.expect('Postój przy parowozie')  # open container blocks switch
        self.take_first();self.take_first();self.key('Escape')
        self.source(3);self.click(50,238)           # wrench -> valve; I41 becomes owned
        self.source(4);self.click(462,191)          # rag -> I41 (sixth inventory slot)
        self.source(5);self.click(180,238)          # I41 -> body
        self.source(3);self.click(50,238)           # close valve
        self.talk(1,2)                             # running test
        self.use(3,3);self.use(3,3)                 # return wrench, then shifted rag
        self.go(0,'Przedział pociągu');self.go(1,'Stacja Opoczno')
        self.use(0,1);self.talk(1);self.expect('Droga i most w Wąglanach')
        self.inspect(3);self.verb(0);self.click(50,238)
        self.verb(5);self.click(180,238)
        self.journal_title('Przyjazd',2,2)
        self.key('Tab');self.expect('Pokój Konstancji w Warszawie');self.key('Escape')
        self.open(1);self.take_first();self.take_first();self.key('Escape')
        self.inventory();self.verb(0);self.click(390,165);self.key('Escape')
        self.use(0,3);self.use(1,3)                  # photo + document -> bag
        self.click(50,238);self.click(100,90)
        self.expect('Pokój w Seroczynie')
        self.open(1);self.take_first();self.take_first();self.key('Escape')
        self.go(0,'Korytarz Borakowskich');self.talk(1)
        self.go(1,'Kuchnia w Seroczynie');self.talk(1)
        self.go(0,'Korytarz Borakowskich');self.go(2,'Park Borakowskich')
        self.use(3,2);self.go(1,'Droga pod Seroczynem');self.talk(1)
        self.go(0,'Park Borakowskich');self.go(0,'Korytarz Borakowskich');self.go(0,'Pokój w Seroczynie')
        self.source(3);self.click(426,191);self.click(100,90) # paper + pencil, Izydor
        self.go(0,'Korytarz Borakowskich');self.use(3,2)
        self.go(0,'Pokój w Seroczynie');self.go(0,'Korytarz Borakowskich')
        self.verb(0);self.click(50,238);self.talk(1,1)
        self.go(0,'Pokój w Seroczynie');self.click(50,238);self.click(100,90)
        self.expect('Pokój w Sopocie')
        self.journal_title('List, który nie wyszedł',2,0)
        self.key('Tab');self.expect('Droga i most w Wąglanach')
        self.journal_title('Przyjazd',2,2)


if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--container',default='proch-emulation')
    parser.add_argument('--window',default='0x200004')
    parser.add_argument('--profile',required=True,type=Path)
    args=parser.parse_args();args.part='campaign-a'
    d=CampaignDriver(args);d.run()
    (d.directory/'campaign-a-result.json').write_text(json.dumps({
        'result':'PASS','checks':d.passed,'run_id':d.run_id,
        'application_sha256':d.profile['application_sha256'],'profile':str(args.profile),
        'scope':'Q01-Q08 native UI, Mini vMac Plus/System 6.0.8/4 MB; not Macintosh SE'},
        ensure_ascii=False,indent=2)+'\n')
