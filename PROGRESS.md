# PROCH — postęp implementacji

## Cel i zasady wznowienia

Natywna aplikacja Motorola 68000, Macintosh SE, 4 MB RAM, System 6.0.8,
512×342, 1-bit. Bez wersji przeglądarkowej. Host służy do budowania i testów.
Specyfikacja znajduje się w katalogu głównym repozytorium, zaczynając od
`00_START_DLA_CODEXA.md` (nie w podkatalogu `PROCH_Codex_v1`).

Po przerwie: przeczytać ten plik, sprawdzić `git status`, bieżący kod i raport
testów, następnie kontynuować od ostatniego etapu. Nie tworzyć nowego worktree
bez polecenia użytkownika. Zachować rozdzielenie kompilacji, testów hostowych,
emulacji i rzeczywistego sprzętu.

Gałąź implementacji: `codex/proch-mac-se`. Baza specyfikacji: `c0458e1`.

## 2026-11-01 — etap 0: pobranie specyfikacji i rozpoznanie

Wykonano:
- pobrano aktualny `origin/main` i utworzono osobną gałąź;
- rozpoznano wymagania platformowe, etapy, stan dwóch postaci i plan testów;
- sprawdzono narzędzia hosta: dostępne Git, GCC/G++, Make, Python i Docker;
  brak Retro68, CMake oraz emulatora w PATH;
- wybrano oficjalny Retro68 i otwarte Multiversal Interfaces; trwa pobieranie
  narzędzi. Kandydat rewizji źródeł: `2aa5c87e88771c6057f52bf830af9d440a5e4e36`.

Przetestowano:
- `python3 validate_spec.py`: PASS — 40 Q, 43 lokacje, 45 przedmiotów,
  132 bazowe wpisy grafik, 174 pliki ilustracji z wariantami;
- `git fetch origin`: PASS po przyznaniu uprawnień wykonania sieciowego;
- zarządzany Docker: dostępny, 28.4.0, sterownik vfs;
- przed rozpoczęciem zmian katalog roboczy był czysty.

Problemy i granice:
- początkowy błąd proxy wynikał z ograniczeń wykonania; pobranie Git działa
  przez istniejące uwierzytelnienie i proxy, bez nowego tokenu;
- walidator specyfikacji nie testuje silnika ani aplikacji;
- aplikacji jeszcze nie skompilowano, żadne Q nie jest zaimplementowane;
- nie znaleziono skonfigurowanego środowiska SE z legalnym ROM-em/Systemem 6.0.8.

Następny krok: przypiąć działający toolchain i zbudować minimalną aplikację
68000 z oknem, rysowaniem monochromatycznym oraz obsługą myszy. Potem techniczny
wycinek Q09/Q12 i Konstancji w L33. Nie oznaczać zgodności SE po samym buildzie.

Synchronizacja: ten zapis ma zostać wysłany natychmiast po commicie; wynik
potwierdza polecenie `git push`, a nie sam lokalny commit.

## 2026-11-01 — etap 1a: pierwszy build aplikacji 68000

Wykonano: CMake Retro68, aplikacja Toolbox w C, okno o geometrii docelowej,
monochromatyczny bufor sceny 360×208/46 B na wiersz, zachowywanie kliknięć
w buforze, obsługa menu i wyjścia. Pętla zdarzeń usypia przez WaitNextEvent,
odrysowuje tylko po unieważnieniu. Powstały MacBinary i wolumin HFS w `dist/`.
Dodano `README_PL.md`, `TEST_REPORT.md`, lock narzędzi i testy renderera/forków.

Testy: build z ostrzeżeniami jako błędami PASS; C host ASan/UBSan PASS;
5 testów struktury pakietu PASS; walidator specyfikacji PASS. Wyniki i granice
w raporcie. To wzorzec diagnostyczny, nie ilustracja ani gra.

Problemy: build toolchaina ze źródeł jest nadal wykonywany poza repozytorium.
Oficjalny bootstrap jest przypięty digestem; jego SHA źródeł nie jest podane
w metadanych. Nie przedstawiać obrazu jako kompilacji wybranego SHA.
Nie potwierdzono jeszcze uruchomienia aplikacji. Brakuje dostarczonego ROM-u SE
i obrazu Systemu 6.0.8; poproszono o ścieżki, bez zatrzymywania prac hostowych.

Następny krok: uruchomić test Toolbox w Executor 2000 (osobny wynik, nie SE),
dokończyć toolchain ze źródeł, przebudować aplikację i rozpocząć wycinek Q09/Q12.
Pierwszy zapis etapu 0 został wysłany na GitHub: `0b03963`.

## 2026-11-01 — etap 1b / początek 2: uruchomienie Toolbox i reguły demonstracji

Wykonano:
- testowa odmiana aplikacji sprawdza rzeczywisty CopyBits/GetPixel, geometrię
  okna i funkcję obsługi kliknięcia, zapisuje framebuffer QuickDraw do PBM;
- zrzut `screenshots/etap1-executor2000.png` to bezstratna konwersja ekranu
  testowego 512×342, 1-bit (bez rekonstrukcji i retuszu);
- dodano skrypty budowania toolchaina/aplikacji i testu Toolbox;
- rozpoczęto engine C: niezależne miejsca, własność przedmiotów, wiedza,
  dzienniki i przełączanie. Deterministyczne reguły demonstracyjne Q09/Q12
  oraz Q21 w L33. To mieszana fixture etapów do testów, nie początek kampanii.
  Engine nie jest jeszcze podłączony do interfejsu natywnego;
- scalono `origin/main` z materiałami `MAC PLUS` dostarczonymi przez autora.

Testy:
- Executor 2000 v0.1.0, 4M, applzone 2M, 512×342, bpp1:
  `PROCH_TOOLBOX_SMOKE_PASS`. Wywołanie kliknięcia jest syntetyczne; rzeczywista
  jednoprzyciskowa obsługa myszy wymaga osobnego testu emulatora;
- test hostowy engine C + ASan/UBSan: PASS. Pełne demonstracyjne Q09/Q12/Q21,
  przełączanie po każdej czynności, wcześniejsze podnoszenie, opcjonalna Biblia,
  brak współdzielenia ekwipunku/wiedzy, brak duplikacji nagród i wpisów;
- zapisany `build_mac.sh bootstrap ON`: PASS;
- ROM dostarczony jako Mac-Plus.ROM ma 7504 dodatkowe bajty. Osobną kopię
  pierwszych 128 KiB zweryfikowano oryginalną sumą ROM 0x4d1f8172;
- obraz DiskCopy 4.2 rozpakowano poza repozytorium po sprawdzeniu sumy danych
  0x816f85c8. Pliki źródłowe pozostały niezmienione.

Problemy: to ROM Macintosh Plus, nie SE. Trwa budowanie Mini vMac Plus/4 MB
oraz kończenie własnego toolchaina. Nie ogłaszamy jeszcze zgodności System 6.
Font PL i kompletne UI pozostają do zrobienia, podobnie reszta kampanii.

Następny krok: Mini vMac Plus + dostarczony System 6.0.8, uruchomienie aplikacji
i rzeczywiste kliknięcia; zakończyć build narzędzi i powtórzyć natywne testy.
Następnie font PL i podłączenie reguł demonstracji do interfejsu.
Etap 1a wysłany na GitHub: `82500fd`.

## 2026-11-01 — etap 1c: przypięty toolchain i test na Systemie 6.0.8; font PL

Wykonano:
- ukończono budowę Retro68 `2aa5c87e88771c6057f52bf830af9d440a5e4e36`
  i Multiversal `580f3309649ad4c788c048be3dff2416d7ba49f3` ze źródeł,
  bez PPC/Carbon. Naprawiono prawa odczytu wygenerowanego Multiverse.r;
- zapisane skrypty `build_mac.sh source OFF` i `test_toolbox.sh source`
  uruchomiono pomyślnie. Cache przypiętego toolchaina jest ponownie używany;
- zbudowano Mini vMac `6860a9a7f372c461b25dc42974b191a453ebcfb2`, Plus,
  4 MB, X11, bez powiększenia. System faktycznie potwierdzony oknem Findera:
  System 6.0.8, Finder 6.1.8, Total Memory 4096K;
- aplikacja uruchomiła się z HFS, zareagowała na rzeczywiste kliknięcie
  (wszystkie 49 pikseli pędzla 7×7 odwrócone), Command-Q wróciło do Findera;
- własne oryginalne glify 6×11, przesunięcie 7, interlinia 12, atlas i maska
  1-bit, ASCII + komplet 18 polskich liter. Tytuły i próbka w aplikacji są
  rysowane tym fontem przez CopyBits. Kompilator etykiet UTF-8 nie zastępuje
  nieznanych znaków; mapowanie opisuje `FONT_PL.md`;
- dodano narzędzia weryfikacji wejść emulatora oraz bezstratnych zrzutów.
  `dist/` zawiera tylko aplikację i jej wolumin, bez ROM-u/systemu.

Testy:
- MC68000, ELF32 big endian, flagi `m68000`, potwierdzone readelf;
- kompilacja C/Rez i MacBinary/HFS: PASS;
- Executor 2000, najnowszy font: `PROCH_TOOLBOX_SMOKE_PASS`;
- testy hostowe C ASan/UBSan renderera i reguł demonstracji: PASS;
- 9 testów Python struktury aktualnego `dist/`, fontu, konwersji i błędnego
  kodowania: PASS. Powtarzalna generacja nagłówków/atlasu;
- zrzuty 512×342/1-bit: Plus/System 6, próbka PL oraz informacje systemowe.

Ograniczenia: testowany był Plus, nie SE. Etap 1 nie ma jeszcze wymaganej
weryfikacji SE/4 MB; potrzebny ROM SE. Nie testowano SE/30/System7 ani sprzętu.
Nie mierzono wydajności i maksymalnej sterty po 200 przejściach. Dziewięć
testów Python nie jest testami całej gry. Demonstrowane Q09/Q12/Q21 działają
w engine na hoście, ale nie są jeszcze połączone z natywnym UI. Kampania,
zapisy, produkcyjne grafiki i dźwięki pozostają niewykonane.

Następny krok (etap 2): pełna geometria interfejsu, obsługa komend/ekwipunku/
pojemników, wybór dwóch postaci i podłączenie przetestowanych reguł demonstracji.
Następnie kompletna logika Q01–Q40 z czterema ścieżkami. Nie zaczynać od nowa.
Poprzedni etap wysłano na GitHub: `7bacbb8`.

## 2026-11-01 — etap 2a: natywne UI i demonstracja połączona z silnikiem

Wykonano kod `src/platform_mac/demo.c`: docelowy układ 512×342, osiem komend,
ekwipunek, przejścia, modalne pojemniki, rozmowy, dzienniki, trzy poziomy
podpowiedzi, własna historia każdej postaci i pełny widok komunikatu z przewijaniem.
Przeciąganie przedmiotów pojemnik→ekwipunek i ekwipunek→obiekt/portret.
Tab i przycisk przełączają postać; modalne okna blokują przełączanie.
Zmieniane obszary są unieważniane osobno, bez odrysowywania całego ekranu
przy samej selekcji. Standardowy build wybiera teraz demonstrację;
`PROCH_BRINGUP=ON` lub `PROCH_AUTOTEST=ON` zachowuje test początkowy.

Reguły Q09/Q12/Q21 są podłączone do realnego UI. Wczesne podnoszenie działa,
Biblia pozostaje opcjonalna, obejrzenie jej jest osobną czynnością. Grafiki
to wyraźnie oznaczone prostokąty diagnostyczne, nie ilustracje wydania końcowego.
Zapis/wczytanie są celowo nieaktywne, bo nie zostały jeszcze zaimplementowane.

Testy: kompilacja 68000 z -Werror PASS, engine C/ASan/UBSan PASS, kodowanie
i generacja fontu PASS. Pierwsze pełne przejście Q09/Q12/Q21 przez kliknięcia
w Mini vMac Plus/System 6.0.8 PASS, potwierdzone pikselami dzienników.
Po tej próbie poprawiono izolację historii i rysowanie dirty rects.
**Końcowe powtórzenie na najnowszym buildzie jest w toku**; nie utożsamiać
pierwszej próby z wynikiem aktualnego pliku. Narzędzie `test_native_demo.py`
wiąże wynik z niezmiennym `PROCH.bin` i manifestem konkretnego startu emulatora.

Aktualny test: `/workspace/testing/stage2-final`, emulator w kontenerze
`proch-emulation`, DISPLAY=:99, okno 0x200004. Wyniki i surowe zrzuty:
`/workspace/testing/native-ui`. Przed ewentualnym wznowieniem sprawdzić ekran
i które Q zakończono; skrypty q09/q12/q21 uruchamia się kolejno na świeżym starcie.
`dist/` nadal zawiera poprzedni zweryfikowany build z `019e929`; zostanie
zaktualizowany po końcowym teście UI.

Następny krok: dokończyć końcowe testy UI trzech Q, utrwalić wyniki i binaria,
potem kampania A–F i pełna logika Q01–Q40. SE nadal niezweryfikowany (ROM Plus).

## 2026-11-01 — etap 2b: końcowe przejście demonstracji i dystrybucja

Końcowy build UI (SHA256 `82ce97247d1e6ed3860a710d2cf726887da8a7b060239c269e3ca500ed063be7`)
przeszedł Q09, Q12, Q21 oraz test dłuższego dialogu i pełnego opisu z historii
w Mini vMac Plus/System 6.0.8/4 MB. Dowodem są odczyty pikseli dzienników,
prywatnej historii K i pełnych tekstów. Testy nie wywołują wewnętrznych metod
silnika ani nie ustawiają flag przez skróty. Używają klikania i klawiatury.

Wykryto problem runnera: zrzut w trakcie odrysowania oraz kursor zasłaniający
sprawdzaną literę. Poprawiono stabilizację klatki/położenie kursora, potwierdzono
całą końcówkę Q12. Nie wyłączano asercji ani nie podmieniano tekstu.

`dist/PROCH.bin` i `dist/PROCH.dsk` zaktualizowane dokładnie do przetestowanego
snapshotu. Raport w `tests/results/stage2-native.json`, zrzuty `stage2-*`,
instrukcje uruchomienia i powtórzenia w README_PL. Testy hostowe dwóch programów
C (ASan/UBSan) i 9 testów Python PASS.

Ograniczenia: gra nadal jest demonstracją; komplet Q01–Q40, fazy A–F, T01–T04,
zapis/odczyt, końcowe grafiki i dźwięki nie są wykonane. Część gestów, wpisy
faktograficzne dziennika i wszystkie pojemniki wymagają rozszerzenia w kampanii.
Pośrednie substeps demonstracji muszą zostać doprecyzowane przed serializacją;
dotychczas pełny stan czynności zachowują osobne flagi. SE nie został przetestowany.

Następny etap 3: produkcyjny model kampanii i mapa/ograniczenia A–F, najpierw
Q01–Q08 z testami obu kolejności postaci, potem pozostałe Q i cztery zakończenia.
Zachować istniejące testy demonstracji jako regresję. Kod UI wysłano w `593e12a`.

## 2026-11-01 — etap 3a: produkcyjny model kampanii (biblioteka)

Dodano `src/campaign/`: pełny model faz A–F, stany trójwartościowe, flagi
normatywne, własną wiedzę z poziomem pewności i dziennikami, jednoznaczną
własność przedmiotów (w tym zawartość walizki), kolejkę fizycznych wiadomości,
bariery faz oraz wyliczanie priorytetu czterech zakończeń. Cofnięcie odtwarza
cały snapshot obu bohaterów. Są osobne snapshoty bezpieczeństwa i sprzed stawu.

Mapa i zależności są kompilowane z JSON na hoście. Normalizowane są krawędzie
lokalne, a nie podróże między regionami. Sprawdzono ograniczenia stróżówki,
stawu K, biblioteki, fazy E M i nadpisania dostępu F wskazane w dokumencie 03.

Testy modelu C/ASan/UBSan PASS: obie kolejności kończenia A, potwierdzenie C→D,
brak automatycznej wiedzy M po doręczeniu listu, dostarczenie I45 po przełączeniu
na K, brak cykli pojemników, własna wiedza i kompletne cofnięcie. Wszystkie
kombinacje rozstrzygnięć zakończeń spełniają priorytet E04/E01/E02/E03.
Model ma 2464 B na hoście; kompilacja 68000 biblioteki PASS z limitem 4 KiB
na pojedynczy stan. Trzy snapshoty to nadal mała część budżetu 160 KiB.

To testy modelu, **nie implementacja wszystkich Q ani T01–T04**. Biblioteka
`PROCHCampaignCore` jest budowana, ale nie jest jeszcze podłączona zamiast
demonstracji. `dist/` pozostaje zweryfikowanym wycinkiem z etapu 2b (`46caf44`).

Następny krok: deterministyczne reguły Q01–Q08, jawne tematy dialogów i akcje,
testy całego początku przy obu kolejnościach M/K. Potem etapy B–F i integracja
pełnego interfejsu/mapy. Serializacja i produkcyjne zasoby nadal pozostają.

## 2026-11-01 — etap 3b: reguły początku Q01–Q08

Biblioteka kampanii obsługuje publiczne akcje, jawne semantyczne cele,
warunkowe tematy dialogowe, pojemniki i mikroczynności Q01–Q08. Są umowa,
broszka, bilet, naprawa z czterema stanami I41, most/brama i koniec podróży;
u K fotografia matki, pakowanie, Seroczyn, furtka i kontrolowany list.
Teksty z 06 i etykiety z 02 są kompilowane do własnego kodowania PL.
Zapis substep odzwierciedla kroki autorskie; dodatkowe akcje zachowują się
niezależnie. List Q08 nie jest I28 z późniejszego zadania.

Testy C/ASan/UBSan PASS: cztery pełne przejścia początku (M/K najpierw,
adres zostawiony/pominięty). Runner używa wyłącznie działań i zapytań o tematy,
nie kończy Q ani nie ustawia flag. Przełącza postacie po każdej czynności,
sprawdza wczesne podniesienie rzeczy, błędne kolejności, brak mutacji po
odmowie, fizyczną własność rzeczy, prywatną wiedzę i wspólną barierę A→B.
Regresja trzech wcześniejszych programów C i 9 testów Python PASS.
Biblioteka reguł kompiluje się dla 68000 z -Werror.

Ograniczenie: to nadal testy reguł na hoście i cross-build biblioteki.
Nowe Q nie są jeszcze w podłączonym UI, więc nie deklaruję ich przejścia
na Macu. `dist/` pozostaje przetestowaną demonstracją etapu 2b.

Następny krok: reguły fazy B i włączenie kampanii do natywnego interfejsu,
potem C–F oraz cztery pełne ścieżki. Zapis/odczyt, grafiki produkcyjne,
dźwięki i test SE nadal niewykonane.

## 2026-11-01 — etap 3c, zapis roboczy: natywny interfejs kampanii

`PROCH_CAMPAIGN=ON` domyślnie łączy produkcyjne reguły z nowym UI. Są
sceny i cele z JSON, jawne tematy, pojemniki z przeciąganiem, łączenie rzeczy,
osobne historie, fakty i ukończone cele w dziennikach, pełne czytanie wpisu,
podpowiedzi i przewijane panele. Stare UI etapu 2 dostępne przy opcji OFF.
Grafiki nadal jawnie testowe. Zapis/wczytanie nadal nieaktywne.

Cross-build całej aplikacji 68000 PASS; cztery testy C PASS. W natywnym UI
przejście M do Q05 i piksele dziennika PASS. Pierwszy runner miał błędny
wiersz dziennika; poprawiono na podstawie rzeczywistego zrzutu. Próba K
ujawniła utratę widocznej własności rzeczy po spakowaniu do jeszcze stojącej
walizki; pakowanie przenosi teraz również walizkę do K. Dodano asercję C.
Poprawiono też odrysowanie celów zależnych od mikroczynności.

Pełne powtórzenie Q01–Q08 na poprawionym buildzie **w toku**.
Profil `/workspace/testing/stage3a-candidate2`, aplikacja SHA256
`a9afaecc0600cff8ca4d7b6fc3f315a911ff8d4d67a5262c15ad9d0b03b98482`.
Emulator `proch-emulation`, :99, okno 0x200004. Test
`tools/test_native_campaign.py --profile ...` zaczyna od świeżej gry.
`dist/` pozostaje etapu 2b do potwierdzenia wyniku nowego UI.

Następny krok: dokończyć ten test, zapisać dowody/binaria, następnie reguły B
i dalsze fazy. Nie utożsamiać tego etapu z kompletem Q01–Q40/T01–T04.

## 2026-11-01 — etap 3c ukończony: test UI początku i dystrybucja

Pełne powtórzenie Q01–Q08 po poprawkach PASS: 31 kontroli pikseli w Mini vMac
Plus/4 MB/System 6.0.8. Runner używa rzeczywistej myszy i klawiatury.
Wynik `tests/results/stage3-a-native.json`; trzy zrzuty `stage3-a-*.png`.
M przechodzi umowę, broszkę, adres, pociąg/naprawę/przyjazd; K pakowanie,
Seroczyn i kontrolę listu. Dopiero obie gotowe ścieżki uruchamiają fazę B.
Powrót na M potwierdza zachowany dziennik. Testy hostowe i 9 Python PASS.

`dist/` zaktualizowano do dokładnie przetestowanej aplikacji i oryginalnego
obrazu HFS builda (nie do dysku zmodyfikowanego przez emulator). SHA aplikacji
`a9afaecc0600cff8ca4d7b6fc3f315a911ff8d4d67a5262c15ad9d0b03b98482`.
Forki/zasoby/HFS PASS. Źródła UI zapisano i wysłano w `f8d29aa`.

Następny krok: reguły Q09–Q15 fazy B w modelu produkcyjnym (stary wycinek
pozostaje regresją), potem C–F i pełne ścieżki. Zapis, grafiki produkcyjne,
audio, pomiary pamięci i test SE nadal czekają. Gra nie jest ukończona.

## 2026-11-01 — etap 3d: reguły hostowe Q09–Q15 (przed testem natywnym)

Produkcyjny silnik i UI obsługują fazę B: szufladę, klucze/Biblię, Tolka,
Marysię/zeznanie, znaczniki i noc, cień z blokadą i odrzuceniem bez utraty
rzeczy; po stronie K ostrzeżenie/skrócenie ataku, pakowanie, dwa warianty
ucieczki, molo/bezpieczny odwrót i ratunek rybaka. Znaczniki pozostają
w scenie. Odłożonych znaczników nie można zabrać i nadal uznać za działające.
Przewinięcie listy przejść zeruje się przy zmianie lokacji, pozostając
niezależne między bohaterami.

Host C/ASan/UBSan PASS: cztery pełne ścieżki Q01–Q15 bez ustawiania flag,
obie kolejności M/K i Q11/Q12, Biblia zabrana/zostawiona, obie ucieczki
i skrócenie opisu, błędne rozmowy, odrzucenie przez cień i blokada zmiany.
Cross-build aplikacji 68000 PASS. Dotychczasowe regresje PASS.

W chwili tego wpisu test natywny był w przygotowaniu, a `dist/` nadal oznaczał
zweryfikowane Q01–Q08 z `d6e6124`, nie przypisywać mu wyników Q09–Q15.
Następny krok: natywne przejście A+B na świeżym profilu, poprawki jeśli
potrzebne, potem faza C. Ten status roboczy zamyka końcowy wpis poniżej.

Końcowe powtórzenie 3d: profil `/workspace/testing/stage3b-final`, SHA aplikacji
`b6cc3532f2a31ff9709552e0f3574e4bfad99f3cbfac5d1648a868b3aa6df60b`,
runner `test_native_campaign.py --chapter ab --profile ...` **w toku**.
Pierwsze A+B PASS na poprzednim snapshotcie. Następnie poprawiono fakt
o obu znacznikach: pojawia się dopiero po obu oględzinach, z osobną asercją C.
Podsumowanie Q12 pojawia się po wszystkich warunkach, niezależnie od tego,
czy koronkę zabrano przed oględzinami, czy po nich. `dist/` nadal etapu 3c.

## 2026-11-01 — etap 3d ukończony: natywne przejście A+B

Końcowy poprawiony snapshot z `af64764` przeszedł Q01–Q15: 63 kontrole
pikseli w Plus/System 6.0.8/4 MB. Raport `stage3-ab-native.json`, zrzuty
`stage3-b-*.png`. Sprawdzono cień z odrzuceniem i blokadą, ostrzeżenie/
skrót Ireny, konfrontację, odwrót od molo i wspólne wejście do C.
`dist/` zawiera dokładnie ten build, SHA
`b6cc3532f2a31ff9709552e0f3574e4bfad99f3cbfac5d1648a868b3aa6df60b`;
HFS skopiowano z oryginalnego builda po weryfikacji manifestu, nie z sesji.
Forki/zasoby/HFS PASS. Hostowe warianty opisano w poprzednim wpisie.
Przy zamknięciu sprawdzono `git diff --check`, integralność MacBinary/HFS,
SHA256 aplikacji oraz zgodność sumy z raportem natywnym. Raport zawiera PASS
i 63 kontrole; cztery zrzuty fazy B są dołączone.

Następny etap: C, Q16–Q24. Potrzebne biblioteka/portret/kronika, ścieżka/
widzenie z zawsze dostępnym wyjściem, opcjonalna uczciwa rozmowa, szycie,
sieć i prywatny list, podróż z alternatywną księgą adresów oraz jawne
potwierdzenie C→D. Nadal pozostają Q25–Q40 i dalsze wymagania; SE niebadany.

## 2026-11-01 — etap 3e: reguły M fazy C, Q16–Q19

Wykonano: do produkcyjnego modelu dołączono rozmowę z Marianną, proboszczem
i Krystyną, zaproszenie do pałacu, portret i drabinę, wskazówki katalogu oraz
kroniki, mapę i widzenie nad stawem. Wiedza o Grecie ma osobne poziomy:
tożsamość jest poznana, a legenda pozostaje podejrzeniem. Widzenie blokuje
zmianę postaci, nie przenosi dawnych przedmiotów do ekwipunku i pozwala zawsze
wyjść ku światłu, także bez wcześniejszego oglądania szczegółów.

Przetestowano: publiczne akcje Q01–Q19 M w dwóch wariantach widzenia, wraz
z odmową przedwczesnych działań, blokadą drabiny, niezależnością wiedzy K,
identycznym ekwipunkiem przed/po widzeniu poza I23 i pozostaniem w fazie C
do ukończenia ścieżki K. Testy hostowe C z ASan/UBSan oraz walidacja danych
PASS; cross-build całej aplikacji 68000 Retro68 PASS.

Problemy i granice: nowy odcinek jest sprawdzony tylko w modelu hostowym
i przez kompilator 68000. Interfejs Mac nie pokazuje jeszcze przejść ani
celów fazy C; w `dist/` nadal jest dokładnie natywnie przetestowany build
Q01–Q15 (`b6cc3532...`). Nie wykonano przejścia Q16–Q19 w Mini vMac ani
testu na SE. Q20–Q40, zapis/odczyt, końcowe ilustracje, audio i pomiary
pamięci nadal pozostają do wykonania.

Następny krok: podłączyć Q16–Q19 do natywnego UI i przetestować w Mini vMac,
następnie dobudować pozostałe Q20–Q24 fazy C.

## 2026-11-01 — etap 3f: natywne Q16–Q19 Mikołaja

Wykonano: panel przejść udostępnia trasę fazy C Mikołaja, biblioteka pokazuje
Ludwika, kartę kroniki i margines, drabinę można wskazać jako źródło Użyj.
W widzeniu przycisk Przejścia oraz światło prowadzą bezpiecznie na ścieżkę.
Podpowiedzi wybierają teraz właściwe Q16–Q19. Zapisano dokładnie testowane
`PROCH.bin` i oryginalny obraz HFS do `dist/`, raport i zrzut dziennika Q19.

Przetestowano: pełny natywny przebieg od nowej gry Q01–Q15 obu postaci,
następnie Q16–Q19 M w Mini vMac Plus/System 6.0.8/4 MB: PASS, 80 kontroli
obrazu. Profil `/workspace/testing/stage3c-m-final`, raport
`tests/results/stage3-c-m-native.json`, SHA aplikacji
`76da6b3a8364211d0f6a5d115c561e4268e8892d9343bd622bba94da120b5a41`.
Suma builda, kopii uruchomionej i `dist/` jest identyczna; kontrola MacBinary,
forków zasobów i HFS PASS. Host C/ASan/UBSan, walidator i 9 testów Python PASS.
Zrzut `screenshots/stage3-c-q19-journal.png` ma 512×342 i tryb 1-bit.

Problemy i granice: pierwsza próba runnera wybrała pusty slot zamiast I19;
druga nie zamknęła okna kroniki. Po poprawkach skryptu końcowy pełny przebieg
przeszedł bez przerwy. Te dwie próby nie wykazały błędu gry. Q20–Q24 i reszta
kampanii, zapis/odczyt, produkcyjne ilustracje, audio, pomiary pamięci oraz
test SE nadal niewykonane. Nie utożsamiać testu Plus ze zgodnością SE.

Następny krok: opcjonalne Q20, potem ścieżka K Q21–Q24 i potwierdzenie C→D.
Przy realizacji prostego Q20 nie zmieniać zasad drabiny, widzenia ani kodu UI
fazy B; zachować osobny mały etap i test publicznych akcji.

## 2026-11-01 — etap 3g: opcjonalne Q20 w fazie C

Wykonano: Mikołaj może porozmawiać z Krystyną o Warszawie, nazwać związek
z Konstancją, pokazać broszkę I03 i złożyć uczciwą deklarację. Tematy
udostępniają się po kolei, a Q17 jest warunkiem wstępnym. Flaga
`PR_HONEST_KRYSTYNA` ustawia się dopiero przy ostatnim wyborze; I03 pozostaje
w ekwipunku. Q20 nie jest warunkiem dalszej fazy C.

Przetestowano: host C/ASan/UBSan przez `pr_act`: pełne Q20 oraz dwie ścieżki
pomijające zadanie; nieprawidłowe rozmowy i użycie I01 nie zmieniają stanu,
flaga nie ustawia się przed ostatnim wyborem, broszka nie jest zużywana.
Dziewięć testów Python PASS. Cross-build pełnej aplikacji 68000 PASS.
Mini vMac Plus/System 6.0.8/4 MB: pełny natywny przebieg Q01–Q15 obu postaci,
Q16–Q20 M PASS, 84 kontrole obrazu. Profil `/workspace/testing/stage3c-q20-final2`,
raport `tests/results/stage3-c-m-q20-native.json`, SHA aplikacji
`bacef93fca4b43fcf455fd72a814ec5da869fb8ab8bb9d31b27e1824957dcdb6`.
Testowana kopia, build i `dist/` mają tę samą sumę. Kontrola forków/HFS PASS;
zrzut wpisu Q20 `screenshots/stage3-c-q20-journal.png` ma 512×342/1-bit.

Problemy i granice: rozmowa Q20 jest zaimplementowana i przetestowana tylko
w fazie C. Jej dostępność w D, wymagana specyfikacją, pozostaje do wdrożenia;
kod D nie był zmieniany. Nie wykonano testu SE. Q21–Q40, zapis/odczyt,
końcowe ilustracje, audio i pomiary pamięci nadal pozostają do zrobienia.

Następny krok: ścieżka K Q21–Q24 w C. Później dodać Q20 także w D przed
rozmową w ogrodzie i przetestować oba punkty dostępu.

## 2026-11-01 — etap 3h: model Q21 Konstancji

Wykonano: oddzielono reguły K w fazie C od reguł M; Q21 prowadzi od zgody
rybaka przez skrzynię z I24/I25, dwa użycia na stole, wybór kroju i długości,
szycie I26 oraz założenie sukni. I24/I25 pozostają własnością K, I26 ma stan
noszony, a flaga `PR_DISGUISE` ustawia się po założeniu. Nie dodano przejścia
C→D ani reguł Q22–Q24.

Przetestowano: publiczne akcje `pr_act` z odmową zbyt wczesnego otwarcia,
zabrania i szycia, właściwym ukończeniem, własnością rzeczy, flagą i stanem
fazy C. Host C/ASan/UBSan i walidator danych PASS. Cross-build całej aplikacji
Motorola 68000 PASS.

Problemy i granice: interfejs Mac nie obsługuje jeszcze skrzyni, wyboru przy
stole ani założenia I26 na portret. `dist/` nadal zawiera natywnie sprawdzony
build Q01–Q20 z etapu 3g. Q21 nie jest jeszcze przetestowane w emulatorze Plus
ani na SE.

Następny krok: podłączyć Q21 do UI i przejść je od nowej gry w Mini vMac;
dopiero po takim teście aktualizować `dist/`. Potem Q22–Q24.

## 2026-11-01 — etap 3i: natywne Q21 Konstancji

Wykonano: w interfejsie Mac skrzynia pokazuje I24/I25 po zgodzie rybaka,
stół otwiera kolejno wybór kroju, długości i szycia, a I26 można użyć na
portrecie Konstancji. Podpowiedź w C kieruje do Q21. Do `dist/` zapisano
testowany build i oryginalny obraz HFS; dołączono raport i zrzut dziennika.

Przetestowano: pełny natywny przebieg Q01–Q15 obu postaci, Q16–Q20 M
i Q21 K w Mini vMac Plus/System 6.0.8/4 MB: PASS, 86 kontroli obrazu.
Profil `/workspace/testing/stage3c-q21-candidate1`, raport
`tests/results/stage3-c-q21-native.json`, SHA aplikacji
`f7c70232d10ebf26f64a7039eaefb1851755320e16445ac70e2d6b72a00b3180`.
Build, uruchomiona kopia i `dist/` mają tę samą sumę; kontrola MacBinary,
zasobów i HFS PASS. Zrzut `screenshots/stage3-c-q21-journal.png` ma
512×342/1-bit. Test hostowy C/ASan/UBSan, walidacja danych, 9 testów
Python i cross-build 68000 PASS.

Problemy i granice: Q22–Q24, przejście do D i dostępność Q20 w D nie są
zaimplementowane. Ilustracje nadal są testowymi prostokątami; zapis/odczyt,
audio i pomiar pamięci czekają. Nie wykonano testu SE.

Następny krok: Q22 — sieć z możliwością cofnięcia błędnego połączenia,
potem opcjonalny list Q23 i podróż Q24. Przed zmianą silnika przygotować
teksty, mapę akcji i przypadki testowe, zachowując opcjonalność Q22/Q23.

## 2026-11-01 — etap 3j: przygotowanie treści i kontraktu Q22–Q24

Wykonano: dodano polskie etykiety i odpowiedzi dla naprawy sieci, bezpiecznej
drogi przez sąsiada, listu K do Izydora oraz podróży powrotnej. Teksty
rozróżniają obie gałęzie adresu: wcześniej pozostawiony adres i księgę wysyłek
za zgodą Izydora. Odpowiedź rybaka w Q24 mówi wprost, że pieniądze na podróż
nie zależą od naprawy sieci. Dodano `Q22-Q24_IMPLEMENTATION_CONTRACT.md`
z mapą akcji i przypadkami testowymi.

Przetestowano: `python3 -m json.tool content/campaign_texts.json` PASS;
`python3 tools/generate_campaign.py build/generated` PASS; `git diff --check`
PASS; `bash tools/test_host.sh` PASS, łącznie walidator 40 zadań / 43 sceny /
45 przedmiotów. Testy hostowe obejmują dotychczasowe Q01–Q21 i nie weryfikują
nowych zachowań Q22–Q24.

Problemy i granice: nowe klucze tekstowe i kontrakt nie są jeszcze podłączone
do reguł ani natywnego UI. Nie zmieniano `dist/`; nie wykonano cross-builda
ani testu emulatora dla tych tekstów. Sieć, list, obie gałęzie adresu, podróż
i bariera C→D pozostają do implementacji i pełnego przetestowania.

Następny krok: zaimplementować Q22 z resetem wyłącznie stanu układanki przy
błędnym połączeniu, a potem Q23/Q24 z niezależnością podróży od Q22/Q23.

## 2026-11-01 — etap 3k: natywne Q22, sieć i zaufanie

Wykonano: Konstancja po Q21 może przejść przez L32 do L34, porozmawiać
z sąsiadem, obejrzeć sieć, użyć I25 i połączyć końce w zadanej kolejności.
Błędny wybór zeruje wyłącznie dwa bity połączeń, pozostawiając rozmowę,
oględziny, igłę, inne zadania i przedmioty. Potwierdzenie wzoru odblokowuje
odbiór I27 u sąsiada; dopiero wtedy Q22 kończy się i ustawia
`PR_SAFE_COURIER`. Q22 można całkowicie pominąć. Podłączono wybory, przejścia
i podpowiedzi do interfejsu Mac. `dist/` zawiera przetestowaną aplikację
i oryginalny obraz HFS.

Przetestowano: C host ASan/UBSan i walidator danych PASS; 9 testów Python
PASS; cross-build Motorola 68000 PASS; kontrola MacBinary, zasobów i HFS
PASS. Pełny natywny przebieg Q01–Q15 obu postaci, Q16–Q20 M i Q21–Q22 K
w Mini vMac Plus/System 6.0.8/4 MB: PASS, 95 kontroli pikseli, w tym dwa
błędne połączenia i wpis Q22 w dzienniku. Raport
`tests/results/stage3-c-q22-native.json`, profil
`/workspace/testing/stage3c-q22-candidate1`, SHA aplikacji
`146675f3dd2636f0ae91fbd7dc8b0f379f0ddf53800bd6aa5cc4698527f8d3a1`.
Zrzut `screenshots/stage3-c-q22-journal.png` ma 512×342/1-bit.

Problemy i granice: Q23/Q24 oraz przejście C→D nadal nie istnieją.
Opcjonalność Q22 względem Q24 jest udowodniona kontraktem i testem hostowym
pominięcia, ale pełna ścieżka Q24 bez Q22 czeka na implementację Q24.
Q20 w D, SE, zapis/odczyt, produkcyjne ilustracje, audio i pomiary pamięci
również pozostają nieweryfikowane lub niewykonane.

Następny krok: Q23 — złożenie listu, prywatne wspomnienie, jeden fizyczny
egzemplarz u kuriera i doręczenie dopiero przy wejściu do D. Najpierw
przygotować mapę stanów i testów bez zmiany reguł, następnie wdrożyć Q23;
po nim Q24 z niezależnością od Q22/Q23.
