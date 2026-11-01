# PROCH — implementacja natywna

Cel: Macintosh SE, Motorola 68000, 4 MB, System 6.0.8, ekran 512×342 1-bit.
Obecnie: **etap techniczny, nie ukończona gra**. Uruchomiony na emulowanym
Plusie/4 MB/Systemie 6.0.8. Status w `PROGRESS.md` i
`TEST_REPORT.md`. Specyfikacja autora pozostaje w plikach `00_`–`08_` i JSON.

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

Na czas testu technicznego: kliknięcie wzoru zmienia jego fragment. Plik →
Zmien wzor wybiera drugi wzór. Plik → Wyjscie lub Command-Q kończy program.
Szachownica jest wzorcem diagnostycznym. Własny font PL i jego mapowanie są
opisane w `FONT_PL.md`; próbka liter jest widoczna na dole ekranu.

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

Nie dołączono cudzych ROM-ów ani systemu. Sam build nie potwierdza działania
na Systemie 6.0.8. Minimalna partycja wynosi 1536 KiB, zalecana 2048 KiB;
rzeczywiste zużycie i wolna sterta na 4 MB pozostają do pomiaru.
