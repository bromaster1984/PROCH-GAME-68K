# PROCH — implementacja natywna

Cel: Macintosh SE, Motorola 68000, 4 MB, System 6.0.8, ekran 512×342 1-bit.
Obecnie: **etap techniczny, nie ukończona gra**. Status w `PROGRESS.md` i
`TEST_REPORT.md`. Specyfikacja autora pozostaje w plikach `00_`–`08_` i JSON.

## Pierwszy build

Wymagane Docker, Git, Python 3 i kompilator C hosta do testów. Komendy z katalogu
głównego repozytorium. Konkretny commit Retro68 oraz digest obrazu są zapisane
w `toolchain.lock.json`. Obraz oficjalny jest bootstrapem; build toolchaina
ze źródeł przypiętego commita jest w przygotowaniu, nie utożsamiać tych rewizji.

```sh
docker run --rm --network none --user "$(id -u):$(id -g)" \
  --entrypoint /bin/bash -v "$PWD:/project" -w /project \
  ghcr.io/autc04/retro68@sha256:dd923969100f408943f73c9618b3c7628686aae819583eecb0ddd1837da6943c \
  -lc 'cmake -S . -B build/mac -DCMAKE_TOOLCHAIN_FILE=/Retro68-build/toolchain/m68k-apple-macos/cmake/retro68.toolchain.cmake && cmake --build build/mac --parallel 4'
bash tools/test_host.sh
python3 tools/check_artifacts.py build/mac
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

Na czas testu technicznego: kliknięcie wzoru zmienia jego fragment. Plik →
Zmien wzor wybiera drugi wzór. Plik → Wyjscie lub Command-Q kończy program.
Napisy bez polskich liter w tym teście są tymczasowe; własny font PL jest
wymaganiem kolejnego etapu. Szachownica jest wzorcem diagnostycznym.

Nie dołączono cudzych ROM-ów ani systemu. Sam build nie potwierdza działania
na Systemie 6.0.8. Minimalna partycja wynosi 1536 KiB, zalecana 2048 KiB;
rzeczywiste zużycie i wolna sterta na 4 MB pozostają do pomiaru.
