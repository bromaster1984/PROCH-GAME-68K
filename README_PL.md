# PROCH — implementacja natywna

Cel: Macintosh SE, Motorola 68000, 4 MB, System 6.0.8, ekran 512×342 1-bit.
Obecnie: **grywalne Q01–Q15 obu postaci oraz Q16–Q20 Mikołaja w C; gra nieukończona**.
Przetestowany na emulowanym Plusie/4 MB/Systemie 6.0.8.
Status w `PROGRESS.md` i
`TEST_REPORT.md`. Specyfikacja autora pozostaje w plikach `00_`–`08_` i JSON.

Źródła domyślnie budują ten początek kampanii (etap 3).
`dist/` zawiera dokładnie przetestowany build `bacef93f…57dcdb6` z etapu 3g.
Do budowania historycznej demonstracji służy `PROCH_CAMPAIGN=OFF`;
z innym katalogiem `PROCH_DIST_DIR`, aby nie nadpisać aktualnej dystrybucji.

## Sterowanie początkiem kampanii

Mikołaj zaczyna w gabinecie Koreckiego, Konstancja w swoim pokoju. Komendy
i przyciski są obsługiwane jednoprzyciskową myszą. Rozmawiaj na postaci
otwiera aktualnie dostępne tematy. Dokumenty i wpisy historii można czytać
w całości z przewijaniem. Gra → Dziennik zawiera osobne fakty każdej osoby;
kliknięcie wpisu otwiera pełny tekst. Gra → Podpowiedź stopniuje wskazówki.

Otwórz szkatułkę/skrzynkę/kufer, potem przeciągnij rzecz do ekwipunku.
Kliknięcie rzeczy w pojemniku ją ogląda. Użyj: wybierz rzecz, potem obiekt
sceny lub drugą rzecz. Pakowanie fotografii/dokumentu do walizki zachowuje
własność Konstancji. Dolne przyciski sceny udostępniają szczegóły zaworu,
bramę i wyjazd. Tab przełącza poza otwartym oknem; Escape je zamyka.
Panel Przejścia i ekwipunek mają przyciski przewijania.

Zapis i wczytanie jeszcze nie są dostępne. Po Q05 i Q08 obie postacie
przechodzą razem do B. W pokoju M przyciski Szuflada/Drzwi udostępniają
szczegóły, Użyj na łóżku bez wybranej rzeczy otwiera wybór odpoczynku.
Koronkę można przeciągnąć do ekwipunku. Przy cieniu przełączenie jest
zablokowane do wyjścia; uderzenie resetuje scenę, zachowując rzeczy.
Scena Ireny ma ostrzeżenie i skrócenie opisu. Rozmawiaj na linii brzegu
otwiera wybór kierunku po obejrzeniu świateł. Po Q13 i Q15 rozpoczyna się C;
Mikołaj może dalej rozmawiać w plebanii, porównać koronkę z portretem po
ustawieniu drabiny, czytać kronikę i dotrzeć nad staw. W widzeniu należy
zamknąć tekst, obejrzeć szczegóły i wybrać światło; wyjście działa także
bez oglądania szczegółów. Po Q19 Mikołaj może wrócić do Krystyny, powiedzieć
jej o Konstancji i ukończyć opcjonalne Q20. Q20 jest obecnie dostępne tylko
w C; jego dostępność w D oraz Konstancja w C pozostają do implementacji.

## Pierwszy build

Wymagane Docker, Git, Python 3 (Pillow do konwersji zrzutów) i kompilator C hosta
do testów. Komendy z katalogu
głównego repozytorium. Konkretny commit Retro68 oraz digest obrazu są zapisane
w `toolchain.lock.json`. Toolchain został zbudowany z przypiętych źródeł,
tylko 68K, z Multiversal Interfaces. Oficjalny obraz służy jako środowisko
budowania. Pełny pierwszy build GCC/binutils jest długi; kolejne zadania
wykorzystują istniejące narzędzia bez ponownej kompilacji.

```sh
bash tools/build_toolchain.sh
bash tools/build_mac.sh source OFF
bash tools/test_host.sh
python3 tools/check_artifacts.py dist
python3 -m unittest discover -s tests -p 'test_*.py' -v
```

`-m68000 -msoft-float` jest wymagane przy kompilacji i linkowaniu. Brak konsoli,
C++ i interpretacji JSON na Macu. Multiversal Interfaces są otwarte.
W środowisku cloud polecenia Docker i Git przez proxy mogą wymagać uprawnień
wykonania; nie zmieniać proxy i nie wyłączać weryfikacji TLS.

## Przeniesienie i uruchomienie

`dist/PROCH.bin` to MacBinary zawierający resource fork, `APPL`/`PRCH` i zasoby
`CODE` oraz `SIZE`. Skopiować plik `.bin` na działający dysk Maca i rozpakować
narzędziem obsługującym MacBinary; zwykłe przemianowanie pliku nie wystarczy.
Alternatywnie zamontować `dist/PROCH.dsk` jako **wolumin HFS** w emulatorze
i skopiować aplikację na dysk systemowy. Obraz nie zawiera systemu, sterownika
SCSI ani mapy partycji i nie jest reklamowany jako bootowalny dysk BlueSCSI.

Domyślne ścieżki narzędzi poza checkoutem: `/workspace/toolchains/Retro68`
i `/workspace/toolchains/Retro68-build`; do zmiany służą `PROCH_TOOLS_DIR`
i `PROCH_TOOLCHAIN_BUILD`. Dodatkowy test Toolbox: `bash tools/test_toolbox.sh
source`, po instalacji Executor 2000 v0.1.0 z URL i sumą w locku. `bootstrap`
jest jawną opcją budowania oficjalnym obrazem zamiast własnego toolchaina.

## Historyczna demonstracja etapu 2 (PROCH_CAMPAIGN=OFF)

Komenda, potem obiekt. Użyj: najpierw przedmiot w ekwipunku, potem cel.
Przeciągnięcie z pojemnika do ekwipunku zabiera rzecz; kliknięcie jej ikony
w pojemniku również. Biblię kliknij, by obejrzeć, lub przeciągnij, by zabrać
(zabranie nie jest wymagane). Przedmiot z ekwipunku można przeciągnąć na obiekt
lub własny portret. W panelu Przejścia kliknij nazwę dostępnej lokacji.
Tab lub przycisk zmieniają bohatera, Escape zamyka okno/anuluje wybór.
Gra → Dziennik (Command-J), Podpowiedź (Command-H), Pomoc → Sterowanie.
Kliknięcie narracji otwiera historię aktywnego bohatera; kliknięcie wpisu
otwiera pełny tekst z przyciskami przewijania.

Mikołaj zaczyna w L11, Konstancja w L33. To jawna fixture dwóch fragmentów,
nie początek kampanii A–F. Z Florkiem porozmawiaj o pokoju, w pokoju otwórz
biurko, weź kluczyk, użyj go na biurku/szufladzie, otwórz szufladę, weź klucze
i obejrzyj Biblię. Potem zapytaj Florka o rower. Materiały do Q12 są na stole
w warsztacie. Drzwi i okno należy obejrzeć, użyć na nich znaczników, użyć łóżka,
a rano obejrzeć oba wejścia i zabrać koronkę. Jako Konstancja porozmawiaj
z rybakiem, otwórz skrzynię, użyj tkaniny i igły na stole, następnie przy pustym
wyborze Użyj kliknij stół, wybierz krój, długość i szycie. Suknię użyj na portrecie.

Plik → Nowa demonstracja resetuje wycinek. Plik → Wyjscie lub Command-Q kończy
program. Zapis i wczytanie są nieaktywne. Prostokąty z podpisami są celowo
oznaczonymi grafikami testowymi. Własny font PL opisuje `FONT_PL.md`.
Do pierwszego testu szachownicy można wrócić przez `-DPROCH_BRINGUP=ON` w CMake.

## Wykonany test Plus / System 6

Użyto dostarczonych przez autora plików `MAC PLUS`, z zachowaniem oryginałów.
Skrypt `python3 tools/prepare_plus_inputs.py 'MAC PLUS' /workspace/testing/nowy-test`
weryfikuje sumy ROM/DiskCopy i tworzy kopie do testów. Odmawia nadpisania
zmodyfikowanego dysku. Zbudowano Mini vMac z SHA i opcjami podanymi w locku:

```sh
gcc -o setup_t setup/tool.c
./setup_t -n PROCH-MacPlus -t lx64 -m Plus -mem 4M -api xwn -sound 0 \
  -speed 1 -magnify 0 -fullscreen 0 > setup-local.sh
bash setup-local.sh
make -j4
```

Wymaga X11 (`libx11-dev`, do testów bez monitora Xvfb i xdotool). Uruchomić
`minivmac System608.dsk PROCH.dsk` z katalogu kopii zawierającego `vMac.ROM`.
W Finderze otworzyć dysk PROCH, następnie aplikację PROCH. Sprawdzono okno,
rysowanie, kliknięcie i Command-Q. Systemowy „About the Finder” potwierdza
6.0.8 i 4096K. Zrzuty są w `screenshots/`, w rzeczywistych 512×342/1-bit.
Do bezstratnej konwersji `xwd -nobdrs` służy `tools/capture_screen.py`.

ROM-u ani systemu nie kopiujemy do `dist/`. Test Plusa nie zastępuje testu SE.

## Powtarzanie testu UI

Przygotowanie konkretnego builda z manifestem sum:

```sh
python3 tools/prepare_plus_inputs.py 'MAC PLUS' /workspace/testing/nowy-test build/mac-source
```

Uruchomić Mini vMac na tych kopiach, otworzyć aplikację w Finderze. W lokalnym
środowisku testowym Xvfb=:99, kontenerze `proch-emulation` i oknie 0x200004:

```sh
python3 tools/test_native_campaign.py --chapter abc_m --profile /workspace/testing/nowy-test
```

Zmiana nazwy kontenera/okna: `--container`, `--window`. Test wymaga świeżej gry.
Wynik identyfikuje snapshot aplikacji, nie plik nadpisywany następnym buildem.
Aktualny raport to `tests/results/stage3-c-m-q20-native.json`; zrzut Q20:
`screenshots/stage3-c-q20-journal.png`. Poprzednie Q16–Q19:
`stage3-c-m-native.json` i `stage3-c-q19-journal.png`. Q01–Q15:
`stage3-ab-native.json` i `stage3-b-*.png`.
To test początku, nie czterech zakończeń całej gry. Starszy runner
`tools/test_native_demo.py` sprawdza etapy q09, q12, q21, long_dialogue,
description_history w tej kolejności, wyłącznie po zbudowaniu opcji
`PROCH_CAMPAIGN=OFF`. Jego archiwum znajduje się w `stage2-native.json`.

Pakiet `dist/` nie zawiera ROM-u ani systemu. Sam build nie potwierdza działania
na Systemie 6.0.8. Minimalna partycja wynosi 1536 KiB, zalecana 2048 KiB;
rzeczywiste zużycie i wolna sterta na 4 MB pozostają do pomiaru.
