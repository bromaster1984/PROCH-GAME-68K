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
