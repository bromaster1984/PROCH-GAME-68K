# PROCH — pełny katalog lokacji i grafik

## Wspólna reguła obrazu

Scena ma 360×208 pikseli, ekran 512×342. PNG to format źródłowy; runtime dostaje własne bitmapy 1-bit. Kolory wyłącznie 0 i 255. Kreska 1 px; drobiny nie zastępują czytelnych przedmiotów. Raster regularny, bez antyaliasingu. Interfejs i tekst zawsze rysuje silnik, nie generator obrazów. Przygotuj grafiki w docelowej rozdzielczości i sprawdź w skali 1:1. Generowanie dużego konceptu wymaga ręcznej lub narzędziowej redukcji i korekty, nie gwarantuje poprawnego finalnego pixelartu.

Prostokąty hotspots w scenes.json to zamknięty projekt startowy interakcji. Ilustracja ma komponować cele w tych obszarach. Są szerokie, by uniknąć polowania na piksel. Wolno skorygować współrzędne do gotowego obrazu, zachowując znaczenie obiektu, bez zmiany questów. Przy nakładaniu celów użyj jawnego z-order i masek. Wyjścia są osobnymi przyciskami panelu Przejścia; nie trzeba zgadywać pikseli drzwi.

Każdy obiekt przenośny rysowany na scenie to osobna bitmapa + maska, po zabraniu znika. Jeśli generator umieścił go w tle, usuń go z tła przed wydaniem. Dla każdej postaci portret 48×48 jest obowiązkowy; sylwetka w lokacji może być stała. Dla M/K dodaj wariant spokojny, zmęczony i alarmowy poprzez brwi/usta; nie zmieniaj tożsamości. Dla K strój elegancki i prosty; dla Grety normalna i zjawa. Dla Krystyny mokra sylwetka po ratunku, bez erotyzacji. Obiekty wskazane w Q, a nieobecne na liście głównych hotspots (np. kartka w kufrze), są w oknie pojemnika otwieranym przez obiekt nadrzędny.

## Manifest

assets.json zawiera każdy bazowy obraz lokacji, wariant fabularny, ikonę, portret i zbliżenie wraz z nazwą pliku i dokładnym opisem. Nazwy nie zależą od polskich znaków. Wariant nie może zmieniać położenia nieruchomych obiektów. Bitmapa bazowa jest stanem domyślnym, warianty nakładaj według nadrzędności: kryzys > skutek > pora > bazowy.

### L01 — Gabinet Koreckiego

Ciężkie biurko po lewej, okno z tramwajem konnym w głębi, fotel gospodarza po prawej. Deszcz na szybie. Papier umowy leży na jasnym fragmencie blatu.

Postać: M; etapy: A. Połączenia topologiczne: L02.

Cele: L01_H1 Korecki [12, 65, 106, 188]; L01_H2 umowa [128, 35, 235, 178]; L01_H3 okno [252, 45, 348, 192]

### L02 — Przedpokój Koreckich

Wysokie lustro, wieszak, drzwi do gabinetu i kufer podróżny. Marian przy bocznych drzwiach.

Postać: MK; etapy: A,E,F. Połączenia topologiczne: L01, L03, L04.

Cele: L02_H1 Marian [12, 65, 106, 188]; L02_H2 kufer [128, 35, 235, 178]; L02_H3 drzwi [252, 45, 348, 192]

### L03 — Pokój Konstancji w Warszawie

Toaletka przy oknie, mała szkatułka na stole, podróżna walizka i fotografia matki. Bez luksusowego nadmiaru drobiazgów.

Postać: K; etapy: A,E,F. Połączenia topologiczne: L02.

Cele: L03_H1 szkatułka [12, 65, 106, 188]; L03_H2 fotografia Luizy [128, 35, 235, 178]; L03_H3 walizka [252, 45, 348, 192]

### L04 — Redakcja Izydora

Biurko publicysty, szuflada korespondencji, szpalty gazety. Izydor w kamizelce, puste miejsce na przekazywane dokumenty.

Postać: MK; etapy: A,C,E,F. Połączenia topologiczne: L02, L05, L38.

Cele: L04_H1 Izydor [12, 65, 106, 188]; L04_H2 poczta [128, 35, 235, 178]; L04_H3 próbna gazeta [252, 45, 348, 192]

### L05 — Dworzec warszawski

Kasa po lewej, tablica odjazdów centralnie, wejście na peron po prawej. Para za oknem, kufry, stalowe wiązary.

Postać: MK; etapy: A,C,E,F. Połączenia topologiczne: L04, L06.

Cele: L05_H1 kasjer [12, 65, 106, 188]; L05_H2 rozkład [128, 35, 235, 178]; L05_H3 bramka [252, 45, 348, 192]

### L06 — Przedział pociągu

Drewniane ławki, ciężarna podróżna przy oknie, drzwi na pomost. Krystyna widoczna w osobnym kadrze rozmowy.

Postać: M; etapy: A. Połączenia topologiczne: L05, L07, L08.

Cele: L06_H1 podróżna [12, 65, 106, 188]; L06_H2 konduktor [128, 35, 235, 178]; L06_H3 drzwi na pomost [252, 45, 348, 192]

### L07 — Postój przy parowozie

Bok maszyny, uproszczona sprężarka i trzy czytelne elementy: dopływ, zawór, przewód. Maszynista stoi z dala od mechanizmu.

Postać: M; etapy: A. Połączenia topologiczne: L06.

Cele: L07_H1 maszynista [12, 65, 106, 188]; L07_H2 sprężarka [128, 35, 235, 178]; L07_H3 skrzynka narzędzi [252, 45, 348, 192]

### L08 — Stacja Opoczno

Niski budynek stacyjny, drogowskaz Wąglany, wóz przy studni. Otwarte niebo, szeroka biała przestrzeń.

Postać: MK; etapy: A,C,E,F. Połączenia topologiczne: L06, L09.

Cele: L08_H1 woźnica [12, 65, 106, 188]; L08_H2 drogowskaz [128, 35, 235, 178]; L08_H3 ławka [252, 45, 348, 192]

### L09 — Droga i most w Wąglanach

Mostek nad wodą, młyn w tle, po prawej brama fabryki. Las odcina horyzont zwartą czernią.

Postać: MK; etapy: B,C,D,F. Połączenia topologiczne: L08, L10, L11, L16, L18.

Cele: L09_H1 drogowskaz [12, 65, 106, 188]; L09_H2 młyn [128, 35, 235, 178]; L09_H3 most [252, 45, 348, 192]

### L10 — Karczma

Tolek przy stole, Celina za ladą; wolne miejsce dla fotografa w etapie D. Belki, jasne naczynia na ciemnym tle.

Postać: MK; etapy: B,C,D. Połączenia topologiczne: L09.

Cele: L10_H1 Tolek [12, 65, 106, 188]; L10_H2 Celina [128, 35, 235, 178]; L10_H3 fotograf [252, 45, 348, 192]

### L11 — Dziedziniec gorzelni

Biały dawny dworek, brama, komin i niewykończony budynek. Florek obok stojaka na rowery.

Postać: MK; etapy: B,C,D,F. Połączenia topologiczne: L09, L12, L14, L15.

Cele: L11_H1 Florek [12, 65, 106, 188]; L11_H2 brama [128, 35, 235, 178]; L11_H3 rower [252, 45, 348, 192]

### L12 — Korytarz stróżówki

Drzwi do pokoju, ciemny koniec korytarza, okno nad ławką. W nawiedzeniu światło pod drzwiami znika.

Postać: M; etapy: B,C,D. Połączenia topologiczne: L11, L13.

Cele: L12_H1 drzwi pokoju [12, 65, 106, 188]; L12_H2 okno [128, 35, 235, 178]; L12_H3 cień [252, 45, 348, 192]

### L13 — Pokój Mikołaja

Biurko po lewej, zamknięte okno centralnie, łóżko i budzik po prawej, piec w rogu. Biała koronka kontrastuje z ciemną podłogą.

Postać: M; etapy: B,C,D. Połączenia topologiczne: L12.

Cele: L13_H1 biurko [10, 28, 170, 104]; L13_H2 okno [190, 28, 350, 104]; L13_H3 łóżko [10, 119, 170, 199]; L13_H4 koronka [190, 119, 350, 199]

### L14 — Hala browaru

Kadzie i rury, mokre kamienne posadzki, małe górne okna. Żadnych elektrycznych mierników.

Postać: M; etapy: B,C. Połączenia topologiczne: L11, L15.

Cele: L14_H1 kadź [12, 65, 106, 188]; L14_H2 rura [128, 35, 235, 178]; L14_H3 ślady na podłodze [252, 45, 348, 192]

### L15 — Warsztat i skład

Stół z imadłem, kołki na ścianie, bęben liny, hak, lampa. Każde narzędzie ma osobny obrys.

Postać: MK; etapy: B,C,D,F. Połączenia topologiczne: L11, L14.

Cele: L15_H1 stół [10, 28, 170, 104]; L15_H2 lina [190, 28, 350, 104]; L15_H3 hak [10, 119, 170, 199]; L15_H4 lampa [190, 119, 350, 199]

### L16 — Dom poszkodowanego robotnika

Furtka, mała Marysia, matka w progu; w środku łóżko chorego za kotarą. Obecność Grety jedynie przez spojrzenie dziecka.

Postać: M; etapy: B. Połączenia topologiczne: L09.

Cele: L16_H1 Marysia [12, 65, 106, 188]; L16_H2 matka [128, 35, 235, 178]; L16_H3 robotnik [252, 45, 348, 192]

### L17 — Plebania

Stół, księgi i okno, proboszcz w głębi. Marianna przy drzwiach do kuchni. Spokojne jasne wnętrze.

Postać: MK; etapy: B,C,D,F. Połączenia topologiczne: L18.

Cele: L17_H1 proboszcz [12, 65, 106, 188]; L17_H2 Marianna [128, 35, 235, 178]; L17_H3 księga [252, 45, 348, 192]

### L18 — Plac przy kościele

Kościół i ławka; rozgałęzienie do pałacu i cmentarza. Krystyna czeka przy bramce tylko przed umówionym spotkaniem.

Postać: MK; etapy: B,C,D,F. Połączenia topologiczne: L09, L17, L19, L40.

Cele: L18_H1 Krystyna [12, 65, 106, 188]; L18_H2 ławka [128, 35, 235, 178]; L18_H3 drogowskaz [252, 45, 348, 192]

### L19 — Hall pałacu w Białaczowie

Schody, duże drzwi biblioteki, służący. Jasne ściany i czarne drewniane płyciny.

Postać: MK; etapy: C,D,F. Połączenia topologiczne: L18, L20, L21.

Cele: L19_H1 służący [12, 65, 106, 188]; L19_H2 drzwi biblioteki [128, 35, 235, 178]; L19_H3 schody [252, 45, 348, 192]

### L20 — Biblioteka

Pięciokątny pokój, obraz wysoko nad drzwiami, ruchoma drabina, katalog pod oknem i oznaczony regał kronik.

Postać: M; etapy: C,D. Połączenia topologiczne: L19.

Cele: L20_H1 portret [10, 28, 170, 104]; L20_H2 drabina [190, 28, 350, 104]; L20_H3 katalog [10, 119, 170, 199]; L20_H4 kronika [190, 119, 350, 199]

### L21 — Ogród pałacowy

Żywopłot przesłania rozmówców, ścieżka biegnie ku otwartemu placowi. Trzy sylwetki w kadrze podsłuchu.

Postać: MK; etapy: C,D. Połączenia topologiczne: L19.

Cele: L21_H1 żywopłot [10, 28, 170, 104]; L21_H2 Ludwik [190, 28, 350, 104]; L21_H3 Korecki [10, 119, 170, 199]; L21_H4 Krystyna [190, 119, 350, 199]

### L22 — Leśna ścieżka

Jeżyny na pierwszym planie, blady fragment tkaniny na kolcu, wydeptana ścieżka znikająca w ciemności.

Postać: MK; etapy: C,D,F. Połączenia topologiczne: L11, L23.

Cele: L22_H1 jeżyny [12, 65, 106, 188]; L22_H2 koronka [128, 35, 235, 178]; L22_H3 ścieżka [252, 45, 348, 192]

### L23 — Brzeg stawu

Nieruchoma woda, korzenie, zwalony pień po lewej i stabilny głaz po prawej. Biała koronka na wodzie; odległy brzeg tonie w czerni.

Postać: MK; etapy: C,D,F. Połączenia topologiczne: L22, L24.

Cele: L23_H1 pień [10, 28, 170, 104]; L23_H2 woda [190, 28, 350, 104]; L23_H3 głaz [10, 119, 170, 199]; L23_H4 korzenie [190, 119, 350, 199]

### L24 — Widzenie dawnego obozu

Małe ognisko, dwie szable, skórzana torba, stare naczynia. Zarys postaci za drzewami, bez obrazu przemocy seksualnej.

Postać: M; etapy: C. Połączenia topologiczne: L23.

Cele: L24_H1 ognisko [12, 65, 106, 188]; L24_H2 torba [128, 35, 235, 178]; L24_H3 światło między drzewami [252, 45, 348, 192]

### L25 — Pokój w Seroczynie

Łóżko, kufer, dzwonek, okno na park. Walizka stoi gotowa, drzwi prowadzą do pilnowanego korytarza.

Postać: K; etapy: A. Połączenia topologiczne: L26.

Cele: L25_H1 kufer [12, 65, 106, 188]; L25_H2 dzwonek [128, 35, 235, 178]; L25_H3 okno [252, 45, 348, 192]

### L26 — Korytarz Borakowskich

Trzy drzwi, stolik na korespondencję, schody do salonu. Irena blokuje główne wyjście.

Postać: K; etapy: A. Połączenia topologiczne: L25, L27, L28.

Cele: L26_H1 Irena [12, 65, 106, 188]; L26_H2 stolik [128, 35, 235, 178]; L26_H3 drzwi kuchni [252, 45, 348, 192]

### L27 — Kuchnia w Seroczynie

Stół, dzban, okno gospodarcze i dwa zamki w drzwiach. Luiza, służąca, jest odrębną osobą od matki Konstancji.

Postać: K; etapy: A. Połączenia topologiczne: L26.

Cele: L27_H1 Luiza służąca [12, 65, 106, 188]; L27_H2 dzban [128, 35, 235, 178]; L27_H3 drzwi gospodarcze [252, 45, 348, 192]

### L28 — Park Borakowskich

Gęste drzewa, ławka, ogrodzenie i furtka ku wsi. Dominuje ciemny żywopłot, nie labirynt.

Postać: K; etapy: A. Połączenia topologiczne: L26, L29.

Cele: L28_H1 furtka [12, 65, 106, 188]; L28_H2 ogrodnik [128, 35, 235, 178]; L28_H3 ławka [252, 45, 348, 192]

### L29 — Droga pod Seroczynem

Błotnista droga i wóz wieśniaka; dwór nadal widoczny. Brak bezpiecznej drogi dalszej ucieczki na tym etapie.

Postać: K; etapy: A. Połączenia topologiczne: L28.

Cele: L29_H1 wieśniak [12, 65, 106, 188]; L29_H2 wóz [128, 35, 235, 178]; L29_H3 droga [252, 45, 348, 192]

### L30 — Pokój w Sopocie

Walizka, okno na ogród, drzwi pilnowane przez Irenę. Trzy stany: przed przemocą, po interwencji Adama, otwarte okno.

Postać: K; etapy: B. Połączenia topologiczne: L31.

Cele: L30_H1 Irena [10, 28, 170, 104]; L30_H2 Adam [190, 28, 350, 104]; L30_H3 walizka [10, 119, 170, 199]; L30_H4 okno [190, 119, 350, 199]

### L31 — Ogród i Bergen Strasse

Niska skarpa, krzewy, piaszczysta uliczka i tabliczka. Widoczne przejście ku wydmom.

Postać: K; etapy: B. Połączenia topologiczne: L30, L32.

Cele: L31_H1 skarpa [12, 65, 106, 188]; L31_H2 tabliczka [128, 35, 235, 178]; L31_H3 ścieżka ku morzu [252, 45, 348, 192]

### L32 — Plaża z sieciami

Paliki, sieci, ciemne morze po prawej, molo daleko z lewej. Pies o białej sierści i czarnych łatkach w wariancie porannym.

Postać: K; etapy: B,C,F. Połączenia topologiczne: L31, L33, L34.

Cele: L32_H1 sieci [12, 65, 106, 188]; L32_H2 pies [128, 35, 235, 178]; L32_H3 linia brzegu [252, 45, 348, 192]

### L33 — Chata rybaka

Piec, ława, stół do szycia, skrzynia, małe okno. Rybak i pies; bezpieczna przestrzeń z dużą ilością bieli.

Postać: K; etapy: B,C,F. Połączenia topologiczne: L32.

Cele: L33_H1 rybak [12, 65, 106, 188]; L33_H2 stół do szycia [128, 35, 235, 178]; L33_H3 skrzynia [252, 45, 348, 192]

### L34 — Przystań rybacka

Łódź na piasku, podarte sieci, rybak sąsiad przy paliku. Horyzont morski.

Postać: K; etapy: C,F. Połączenia topologiczne: L32, L35.

Cele: L34_H1 sąsiad [12, 65, 106, 188]; L34_H2 sieć [128, 35, 235, 178]; L34_H3 łódź [252, 45, 348, 192]

### L35 — Stacja w Sopocie

Kasa, rozkład, tor z odjeżdżającym składem. Podróż do Warszawy jest przejściem fabularnym.

Postać: K; etapy: C. Połączenia topologiczne: L34, L05.

Cele: L35_H1 kasjer [12, 65, 106, 188]; L35_H2 rozkład [128, 35, 235, 178]; L35_H3 peron [252, 45, 348, 192]

### L36 — Sala weselna

Muzycy w tle, stoły, drzwi bocznego gabinetu, zegar. W wariancie uratowanej Krystyny jest to przyjęcie zaręczynowe.

Postać: K; etapy: E. Połączenia topologiczne: L02, L37.

Cele: L36_H1 Adam [12, 65, 106, 188]; L36_H2 zegar [128, 35, 235, 178]; L36_H3 drzwi gabinetu [252, 45, 348, 192]

### L37 — Gabinet przy sali

Biurko z teczką, drzwi z przeszkleniem i kredens. Rozmowa Borakowskich dociera przez uchylone drzwi.

Postać: K; etapy: E. Połączenia topologiczne: L36.

Cele: L37_H1 drzwi [12, 65, 106, 188]; L37_H2 teczka [128, 35, 235, 178]; L37_H3 biurko [252, 45, 348, 192]

### L38 — Areszt i pokój rozmów

Stół przed kratą, strażnik w głębi, Mikołaj po drugiej stronie. Po ocaleniu Krystyny ten sam pokój służy do zeznań bez krat na pierwszym planie.

Postać: MK; etapy: E,F. Połączenia topologiczne: L04, L39.

Cele: L38_H1 Mikołaj [12, 65, 106, 188]; L38_H2 strażnik [128, 35, 235, 178]; L38_H3 stół na dokumenty [252, 45, 348, 192]

### L39 — Sala rozpraw

Ława świadka, stół sądu, miejsce na dokumenty; przeciwnicy jako sylwetki w tle.

Postać: K; etapy: F. Połączenia topologiczne: L38, L08.

Cele: L39_H1 sąd [12, 65, 106, 188]; L39_H2 świadkowie [128, 35, 235, 178]; L39_H3 dokumenty [252, 45, 348, 192]

### L40 — Rodzinny grobowiec

Kamienny grobowiec, otwarte miejsce na inskrypcję Grety. W żałobnym wariancie drugi wieniec dla Krystyny.

Postać: MK; etapy: F. Połączenia topologiczne: L18.

Cele: L40_H1 płyta [12, 65, 106, 188]; L40_H2 proboszcz [128, 35, 235, 178]; L40_H3 wieniec [252, 45, 348, 192]

### L41 — Praska ulica

Mokra kostka, kałuża, przygasła witryna, Karol siedzący pod murem. Marian wyłania się z przejścia.

Postać: K; etapy: F. Połączenia topologiczne: L04, L42.

Cele: L41_H1 Karol [12, 65, 106, 188]; L41_H2 Marian [128, 35, 235, 178]; L41_H3 przejście [252, 45, 348, 192]

### L42 — Pokój Klary

Klara przy stole, dokumenty Luizy i stara fotografia. Świt za oknem.

Postać: K; etapy: F. Połączenia topologiczne: L41.

Cele: L42_H1 Klara [12, 65, 106, 188]; L42_H2 dokumenty [128, 35, 235, 178]; L42_H3 fotografia [252, 45, 348, 192]

### L43 — Gospodarstwo Mikołaja

Niewielki dom, płot i jasne pole. Marianna w progu wyłącznie w odpowiednim epilogu.

Postać: M; etapy: F. Połączenia topologiczne: L17.

Cele: L43_H1 dom [12, 65, 106, 188]; L43_H2 Marianna [128, 35, 235, 178]; L43_H3 droga [252, 45, 348, 192]

## Opisy wszystkich zasobów

### BG_L01 — bg/L01.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Ciężkie biurko po lewej, okno z tramwajem konnym w głębi, fotel gospodarza po prawej. Deszcz na szybie. Papier umowy leży na jasnym fragmencie blatu. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Korecki: [12, 65, 106, 188]; umowa: [128, 35, 235, 178]; okno: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L02 — bg/L02.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Wysokie lustro, wieszak, drzwi do gabinetu i kufer podróżny. Marian przy bocznych drzwiach. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Marian: [12, 65, 106, 188]; kufer: [128, 35, 235, 178]; drzwi: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L03 — bg/L03.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Toaletka przy oknie, mała szkatułka na stole, podróżna walizka i fotografia matki. Bez luksusowego nadmiaru drobiazgów. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: szkatułka: [12, 65, 106, 188]; fotografia Luizy: [128, 35, 235, 178]; walizka: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L04 — bg/L04.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Biurko publicysty, szuflada korespondencji, szpalty gazety. Izydor w kamizelce, puste miejsce na przekazywane dokumenty. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Izydor: [12, 65, 106, 188]; poczta: [128, 35, 235, 178]; próbna gazeta: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L05 — bg/L05.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Kasa po lewej, tablica odjazdów centralnie, wejście na peron po prawej. Para za oknem, kufry, stalowe wiązary. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: kasjer: [12, 65, 106, 188]; rozkład: [128, 35, 235, 178]; bramka: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L06 — bg/L06.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Drewniane ławki, ciężarna podróżna przy oknie, drzwi na pomost. Krystyna widoczna w osobnym kadrze rozmowy. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: podróżna: [12, 65, 106, 188]; konduktor: [128, 35, 235, 178]; drzwi na pomost: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L07 — bg/L07.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Bok maszyny, uproszczona sprężarka i trzy czytelne elementy: dopływ, zawór, przewód. Maszynista stoi z dala od mechanizmu. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: maszynista: [12, 65, 106, 188]; sprężarka: [128, 35, 235, 178]; skrzynka narzędzi: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L08 — bg/L08.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Niski budynek stacyjny, drogowskaz Wąglany, wóz przy studni. Otwarte niebo, szeroka biała przestrzeń. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: woźnica: [12, 65, 106, 188]; drogowskaz: [128, 35, 235, 178]; ławka: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L09 — bg/L09.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Mostek nad wodą, młyn w tle, po prawej brama fabryki. Las odcina horyzont zwartą czernią. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: drogowskaz: [12, 65, 106, 188]; młyn: [128, 35, 235, 178]; most: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L10 — bg/L10.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Tolek przy stole, Celina za ladą; wolne miejsce dla fotografa w etapie D. Belki, jasne naczynia na ciemnym tle. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Tolek: [12, 65, 106, 188]; Celina: [128, 35, 235, 178]; fotograf: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L10_photographer.png: fotograf przy stole i odbitka w jego dłoni

### BG_L11 — bg/L11.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Biały dawny dworek, brama, komin i niewykończony budynek. Florek obok stojaka na rowery. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Florek: [12, 65, 106, 188]; brama: [128, 35, 235, 178]; rower: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L11_day.png: praca robotników
- bg/L11_night.png: puste podwórko
- bg/L11_pumping.png: ekipa strażaków z pompą

### BG_L12 — bg/L12.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Drzwi do pokoju, ciemny koniec korytarza, okno nad ławką. W nawiedzeniu światło pod drzwiami znika. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: drzwi pokoju: [12, 65, 106, 188]; okno: [128, 35, 235, 178]; cień: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L12_normal.png: światło pod drzwiami
- bg/L12_haunted.png: czarna szczelina, blada stopa na skraju kadru

### BG_L13 — bg/L13.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Biurko po lewej, zamknięte okno centralnie, łóżko i budzik po prawej, piec w rogu. Biała koronka kontrastuje z ciemną podłogą. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: biurko: [10, 28, 170, 104]; okno: [190, 28, 350, 104]; łóżko: [10, 119, 170, 199]; koronka: [190, 119, 350, 199]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L13_day.png: bez koronki
- bg/L13_night.png: puste wnętrze, zamknięte okno
- bg/L13_sealed.png: pasek na drzwiach i nitka na oknie
- bg/L13_morning_lace.png: nienaruszone znaczniki i koronka na podłodze
- bg/L13_note.png: wiadomość K na biurku

### BG_L14 — bg/L14.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Kadzie i rury, mokre kamienne posadzki, małe górne okna. Żadnych elektrycznych mierników. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: kadź: [12, 65, 106, 188]; rura: [128, 35, 235, 178]; ślady na podłodze: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L15 — bg/L15.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Stół z imadłem, kołki na ścianie, bęben liny, hak, lampa. Każde narzędzie ma osobny obrys. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: stół: [10, 28, 170, 104]; lina: [190, 28, 350, 104]; hak: [10, 119, 170, 199]; lampa: [190, 119, 350, 199]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L16 — bg/L16.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Furtka, mała Marysia, matka w progu; w środku łóżko chorego za kotarą. Obecność Grety jedynie przez spojrzenie dziecka. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Marysia: [12, 65, 106, 188]; matka: [128, 35, 235, 178]; robotnik: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L17 — bg/L17.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Stół, księgi i okno, proboszcz w głębi. Marianna przy drzwiach do kuchni. Spokojne jasne wnętrze. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: proboszcz: [12, 65, 106, 188]; Marianna: [128, 35, 235, 178]; księga: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L18 — bg/L18.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Kościół i ławka; rozgałęzienie do pałacu i cmentarza. Krystyna czeka przy bramce tylko przed umówionym spotkaniem. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Krystyna: [12, 65, 106, 188]; ławka: [128, 35, 235, 178]; drogowskaz: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L19 — bg/L19.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Schody, duże drzwi biblioteki, służący. Jasne ściany i czarne drewniane płyciny. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: służący: [12, 65, 106, 188]; drzwi biblioteki: [128, 35, 235, 178]; schody: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L20 — bg/L20.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Pięciokątny pokój, obraz wysoko nad drzwiami, ruchoma drabina, katalog pod oknem i oznaczony regał kronik. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: portret: [10, 28, 170, 104]; drabina: [190, 28, 350, 104]; katalog: [10, 119, 170, 199]; kronika: [190, 119, 350, 199]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L20_normal.png: czysta suknia na portrecie
- bg/L20_haunted.png: podarta suknia, zaburzona twarz
- bg/L20_ladder.png: drabina pod portretem

### BG_L21 — bg/L21.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Żywopłot przesłania rozmówców, ścieżka biegnie ku otwartemu placowi. Trzy sylwetki w kadrze podsłuchu. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: żywopłot: [10, 28, 170, 104]; Ludwik: [190, 28, 350, 104]; Korecki: [10, 119, 170, 199]; Krystyna: [190, 119, 350, 199]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L21_meeting.png: trzy osoby za żywopłotem
- bg/L21_empty.png: pusty ogród

### BG_L22 — bg/L22.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Jeżyny na pierwszym planie, blady fragment tkaniny na kolcu, wydeptana ścieżka znikająca w ciemności. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: jeżyny: [12, 65, 106, 188]; koronka: [128, 35, 235, 178]; ścieżka: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L23 — bg/L23.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Nieruchoma woda, korzenie, zwalony pień po lewej i stabilny głaz po prawej. Biała koronka na wodzie; odległy brzeg tonie w czerni. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: pień: [10, 28, 170, 104]; woda: [190, 28, 350, 104]; głaz: [10, 119, 170, 199]; korzenie: [190, 119, 350, 199]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L23_calm.png: nieruchoma woda
- bg/L23_vision.png: palce przy koronce
- bg/L23_rigged.png: lina przy głazie i hak obok
- bg/L23_crisis.png: Krystyna w wodzie, twarz ponad powierzchnią
- bg/L23_saved.png: dwie postacie na brzegu
- bg/L23_aftermath.png: pusty brzeg i ludzie w tle
- bg/L23_drained.png: odsłonięte korzenie i sylwetka pod płótnem

### BG_L24 — bg/L24.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Małe ognisko, dwie szable, skórzana torba, stare naczynia. Zarys postaci za drzewami, bez obrazu przemocy seksualnej. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: ognisko: [12, 65, 106, 188]; torba: [128, 35, 235, 178]; światło między drzewami: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L25 — bg/L25.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Łóżko, kufer, dzwonek, okno na park. Walizka stoi gotowa, drzwi prowadzą do pilnowanego korytarza. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: kufer: [12, 65, 106, 188]; dzwonek: [128, 35, 235, 178]; okno: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L26 — bg/L26.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Trzy drzwi, stolik na korespondencję, schody do salonu. Irena blokuje główne wyjście. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Irena: [12, 65, 106, 188]; stolik: [128, 35, 235, 178]; drzwi kuchni: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L27 — bg/L27.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Stół, dzban, okno gospodarcze i dwa zamki w drzwiach. Luiza, służąca, jest odrębną osobą od matki Konstancji. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Luiza służąca: [12, 65, 106, 188]; dzban: [128, 35, 235, 178]; drzwi gospodarcze: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L28 — bg/L28.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Gęste drzewa, ławka, ogrodzenie i furtka ku wsi. Dominuje ciemny żywopłot, nie labirynt. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: furtka: [12, 65, 106, 188]; ogrodnik: [128, 35, 235, 178]; ławka: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L29 — bg/L29.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Błotnista droga i wóz wieśniaka; dwór nadal widoczny. Brak bezpiecznej drogi dalszej ucieczki na tym etapie. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: wieśniak: [12, 65, 106, 188]; wóz: [128, 35, 235, 178]; droga: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L30 — bg/L30.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Walizka, okno na ogród, drzwi pilnowane przez Irenę. Trzy stany: przed przemocą, po interwencji Adama, otwarte okno. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Irena: [10, 28, 170, 104]; Adam: [190, 28, 350, 104]; walizka: [10, 119, 170, 199]; okno: [190, 119, 350, 199]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L30_guarded.png: Irena przy łóżku
- bg/L30_escape.png: otwarte okno i Adam za nim
- bg/L30_aftermath.png: przewrócone krzesło, ciemna plama, bez zbliżenia zwłok

### BG_L31 — bg/L31.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Niska skarpa, krzewy, piaszczysta uliczka i tabliczka. Widoczne przejście ku wydmom. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: skarpa: [12, 65, 106, 188]; tabliczka: [128, 35, 235, 178]; ścieżka ku morzu: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L32 — bg/L32.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Paliki, sieci, ciemne morze po prawej, molo daleko z lewej. Pies o białej sierści i czarnych łatkach w wariancie porannym. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: sieci: [12, 65, 106, 188]; pies: [128, 35, 235, 178]; linia brzegu: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L32_storm.png: wiatr i sieci
- bg/L32_dawn.png: pies przy sieciach
- bg/L32_peace.png: spokojne morze

### BG_L33 — bg/L33.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Piec, ława, stół do szycia, skrzynia, małe okno. Rybak i pies; bezpieczna przestrzeń z dużą ilością bieli. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: rybak: [12, 65, 106, 188]; stół do szycia: [128, 35, 235, 178]; skrzynia: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L33_alive.png: rybak przy stole
- bg/L33_empty.png: puste krzesło, pies przy progu

### BG_L34 — bg/L34.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Łódź na piasku, podarte sieci, rybak sąsiad przy paliku. Horyzont morski. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: sąsiad: [12, 65, 106, 188]; sieć: [128, 35, 235, 178]; łódź: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L35 — bg/L35.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Kasa, rozkład, tor z odjeżdżającym składem. Podróż do Warszawy jest przejściem fabularnym. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: kasjer: [12, 65, 106, 188]; rozkład: [128, 35, 235, 178]; peron: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L36 — bg/L36.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Muzycy w tle, stoły, drzwi bocznego gabinetu, zegar. W wariancie uratowanej Krystyny jest to przyjęcie zaręczynowe. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Adam: [12, 65, 106, 188]; zegar: [128, 35, 235, 178]; drzwi gabinetu: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L36_wedding.png: welon K, weselny stół
- bg/L36_reception.png: K w zwykłej sukni, brak symboli ślubu

### BG_L37 — bg/L37.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Biurko z teczką, drzwi z przeszkleniem i kredens. Rozmowa Borakowskich dociera przez uchylone drzwi. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: drzwi: [12, 65, 106, 188]; teczka: [128, 35, 235, 178]; biurko: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L38 — bg/L38.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Stół przed kratą, strażnik w głębi, Mikołaj po drugiej stronie. Po ocaleniu Krystyny ten sam pokój służy do zeznań bez krat na pierwszym planie. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Mikołaj: [12, 65, 106, 188]; strażnik: [128, 35, 235, 178]; stół na dokumenty: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L38_arrest.png: krata między bohaterami
- bg/L38_statement.png: rozmowa przy stole, bez kraty

### BG_L39 — bg/L39.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Ława świadka, stół sądu, miejsce na dokumenty; przeciwnicy jako sylwetki w tle. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: sąd: [12, 65, 106, 188]; świadkowie: [128, 35, 235, 178]; dokumenty: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L40 — bg/L40.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Kamienny grobowiec, otwarte miejsce na inskrypcję Grety. W żałobnym wariancie drugi wieniec dla Krystyny. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: płyta: [12, 65, 106, 188]; proboszcz: [128, 35, 235, 178]; wieniec: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L40_two.png: wieńce Grety i Krystyny
- bg/L40_one.png: wieniec Grety, Krystyna wśród żałobników

### BG_L41 — bg/L41.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Mokra kostka, kałuża, przygasła witryna, Karol siedzący pod murem. Marian wyłania się z przejścia. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Karol: [12, 65, 106, 188]; Marian: [128, 35, 235, 178]; przejście: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L41_ruined.png: Karol pod ścianą
- bg/L41_warned.png: Karol stojący przy wejściu

### BG_L42 — bg/L42.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Klara przy stole, dokumenty Luizy i stara fotografia. Świt za oknem. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Klara: [12, 65, 106, 188]; dokumenty: [128, 35, 235, 178]; fotografia: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L43 — bg/L43.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Niewielki dom, płot i jasne pole. Marianna w progu wyłącznie w odpowiednim epilogu. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: dom: [12, 65, 106, 188]; Marianna: [128, 35, 235, 178]; droga: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L43_alone.png: M w progu
- bg/L43_marianna.png: Marianna w progu
- bg/L43_together.png: M i K obok siebie

### ICON_I01 — items/I01.png

24×24. Złożony arkusz, podpis i pieczęć. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I02 — items/I02.png

24×24. Wąski kartonik z wyciętym narożnikiem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I03 — items/I03.png

24×24. Symetryczny motyl, jasne skrzydła i czarny owal pośrodku. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I04 — items/I04.png

24×24. Duży klucz o otwartej szczęce. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I05 — items/I05.png

24×24. Złożona tkanina z ciemnym rogiem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I06 — items/I06.png

24×24. Owalny portret kobiety na prostokątnym kartoniku. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I07 — items/I07.png

24×24. Składany papier z widoczną pieczęcią. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I08 — items/I08.png

24×24. Prostokątny neseser z uchwytem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I09 — items/I09.png

24×24. Jasny dzban z czarnym uchwytem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I10 — items/I10.png

24×24. Dwa czyste arkusze. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I11 — items/I11.png

24×24. Gruby ukośny ołówek. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I12 — items/I12.png

24×24. Mały klucz z okrągłym uchem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I13 — items/I13.png

24×24. Trzy różne klucze na kółku. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I14 — items/I14.png

24×24. Księga z krzyżem na okładce. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I15 — items/I15.png

24×24. Kartka z trzema krótkimi liniami. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I16 — items/I16.png

24×24. Szpulka z odwiniętym końcem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I17 — items/I17.png

24×24. Krótka świeca i bryłka. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I18 — items/I18.png

24×24. Długi cienki pasek z zagięciem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I19 — items/I19.png

24×24. Nieregularny biały fragment z trzema czarnymi oczkami. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I20 — items/I20.png

24×24. Mała karta z inicjałem K. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I21 — items/I21.png

24×24. Karta z dużym III i 27. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I22 — items/I22.png

24×24. Rzeka jako krzywa, staw jako owal, krzyżyk przy trakcie. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I23 — items/I23.png

24×24. Szkic uskoku i splątanych korzeni. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I24 — items/I24.png

24×24. Zwinięty materiał o grubym rastrze. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I25 — items/I25.png

24×24. Powiększona igła i pętla nici. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I26 — items/I26.png

24×24. Prosty strój bez krynoliny i koronek. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I27 — items/I27.png

24×24. Mały kartonik z symbolem koperty. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I28 — items/I28.png

24×24. Zamknięta potem otwarta koperta. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I29 — items/I29.png

24×24. Sakiewka i dwie monety. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I30 — items/I30.png

24×24. Dwie stojące osoby i tło straganu. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I31 — items/I31.png

24×24. Zwinięty zwój z czytelnym końcem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I32 — items/I32.png

24×24. Długi trzonek i łagodny hak. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I33 — items/I33.png

24×24. Elegancka karta z ramką. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I34 — items/I34.png

24×24. Tabela i duży podpis na dole. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I35 — items/I35.png

24×24. Arkusz z podpisem i zagiętym rogiem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I36 — items/I36.png

24×24. Arkusz z małą pieczęcią. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I37 — items/I37.png

24×24. Teczka z wystającą mapą. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I38 — items/I38.png

24×24. Dwa węże, uszczelka i pompa ręczna. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I39 — items/I39.png

24×24. Prosty podpisany arkusz. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I40 — items/I40.png

24×24. Dwie kartki o sprzecznych datach i fotografia. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I41 — items/I41.png

24×24. Krótki walec z osadem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I42 — items/I42.png

24×24. Gruby rozwidlony konar na suchym brzegu. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I43 — items/I43.png

24×24. Kartka z prostym podpisem K. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I44 — items/I44.png

24×24. Podpisany arkusz z inicjałami. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I45 — items/I45.png

24×24. Otwarta koperta z piórem obok. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### POR_M — portraits/M.png

48×48. Mikołaj Goworek: młody dorosły mężczyzna, szczupła twarz, falowane ciemne włosy, skromna marynarka i koszula; bez narzucania podobieństwa do osoby rzeczywistej. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_K — portraits/K.png

48×48. Konstancja Korecka: młoda dorosła kobieta, ciemne włosy upięte, wyraźne oczy i zdecydowane spojrzenie; strój początkowo elegancki, potem prosty. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_KR — portraits/KR.png

48×48. Krystyna: młoda dorosła hrabianka, upięte włosy, strój do jazdy konnej, pewne spojrzenie; w późniejszych scenach skrucha. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_GR — portraits/GR.png

48×48. Greta von Platter: dorosła kobieta w historycznej koronkowej sukni, długie ciemne włosy; wersja portretowa pogodna, zjawa wyniszczona, nie erotyzowana. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_KA — portraits/KA.png

48×48. Karol Korecki: dojrzały zamożny mężczyzna, szeroka sylwetka, wąs, kamizelka, twardy wyraz twarzy. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_IZ — portraits/IZ.png

48×48. Izydor Jelinek: dojrzały publicysta, schludny zarost, kamizelka, czujne zmęczone oczy. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_MA — portraits/MA.png

48×48. Marian: starszy służący, skromny ubiór, łagodne oczy i wyprostowana sylwetka. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_FL — portraits/FL.png

48×48. Florek: starszy brygadzista, maciejówka, wąs, robocza kurtka, pogodna lecz zmęczona twarz. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_AD — portraits/AD.png

48×48. Adam Borakowski: młody dorosły, staranny ubiór, gładka twarz, zmienny uśmiech. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_EL — portraits/EL.png

48×48. Eleonora Borakowska: dojrzała kobieta o spiętej twarzy, surowa fryzura, ciężka suknia. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_IR — portraits/IR.png

48×48. Irena: dorosła służąca, gładko spięte włosy, fartuch i nieruchome spojrzenie. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_RY — portraits/RY.png

48×48. Rybak: sędziwy mężczyzna, broda, grube brwi, wełniany sweter, czapka. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_PR — portraits/PR.png

48×48. Proboszcz: dojrzały ksiądz, sutanna, spokojna twarz. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_MI — portraits/MI.png

48×48. Marianna: dorosła kobieta w prostym stroju kuchennym, spokojny wyraz twarzy, bez idealizacji. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_KL — portraits/KL.png

48×48. Klara: dojrzała kobieta, miękkie rysy, prosta elegancka suknia. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_LU — portraits/LU.png

48×48. Ludwik: dojrzały hrabia, bokobrody, surdut i staranny kołnierz. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_TO — portraits/TO.png

48×48. Tolek: dorosły karczmarz, wąs, podwinięte rękawy. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_CE — portraits/CE.png

48×48. Celina: dorosła gospodyni w fartuchu, czujne spojrzenie. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_MY — portraits/MY.png

48×48. Marysia: mała dziewczynka z jasnymi warkoczykami, zwykły dziecięcy strój, ciekawość. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_LS — portraits/LS.png

48×48. Luiza służąca: dorosła kobieta w roboczym fartuchu; nie przypomina portretu matki Konstancji. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_BO — portraits/BO.png

48×48. Borakowski senior: dojrzały mężczyzna w surducie, ciężkie brwi; zawsze ubrany w ilustracjach gry. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_RO — portraits/RO.png

48×48. Ranny robotnik: dorosły mężczyzna odpoczywający na łóżku, blada twarz. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_MT — portraits/MT.png

48×48. Matka Marysi: dorosła kobieta z chustką i śladem mąki na fartuchu. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_SN — portraits/SN.png

48×48. Sąsiad rybaka: dojrzały mężczyzna, czapka, roboczy sweter. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_FO — portraits/FO.png

48×48. Fotograf: dorosły mężczyzna, futerał z odbitkami pod pachą. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_ME — portraits/ME.png

48×48. Maszynista: dorosły mężczyzna w roboczej czapce i kurtce. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_WO — portraits/WO.png

48×48. Woźnica: dorosły mężczyzna w płaszczu z wysokim kołnierzem. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_OG — portraits/OG.png

48×48. Ogrodnik: dorosły mężczyzna w kapeluszu i fartuchu. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_SD — portraits/SD.png

48×48. Sędzia: starszy urzędnik za stołem, powściągliwa twarz. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_ST — portraits/ST.png

48×48. Strażnik: dorosły mężczyzna w umownym mundurze epoki; bez wymyślonych szczegółowych insygniów. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_SL — portraits/SL.png

48×48. Służący pałacowy: dorosły mężczyzna w schludnym ciemnym ubraniu. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_KS — portraits/KS.png

48×48. Kasjer: dorosły urzędnik za okienkiem. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_KN — portraits/KN.png

48×48. Konduktor: dorosły kolejarz w czapce. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_PD — portraits/PD.png

48×48. Podróżna: dorosła ciężarna kobieta w skromnym płaszczu. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### Z01 — closeups/Z01.png

360×208. Portret Grety. Pełny portret z czytelnym pasem koronki na dole; alternatywa z podartą suknią i zranioną twarzą. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z02 — closeups/Z02.png

360×208. Zawór. Korpus, pokrywa, wkład: trzy oddzielne duże części, wyraźny osad; wariant czysty. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z03 — closeups/Z03.png

360×208. Katalog. Szufladka P, karta Platter, trzy pola: tom III, karta 27, Mapa dóbr. Litery renderuje silnik. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z04 — closeups/Z04.png

360×208. Mapa. Trakt, rzeka, młyn, staw; cztery duże symbole, legenda renderowana tekstem. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z05 — closeups/Z05.png

360×208. Sieć. Trzy luźne końce, trzy sąsiednie poprawne oczka jako przykład; warianty po pierwszym i drugim połączeniu. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z06 — closeups/Z06.png

360×208. Pompa. Dwa węże z oznaczeniami A i B, odpowiadające gniazda, duża uszczelka; tekst nakładany przez silnik. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z07 — closeups/Z07.png

360×208. Fotografia jarmarku. Mikołaj i Krystyna obok straganu, zwykła rozmowa, brak fizycznego znaku zaręczyn. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z08 — closeups/Z08.png

360×208. Dokument. Wspólna ramka papieru, niewielka pieczęć; pełną treść wyświetla silnik, nie generować drobnych pseudo-liter. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z09 — closeups/Z09.png

360×208. Fotografia matki. Owalny portret Luizy, matki Konstancji, dorosła kobieta w eleganckiej sukni. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z10 — closeups/Z10.png

360×208. Tytuł. Słowo PROCH renderowane silnikiem; sylwetka dworu i stawu, motyw białej koronki w rogu. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.
