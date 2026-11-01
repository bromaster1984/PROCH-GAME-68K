# PROCH — techniczna specyfikacja wykonawcza

## Podstawa narzędziowa i granice weryfikacji

Sprawdzono dokumentację 1 listopada 2026: Retro68 jest środowiskiem cross-kompilacji dla klasycznych Macintoshy 68K/PPC, z CMake, Rez i przykładami aplikacji. Jego repozytorium zawiera Multiversal Interfaces; projekt ostrzega o ich niekompletności. Mini vMac ma wariant SE; wariant standardowy emuluje Plus, więc sam start w domyślnym emulatorze nie dowodzi testu SE. To uzasadnia wybór narzędzi, nie jest testem gry.

Źródła: https://github.com/autc04/Retro68 ; https://minivmac.github.io/gryphel-mirror/c/minivmac/options.html . Przypnij rewizję na początku implementacji i użyj jej przykładów CMake zamiast zgadywać nazwy targetów. Nie instalowano ani nie uruchamiano tych narzędzi przy tworzeniu niniejszego dokumentu.

## Kod

C z małą warstwą platformową Mac Toolbox/monochrome QuickDraw; C++ dopuszczalne tylko bez RTTI, wyjątków i ciężkiego runtime. Ustaw kompilację 68000, żadnych instrukcji 68020/030, FPU, Color QuickDraw, QuickTime lub API wyłącznie System 7. Identyfikatory i flagi w liczbach całkowitych, stałe tablice indeksów, bez alokacji podczas każdego kliknięcia. Standardowe typy u16/s16/u32/s32 o zweryfikowanym rozmiarze. Serializacja pól jawnie, nie zapis surowych struktur C zależnych od paddingu.

Podział: platform_mac (zdarzenia, pliki, okna), render_1bit, ui, engine (reguły), world, dialogs, save, audio, content. engine działa również na hoście bez Toolbox. Źródłowy JSON/UTF-8 kompilowany na hoście do tablic/reguł i binarnych pakietów. Runtime nie potrzebuje parsera JSON.

## Ekran i operowanie

Układ w globalnych współrzędnych 512×342, prostokąty [x,y,width,height]:

- pasek menu [0,0,512,20]; Plik: Nowa/Wczytaj/Zapisz/Zapisz jako/Wyjście; Gra: Dziennik/Podpowiedź/Opcje; Pomoc: Sterowanie/O grze;
- rama sceny [4,23,364,226], obszar grafiki [6,39,360,208]; tytuł lokacji maksymalnie 46 znaków, dłuższy w dymku lub opisie;
- postać [372,23,136,102], portret [378,42,48,48], imię obok; przycisk przełączania [378,96,124,20]; poniżej imienia mały tekst Mikołaj/Konstancja, bez skrótów niezrozumiałych dla gracza;
- zakładki Ekwipunek/Przejścia [372,129,136,120], 3×3 sloty ikon 24×24 z odstępem 12, przewijanie przy większej liczbie; nazwa zaznaczonego przedmiotu w logu; pojemniki jako okna modalne z własną siatką, Escape zamyka;
- narracja [4,253,504,43], trzy linie po 12 px; dłuższe komunikaty w przewijanym oknie historii, nigdy obcięte bez możliwości odczytu;
- osiem komend w dwóch rzędach: x=4,132,260,388; y=300 i 322; w=120, h=18. Rząd 1 Obejrzyj/Otwórz/Zamknij/Użyj. Rząd 2 Rozmawiaj/Idź/Uderz/Spożyj.

Brak skalowania na SE. Menu i ramki można rysować we własnym oknie aplikacji dla spójności; funkcje plikowe przez standardowe mechanizmy Toolbox. Nie używać wielkiego portretu z poglądowego obrazka kosztem tekstu.

Klik komenda, potem obiekt. Użyj: wybierz źródło, potem cel. Przeciągnięcie do ekwipunku = weź, poza ekwipunek na dozwolony stół = odłóż, na obiekt = użyj. Podwójne kliknięcie = obejrzyj, pojemnik = otwórz. Jednoprzyciskowa mysz, nie wymaga prawego przycisku. Escape anuluje wybór; Tab przełącza postać poza blokadą; Command-S zapis; Command-O wczytaj. Każda funkcja dostępna myszą. Po przełączeniu odtwarzaj lokację, zakładkę i ekwipunek danej osoby; wyczyść niedokończone „użyj”, żeby nie połączyć cudzych przedmiotów.

## Polskie znaki

Teksty autorskie UTF-8. Nie zakładaj, że podstawowy Chicago na angielskim Systemie 6 ma wszystkie polskie litery. Dołącz własną bitmapową czcionkę gry: 6×11 px komórka, 7 px advance, 12 px line-height, czytelne ogonki. ASCII 0x20–0x7E, dalej jawna tabela: 0x80–0x91 = ĄąĆćĘęŁłŃńÓóŚśŹźŻż. Dodatkowe znaki typograficzne normalizuj przy kompilacji do prostych cudzysłowów i myślnika. Nie mapuj ogonków na obce symbole. Atlas 1-bit + maska do CopyBits. Font i dokument mapowania w repo. Błąd kompilacji przy nieznanym znaku, nie cicha utrata liter. Tytuły, dialogi i dzienniki własnym fontem. Nazwy plików danych ASCII. Tekst zapisu użytkownika konwertuj jawnie lub użyj automatycznych nazw Save01.

## Bitmapy i pamięć

360×208: rowBytes wyrównane do 16 bitów = 46, bufor 9568 B. Pełny ekran 512×342 = 64×342 = 21888 B, bez nagłówków. Maski mają ten sam stride co odpowiadające bitmapy. Bit 1 oznacza czerń w formacie runtime; konwerter musi to sprawdzić na wzorcu szachownicy. Źródłowe PNG mogą mieć inne kodowanie, nie wczytuj PNG na Macu.

Proponowany budżet aplikacji, do potwierdzenia w prototypie: partition minimum 1536 KiB, preferred 2048 KiB. W tej puli: kod i stałe do 700 KiB, stan/teksty indeksy do 160 KiB, UI/fonty/render do 180 KiB, cache scen/portretów do 256 KiB, bufor audio do 64 KiB, reszta rezerwa sterty i stosu. To limity projektowe, nie pomiar. Jeśli build przekracza budżet, usuń niepotrzebny runtime/cache, nie zwiększaj potajemnie minimum sprzętu. System też zajmuje RAM; test 4 MB fizycznie jest obowiązkowy.

W RAM bieżąca scena, jej maski i mały LRU; po przełączeniu wolno wczytać drugą lokację z dysku. Prefetch tylko małych potrzebnych wariantów. Nie trzymaj pełnych grafik całej gry. Pełne odrysowanie tylko przy zmianie sceny; ruch myszy i selekcja przez dirty rects. Brak ciągłego render loop. Systemowe zdarzenia obsługuj regularnie, nie zawieszaj komputera w oczekiwaniu na klawisz.

## Format zasobów

Pakiety danych na etapy lub regiony, nazwy ASCII <=31 znaków. Każdy: magic PRPK, version u16, count u16, tabela [id u16, kind u16, offset u32, packedLen u32, unpackedLen u32, crc32 u32], big endian. Pozycje liczone od początku pliku. Bitmapa payload: width u16, height u16, rowBytes u16, codec u16, bytes. codec=0 surowe; codec=1 PackBits wierszami z długością u16 przed każdym wierszem. Parser kontroluje granice, nadmiar dekodowanych bajtów, CRC i nieznane wersje. Pierwsza implementacja może używać wyłącznie codec=0, kompresja nie jest warunkiem jakości.

Teksty: osobny pakiet indeksowany id, każdy rekord długość u16 plus tekst w kodowaniu fontu. Reguły skompilowane na hoście; żadnych dowolnych skryptów eval. Wszystkie zasoby mają manifest z sumami kontrolnymi. Nie pakuj całej gry w jeden wielki resource fork. Resource fork aplikacji zawiera elementy wymagane przez platformę, zasoby gry mogą być w data fork pakietów.

## Zapis

Magic PRSV, version u16, contentVersion u16, payloadLen u32, CRC32 u32, payload. Jawna serializacja stanu z 03. Nie zapisuj wskaźników. Najpierw plik tymczasowy, sprawdzenie zapisu, zachowanie starego jako .bak, dopiero zastąpienie. Przy błędzie dysku stary zapis pozostaje. Kontrola zgodności wersji z czytelnym błędem. Zapis musi odtwarzać oba ekwipunki, otwarte pojemniki, transfery listów, wiedzę, substeps, strój K, zakończenia opcjonalnych zadań i stan ratunku. Dźwięk i pozycja kursora nie są częścią logiki.

## Dźwięk i animacja

Wydanie ma działać w ciszy. Minimum: krótkie efekty mono drzwi, klucza, kroków, wiatru, wody, zegara i pociągu. 8-bit PCM, bez długiego streamingu i miksowania wielu kanałów. API odtwarzania dobierz i zweryfikuj na SE/System6; nie zakładaj istnienia nowszych funkcji. Jeśli wybrana implementacja blokuje UI, skróć efekt lub odtwarzaj asynchronicznie w obsługiwany sposób. Opcja wyciszenia. Muzyka tylko krótki motyw tytułowy; nie obowiązuje ciągła muzyka w lokacjach.

Manifest dźwięków: S01 door.wav (drewniane drzwi, 0.6s), S02 key.wav (klik i brzęk, 0.4s), S03 steps.wav (dwa kroki po deskach, 0.7s), S04 wind.wav (podmuch, 1.5s), S05 water.wav (chlupot, 1s), S06 clock.wav (pojedynczy takt, 0.2s), S07 train.wav (para i krótki stuk, 1.5s), S08 net.wav (szelest sieci, 0.4s), S09 page.wav (kartka, 0.3s), S10 pump.wav (dwa uderzenia pompy, 0.8s), S11 bell.wav (odległy dzwon, 1.5s), S12 title.wav (własny krótki motyw, maks. 6s, opcjonalny). Samodzielne generowanie efektów lub legalne własne nagrania; nie kopiować dźwięków MacVenture. Limit bufora 64 KiB wymaga podziału dłuższego motywu albo jego pominięcia na SE.

Animacje: 2–3 klatki wariantu portretu, 2 klatki zmarszczki wody, miganie ognia maks. 2 Hz; tylko małe obszary. Brak błysków pełnego ekranu. Wyłączenie animacji pozostawia czytelny stan końcowy. Nie uzależniaj wyniku zadania od FPS.

## Dystrybucja i test celu

Wolumin HFS z aplikacją i folderem Data jest rozsądnym nośnikiem dystrybucji. Rozmiar dobrać do finalnych zasobów z zapasem, np. 32 MiB jako punkt startowy, nie twarde ograniczenie gry. Zachowaj resource fork i Finder type/creator. ZIP zwykłego pliku APPL bez forków nie jest poprawnym dostarczeniem. Dla BlueSCSI najbezpieczniej dostarczyć pliki do skopiowania na istniejący działający dysk użytkownika oraz osobno przetestowany format obrazu, jeśli zostanie zbudowany. Nie obiecuj bootowalności dowolnego .dsk.

Mac SE 68000, 4 MB, System 6.0.8 to test wymagany. SE/30 System 7 to osobny test, nie zamiennik. Bez fizycznego sprzętu raportuj emulację. Nie stwierdzaj „działa na SE”, jeśli sprawdzono tylko hostowy engine. Na prawdziwym SE zmierz zmianę lokacji i reakcję na klik; cele <=2 s z dysku i <=150 ms dla prostego UI są celami testowymi, nie obietnicą z dokumentacji.
