#!/usr/bin/env python3
"""Drive real mouse/key events in Mini vMac. Assert the rendered bitmap font.

Run q09, q12, q21 in order on a fresh demo. No in-process state shortcuts.
Requires the local test container/window described in README_PL.
"""
import argparse
import json
from pathlib import Path
import subprocess
import time
import uuid
import hashlib
import textwrap
from PIL import Image
from capture_screen import convert
from generate_content import glyphs
from generate_content import UI_TEXT, REPLIES


class Driver:
    def __init__(self, args):
        self.args=args
        self.directory=Path('/workspace/testing/native-ui')
        self.directory.mkdir(exist_ok=True)
        self.rows=glyphs()[1]
        self.passed=[]
        self.run_id=str(uuid.uuid4())
        self.profile=json.loads((args.profile/'inputs.json').read_text())
        actual=hashlib.sha256((args.profile/'PROCH.bin').read_bytes()).hexdigest()
        if self.profile.get('application_sha256')!=actual:
            raise ValueError('Profile application differs from its boot-time manifest')
        (self.directory/(args.part+'-result.json')).unlink(missing_ok=True)

    def execute(self, *command):
        subprocess.run(['docker','exec','-e','DISPLAY=:99',self.args.container,*map(str,command)],check=True)

    def click(self,x,y):
        self.execute('xdotool','mousemove','--window',self.args.window,x,y,
                     'mousedown',1,'sleep',0.12,'mouseup',1,'sleep',0.16)

    def key(self,key):
        self.execute('xdotool','key','--clearmodifiers',key,'sleep',0.25)

    def capture(self,name='last'):
        if name!='last':
            previous=None
            stable=0
            deadline=time.monotonic()+15
            while time.monotonic()<deadline:
                im=self.capture()
                pixels=im.tobytes()
                stable=stable+1 if pixels==previous else 0
                previous=pixels
                if stable>=3:
                    for suffix in ['.xwd','.png']:
                        dest=self.directory/(name+suffix)
                        temporary=self.directory/(name+suffix+'.stable.tmp')
                        temporary.write_bytes((self.directory/('last'+suffix)).read_bytes())
                        temporary.replace(dest)
                    return im
                time.sleep(0.25)
            raise AssertionError('Framebuffer did not become stable: '+name)
        self.execute('xwd','-nobdrs','-silent','-id',self.args.window,
                     '-out','/testing/native-ui/'+name+'.xwd')
        convert(self.directory/(name+'.xwd'),self.directory/(name+'.png'))
        return Image.open(self.directory/(name+'.png')).convert('1')

    def expect(self,text,x=8,baseline=34):
        # The emulated Mac cursor is part of the framebuffer; keep it off text.
        self.execute('xdotool','mousemove','--window',self.args.window,505,330)
        deadline=time.monotonic()+12
        while True:
            im=self.capture()
            ok=True
            for i,c in enumerate(text):
                for y,row in enumerate(self.rows[c]):
                    for dx in range(6):
                        expected = bool(row & (16>>dx)) if dx<5 else False
                        if (im.getpixel((x+i*7+dx,baseline-8+y))==0)!=expected:
                            ok=False;break
                    if not ok:break
                if not ok:break
            if ok:
                self.passed.append(text)
                print('PASS native pixels:',text,flush=True)
                return
            if time.monotonic()>deadline: raise AssertionError('Screen did not show: '+text)
            time.sleep(0.25)

    def journal(self,*titles):
        self.key('alt+j')
        for i,title in enumerate(titles): self.expect(title,114,90+24*i)
        self.capture(self.args.part+'-journal')
        self.key('Escape')

    def q09(self):
        self.expect('Dziedziniec gorzelni')
        self.click(440,105); self.expect('Chata rybaka')
        self.key('Tab'); self.expect('Dziedziniec gorzelni')
        self.click(64,331); self.click(50,145)
        self.key('Tab'); self.expect('Dziedziniec gorzelni')  # modal blocks switching
        self.click(180,90)
        self.click(473,138); self.click(430,164); self.expect('Korytarz stróżówki')
        self.click(430,196); self.expect('Pokój Mikołaja')
        self.click(192,309); self.click(80,100); self.click(52,127); self.click(438,235)
        self.click(404,138); self.click(442,309); self.click(390,165); self.click(80,100)
        self.click(192,309); self.click(80,100); self.click(180,90)
        self.click(52,127); self.click(52,127); self.click(438,235)
        self.click(473,138); self.click(430,164); self.click(430,164)
        self.expect('Dziedziniec gorzelni')
        self.click(64,331); self.click(50,145); self.click(180,116)
        self.journal('Klucze zmarłego stróża')

    def q12(self):
        self.expect('Dziedziniec gorzelni')
        self.click(473,138); self.click(430,228); self.expect('Warsztat i skład')
        self.click(192,309); self.click(80,100)
        for _ in range(3): self.click(52,127)
        self.click(438,235)
        self.key('Tab'); self.expect('Chata rybaka')
        self.key('Tab'); self.expect('Warsztat i skład')
        self.click(430,164); self.click(430,164); self.click(430,196)
        self.expect('Pokój Mikołaja')
        self.click(64,309); self.click(86,50); self.click(260,100)
        self.click(404,138); self.click(442,309)
        self.click(426,201); self.click(86,50)       # paper strip -> door
        self.click(390,201); self.click(260,100)    # wax -> window
        self.click(462,165); self.click(260,100)    # thread -> window
        self.click(80,190)                         # rest; no selected source
        self.click(64,309); self.click(86,50); self.click(260,100)
        self.click(442,309); self.click(270,200)
        self.journal('Klucze zmarłego stróża','Nienaruszone wejścia')
        self.capture('q12-room')

    def q21(self):
        self.key('Tab'); self.expect('Chata rybaka')
        self.key('alt+j'); self.expect('Nie zakończono jeszcze żadnej znanej sprawy.',30,94); self.key('Escape')
        self.click(200,267)
        self.expect('Ten sam czas, inne miejsce.',30,90)
        self.expect('Chata rybaka',30,120)
        self.key('Escape')
        self.click(64,331); self.click(50,145); self.click(180,90)
        self.click(192,309); self.click(300,100)
        self.click(52,127); self.click(52,127); self.click(438,235)
        self.click(442,309); self.click(390,165); self.click(180,100)
        self.click(426,165); self.click(180,100); self.click(180,100)
        self.click(180,90); self.click(180,116); self.click(180,142); self.click(438,235)
        self.click(426,165); self.click(400,65)
        self.journal('Zwykła suknia')
        self.capture('q21-hut')
        self.key('Tab'); self.expect('Pokój Mikołaja')
        self.journal('Klucze zmarłego stróża','Nienaruszone wejścia')

    def long_dialogue(self):
        self.expect('Pokój Mikołaja')
        self.capture('q12-room')
        self.key('Tab');self.expect('Chata rybaka')
        self.capture('q21-hut');self.journal('Zwykła suknia')
        self.key('Tab');self.expect('Pokój Mikołaja')
        self.click(473,138);self.click(430,164);self.click(430,164)
        self.expect('Dziedziniec gorzelni')
        self.click(64,331);self.click(50,145);self.click(180,90)
        for i,line in enumerate(textwrap.wrap(UI_TEXT['FLOREK_QUOTE'],width=70)):
            self.expect(line,9,266+12*i)
        self.capture('long-dialogue')

    def description_history(self):
        self.expect('Dziedziniec gorzelni')
        self.click(200,267);self.click(80,235)
        self.expect('Papier cały. Nitka na miejscu.',30,90)
        self.click(100,90)
        self.expect(REPLIES['Q12'],30,90)
        self.capture('q12-description')
        self.key('Escape')


if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('part',choices=['q09','q12','q21','long_dialogue','description_history'])
    parser.add_argument('--container',default='proch-emulation')
    parser.add_argument('--window',default='0x200004')
    parser.add_argument('--profile',required=True,type=Path,help='Prepared, running Mini vMac input directory')
    args=parser.parse_args()
    driver=Driver(args)
    getattr(driver,args.part)()
    (driver.directory/(args.part+'-result.json')).write_text(json.dumps({
        'part':args.part,'result':'PASS','checks':driver.passed,'run_id':driver.run_id,
        'application_sha256':driver.profile['application_sha256'],
        'profile':str(args.profile),
        'scope':'Mini vMac Plus / System 6.0.8 / 4 MB, native UI, demo fixture'},ensure_ascii=False,indent=2)+'\n')
