# PROCH — raport testów

## 2026-11-01, etap 1 (w toku)

- Host: Debian 13, x86_64, Docker 28.4.0.
- Bootstrap: oficjalny Retro68, digest z `toolchain.lock.json`, GCC 16.1.0,
  CMake 3.22.1, Multiversal Interfaces. Toolchain ze źródeł wskazanego commita
  jest jeszcze budowany. Nie przypisujemy binariom obrazu niepotwierdzonego SHA źródeł.
- Kompilacja aplikacji: PASS, `-m68000 -msoft-float -Os -Wall -Wextra -Werror`.
- C host + AddressSanitizer/UndefinedBehaviorSanitizer: PASS. Renderer sprawdza
  całą bitmapę, kolejność bitów, stride 46, padding i klipowanie przy krawędziach.
- Walidator autorskich danych: PASS (40 Q, 43 lokacje, 45 przedmiotów).
- 5 testów kontenera aplikacji: PASS. Header CRC MacBinary, oba forki,
  CODE:0/CODE:1, SIZE:-1 (minimum 1536 KiB, preferred 2048 KiB), HFS MDB.
  Testy negatywne: uszkodzony nagłówek, skrócony fork i błędny offset zasobu.
- MacBinary: 8448 B; resource fork 8243 B; data fork pusty — kod 68K i dane
  znajdują się w zasobach, co jest prawidłowe dla tej aplikacji.
- Obraz HFS: 819200 B, bez systemu.

Niewykonane: uruchomienie testu Toolbox, rzeczywiste kliknięcia, SE 68000/4 MB/
System 6.0.8, SE/30/System 7 i fizyczny sprzęt. Brak pomiarów sterty i czasu
reakcji. Nie ma jeszcze logiki Q ani przejść E01–E04, fontu PL, produkcyjnych
ilustracji, zapisu/odczytu i audio. Brak zrzutów ekranu działającego emulatora.

Żaden wynik walidatora ani testu hostowego nie jest przedstawiany jako test SE.

## Aktualizacja: Toolbox i engine demonstracji

Executor 2000 v0.1.0 (suma archiwum w locku), parametry `-bpp 1 -size 512x342
-memory 4M -applzone 2M -nosound -nobrowser`: **PASS**. Test sprawdził geometrię,
polaryzację pikseli po CopyBits i syntetyczne wywołanie funkcji kliknięcia.
Wynik: `PROCH_TOOLBOX_SMOKE_PASS`. Wyeksportowano rzeczywisty framebuffer
w PBM; konwersja do PNG nie zmienia pikseli. To reimplementacja Toolbox,
nie emulacja ROM-u SE i nie System 6.0.8.

Test engine host C + ASan/UBSan: PASS, demonstracyjne Q09/Q12 i fragment Q21,
z przełączaniem po każdej czynności, wczesnym zebraniem przedmiotów, pozostawioną
Biblią, niewspółdzielonymi ekwipunkami/wiedzą oraz idempotencją nagród.
Fixture jawnie łączy wycinek M z B i K z C; nie testuje osi etapów pełnej gry.

Materiały autora z `MAC PLUS`: ROM Plus v3, zweryfikowana suma 0x4d1f8172
pierwszych 131072 B; 7504 B za ROM-em nie są używane. DiskCopy 4.2:
suma danych 0x816f85c8 zgodna. Przygotowanie kopii nie zmienia źródeł.
Testy Plus/System 6 i SE/System 6 nadal oczekują na wykonanie.
