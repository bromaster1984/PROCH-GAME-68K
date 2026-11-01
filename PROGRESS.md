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
