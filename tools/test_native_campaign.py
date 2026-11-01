#!/usr/bin/env python3
"""Play implemented chapters through native mouse/key events; never set engine flags."""
import argparse
import json
from pathlib import Path
from test_native_demo import Driver


class CampaignDriver(Driver):
    def __init__(self,args):
        super().__init__(args)
        self.scenes=json.loads((Path(__file__).resolve().parents[1]/'scenes.json').read_text())
        self.scene=1

    def expect(self,text,*args):
        super().expect(text,*args)
        for s in self.scenes:
            if s['name']==text:self.scene=int(s['id'][1:])

    def verb(self,index):
        self.click(60+(index%4)*128,309+(index//4)*22)

    def spot(self,index):
        h=self.scenes[self.scene-1]['hotspots'][index-1]
        l,t,r,b=h['rect'];self.click(6+(l+r)//2,39+(t+b)//2)

    def inspect(self,index):
        self.verb(0);self.spot(index)

    def talk(self,index,topic=0):
        self.verb(4);self.spot(index)
        self.click(100,90+34*topic+(40 if self.scene==30 and index==1 else 0))

    def go(self,slot,title):
        self.click(470,138)
        for _ in range(slot//3):self.click(470,239)
        self.click(420,162+26*(slot%3));self.expect(title)

    def inventory(self):
        self.click(400,138)

    def source(self,index):
        self.inventory();self.verb(3);self.click(390+(index%3)*36,165+(index//3)*26)

    def use(self,index,target):
        self.source(index);self.spot(target)

    def source_late(self,index):
        """Select an item from either of the first two inventory pages."""
        self.inventory();self.click(405,239)
        if index>=9:self.click(470,239)
        self.verb(3);slot=index%9
        self.click(390+(slot%3)*36,165+(slot//3)*26)

    def use_late(self,index,target):
        self.source_late(index);self.spot(target)

    def extra(self,index,verb=0):
        self.verb(verb);self.click(50+118*index,238)

    def talk_extra(self,index,topic=0):
        self.extra(index,4);self.click(100,90+34*topic)

    def open(self,index):
        self.verb(1);self.spot(index)

    def take_first(self):
        self.execute('xdotool','mousemove','--window',self.args.window,50,100,
                     'mousedown',1,'sleep',0.16,'mousemove','--window',self.args.window,
                     390,210,'sleep',0.16,'mouseup',1,'sleep',0.3)

    def journal_title(self,title,page,index,capture_name=None):
        self.key('alt+j')
        for _ in range(page):self.click(180,235)
        self.expect(title,30,98+44*index)
        self.capture(capture_name or 'campaign-a-'+title.split()[0])
        self.key('Escape')

    def chapter_a(self):
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


    def chapter_b(self):
        self.expect('Droga i most w Wąglanach')
        self.go(1,'Dziedziniec gorzelni');self.talk(1)
        self.go(1,'Korytarz stróżówki');self.go(1,'Pokój Mikołaja')
        self.open(1);self.take_first();self.key('Escape')
        self.source(3);self.click(50,238)             # key -> drawer
        self.verb(1);self.click(50,238);self.take_first()
        self.click(50,100);self.key('Escape')        # examine Bible, leave it
        self.go(0,'Korytarz stróżówki');self.go(0,'Dziedziniec gorzelni');self.talk(1,1)
        self.journal_title('Klucze zmarłego stróża',3,0)
        self.go(0,'Droga i most w Wąglanach');self.go(0,'Karczma')
        self.talk(1);self.talk(1,1);self.use(0,1);self.talk(1,2)
        self.go(0,'Droga i most w Wąglanach');self.go(2,'Dom poszkodowanego robotnika')
        self.talk(1);self.talk(1,1);self.talk(2);self.talk(3)
        self.go(0,'Droga i most w Wąglanach');self.go(1,'Dziedziniec gorzelni')
        self.go(3,'Warsztat i skład');self.open(1)
        self.take_first();self.take_first();self.take_first();self.key('Escape')
        self.go(0,'Dziedziniec gorzelni');self.go(1,'Korytarz stróżówki');self.go(1,'Pokój Mikołaja')
        self.inspect(2);self.verb(0);self.click(180,238)
        self.source(8);self.click(180,238)            # strip -> door
        self.use(7,2);self.use(6,2)                  # wax, thread -> window
        self.verb(3);self.spot(3);self.click(100,90)  # explicit rest
        self.inspect(2);self.verb(0);self.click(180,238)
        self.execute('xdotool','mousemove','--window',self.args.window,276,198,
                     'mousedown',1,'sleep',0.16,'mousemove','--window',self.args.window,
                     390,210,'sleep',0.16,'mouseup',1,'sleep',0.3)
        self.journal_title('Nienaruszone wejścia',5,0)
        self.go(0,'Korytarz stróżówki');self.key('Tab');self.expect('Korytarz stróżówki')
        self.inspect(3);self.verb(6);self.spot(3);self.inspect(3);self.talk(3)
        self.open(1);self.go(0,'Dziedziniec gorzelni')
        self.journal_title('Imię w ciemności',5,1)
        self.key('Tab');self.expect('Pokój w Sopocie')
        self.verb(4);self.spot(1)
        self.expect('Następna scena opisuje atak i śmiertelny uraz.',30,88)
        self.click(100,164);self.expect('Irena atakuje Konstancję.',30,90);self.key('Escape')
        self.talk(2);self.talk(2,2)                  # pack, confrontation route
        self.go(0,'Ogród i Bergen Strasse');self.inspect(2);self.go(0,'Plaża z sieciami')
        self.verb(5);self.click(50,238);self.expect('Plaża z sieciami')
        self.verb(0);self.click(50,238);self.talk(3);self.key('Escape')
        self.expect('Chata rybaka');self.talk(1)
        self.journal_title('Z dala od świateł',3,1)
        self.key('Tab');self.expect('Dziedziniec gorzelni')
        self.journal_title('Imię w ciemności',5,1)

    def chapter_c_m(self):
        self.expect('Dziedziniec gorzelni')
        self.go(0,'Droga i most w Wąglanach')
        self.go(3,'Plac przy kościele');self.go(1,'Plebania')
        self.talk(2);self.talk(1)
        self.go(0,'Plac przy kościele')
        self.use_late(7,1);self.talk(1)
        self.go(2,'Hall pałacu w Białaczowie')
        self.use_late(8,1);self.go(1,'Biblioteka')
        self.inspect(1);self.verb(3);self.spot(2);self.spot(1)
        self.talk(2);self.use_late(7,1);self.talk(2)
        self.talk_extra(0)
        self.talk(3);self.talk(3,1)
        self.use_late(9,4);self.talk(4);self.talk(4,1)
        self.extra(1);self.key('Escape');self.extra(2);self.talk_extra(2)
        self.go(0,'Hall pałacu w Białaczowie')
        self.go(0,'Plac przy kościele');self.go(0,'Droga i most w Wąglanach')
        self.go(2,'Dziedziniec gorzelni');self.go(4,'Leśna ścieżka')
        self.use_late(10,3);self.go(1,'Brzeg stawu')
        self.inspect(1);self.inspect(2);self.talk(1)
        self.expect('Sięgając po koronkę, Mikołaj ślizga się na pniu.',30,90)
        self.key('Escape');self.expect('Widzenie dawnego obozu')
        self.inspect(2);self.extra(0)
        self.verb(5);self.spot(3)
        self.expect('Leśna ścieżka')
        self.journal_title('Ślad prowadzi do wody',7,2)
        self.go(0,'Dziedziniec gorzelni');self.go(0,'Droga i most w Wąglanach')
        self.go(3,'Plac przy kościele')
        self.talk(1,1);self.talk(1,1)
        self.use_late(2,1);self.talk(1,1)
        self.journal_title('Słowo uczciwe',8,0,'campaign-c-q20')

    def chapter_c_k_q21(self):
        self.key('Tab');self.expect('Chata rybaka')
        self.talk(1);self.open(3)
        self.take_first();self.take_first();self.key('Escape')
        self.use(5,2);self.use(6,2)
        self.talk(2);self.talk(2);self.talk(2)
        self.source(7);self.click(400,65)
        self.journal_title('Zwykła suknia',3,2,'campaign-c-q21')

    def chapter_c_k_q22(self):
        self.go(0,'Plaża z sieciami')
        self.go(1,'Przystań rybacka')
        self.talk(1)
        self.inspect(2);self.expect('Trzy luźne końce',9,266)
        self.use(6,2);self.expect('Używam igły i nici',9,266)
        self.talk(2,1);self.expect('Oczko się zaciska',9,266)
        self.talk(2,0)
        self.talk(2,0);self.expect('Oczko się zaciska',9,266)
        self.talk(2,0);self.talk(2,1);self.talk(2,2)
        self.talk(1)
        self.journal_title('Sieć i zaufanie',4,0,'campaign-c-q22')
        self.go(0,'Plaża z sieciami');self.go(0,'Chata rybaka')

    def chapter_c_k_q23(self):
        self.talk(2);self.talk(2);self.talk(2)
        self.go(0,'Plaża z sieciami');self.go(1,'Przystań rybacka')
        self.talk(1);self.expect('Sąsiad: Przyjąłem',9,266)
        self.journal_title('Żyję',4,1,'campaign-c-q23')
        self.go(0,'Plaża z sieciami');self.go(0,'Chata rybaka')

    def run(self):
        self.chapter_a()
        if self.args.chapter in ('ab','abc_m','abc_mk21','abc_mk22','abc_mk23'):self.chapter_b()
        if self.args.chapter in ('abc_m','abc_mk21','abc_mk22','abc_mk23'):self.chapter_c_m()
        if self.args.chapter in ('abc_mk21','abc_mk22','abc_mk23'):self.chapter_c_k_q21()
        if self.args.chapter in ('abc_mk22','abc_mk23'):self.chapter_c_k_q22()
        if self.args.chapter=='abc_mk23':self.chapter_c_k_q23()


if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--container',default='proch-emulation')
    parser.add_argument('--window',default='0x200004')
    parser.add_argument('--profile',required=True,type=Path)
    parser.add_argument('--chapter',choices=['a','ab','abc_m','abc_mk21','abc_mk22','abc_mk23'],default='a')
    args=parser.parse_args();args.part='campaign-'+args.chapter
    d=CampaignDriver(args);d.run()
    (d.directory/(args.part+'-result.json')).write_text(json.dumps({
        'result':'PASS','checks':d.passed,'run_id':d.run_id,
        'application_sha256':d.profile['application_sha256'],'profile':str(args.profile),
        'scope':('Q01-Q15 both heroes; Q16-Q20 M; Q21-Q23 K' if args.chapter=='abc_mk23' else
                 'Q01-Q15 both heroes; Q16-Q20 M; Q21-Q22 K' if args.chapter=='abc_mk22' else
                 'Q01-Q15 both heroes; Q16-Q20 M; Q21 K' if args.chapter=='abc_mk21' else
                 'Q01-Q15 both heroes; Q16-Q20 M' if args.chapter=='abc_m' else
                 'Q01-Q15' if args.chapter=='ab' else 'Q01-Q08')+
                ' native UI, Mini vMac Plus/System 6.0.8/4 MB; not Macintosh SE'},
        ensure_ascii=False,indent=2)+'\n')
