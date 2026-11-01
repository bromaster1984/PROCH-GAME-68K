# PROCH — raport testów

## Reguły fazy A (etap 3b)

Q01–Q08: cztery przejścia przez `pr_act` PASS pod ASan/UBSan, obie kolejności
M/K, Q02 wykonane/pominięte, przełączenia po każdym działaniu. Sprawdzono
odmowy bez zmiany stanu, właściwe kroki naprawy i listu, wczesne podnoszenie,
prywatną wiedzę i barierę faz. Cross-build biblioteki 68000 PASS (-Werror).
To nie są jeszcze testy nowej kampanii w UI ani pełne T01–T04.

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

## Wynik aktualny: System 6.0.8 na Plusie, toolchain ze źródeł i font PL

Retro68 i Multiversal z commitów w locku są zbudowane ze źródeł i użyte do
aktualnego `dist/`. Pierwszy fork zasobów z tego toolchaina był identyczny
z testowanym bootstrapem (SHA256
`fbe019e048b274196b32ff4cc6bd5d89175ad6af90d3d19ead4de2f06b7497ef`).
Po dodaniu fontu wykonano nowy build i nowe uruchomienie.

Mini vMac, SHA `6860a9a7f372c461b25dc42974b191a453ebcfb2`, model **Plus**,
68000, 4 MB, 512×342, bez powiększenia, ROM Plus v3. Źródłem systemu jest
obraz dostarczony przez autora. Systemowy ekran potwierdził **System 6.0.8,
Finder 6.1.8, 4096K** (`screenshots/system608-plus-4mb.png`).

- uruchomienie natywnego APPL z HFS, okno, CopyBits i pozostawienie aplikacji
  przez Command-Q: PASS;
- rzeczywiste zdarzenie jednoprzyciskowej myszy: PASS. Różnica wszystkich
  49 pikseli pędzla 7×7, porównana w zrzutach przed/po;
- próbka własnego fontu z ĄąĆćĘęŁłŃńÓóŚśŹźŻż: wyświetlona w aplikacji
  na angielskim systemie (`screenshots/font-pl-plus-system608.png`);
- ELF32 big endian, Machine MC68000, flag `m68000`: PASS;
- aktualny test natywny Executor 2000: PASS;
- 9 testów Python i 2 programy testów C (ASan/UBSan): PASS. Dotyczą formatu
  dystrybucji, fontu, renderera i trzech demonstracyjnych zadań.

Zrzuty X11 mają wyłączoną ramkę gospodarza (`xwd -nobdrs`); konwerter odmawia
skalowania, kadrowania i redukcji kolorów. PNG są bezstratnym zapisem
rzeczywistego czarno-białego ekranu, nie wizualizacją planowanej gry.

**Nadal niewykonane:** wymagany test SE/4 MB, SE/30/System7, fizyczny sprzęt,
pomiar pamięci i czasów reakcji, pełny natywny interfejs, cała kampania oraz
T01–T04, zapis/odczyt, produkcyjne ilustracje, audio i playtest długości.

## Etap 2 — wycinek połączonego UI i silnika

Natywna aplikacja demonstracji: **35968 B MacBinary**, fork zasobów 35801 B,
HFS 819200 B. SHA256 aplikacji:
`82ce97247d1e6ed3860a710d2cf726887da8a7b060239c269e3ca500ed063be7`.
Jest to dokładnie plik uruchomiony w Mini vMac Plus/System 6.0.8/4 MB,
zachowany przed startem jako niezmienny `PROCH.bin` wraz z manifestem wejść.

Pięć części testu UI: **PASS**. Surowy raport:
`tests/results/stage2-native.json`. Sprawdzono przez rzeczywiste kliknięcia
i odczyt pikseli własnego fontu:

- Q09: rozmowa, przejścia, kluczyk, szuflada, pęk kluczy, Biblia pozostawiona
  w pokoju, rower i wpis w dzienniku;
- Q12: materiały, oba wejścia, znaczniki, jawny odpoczynek, nienaruszone
  znaczniki i podniesienie koronki;
- Q21: pozwolenie rybaka, skrzynia, tkanina/igła, trzy czynności przy stole,
  założenie sukni; K ma własny dziennik i historię;
- przełączanie zachowuje miejsca i postęp; modalna rozmowa blokuje Tab;
- dłuższy dialog wyświetla wszystkie wiersze, historia pokazuje cały opis Q12.

Testy wiążą wynik z sumą aplikacji i konkretnym profilem startu. Wczesny zrzut
zrobiony podczas odrysowania miał niepełną linię; inne porównanie zasłonił
kursor. Poprawiono runner: czeka na stabilną klatkę i odsuwa kursor przed
porównaniem. Pełny opis sprawdzono ponownie na tych samych binariach.

**Zakres:** fixture M w B i K w L33; brak całej osi A–F. Kontrolki zapisu są
wyłączone. Brak produkcyjnych ilustracji i audio. Nie są to T01–T04, test SE
ani fizycznego sprzętu. Pozostają pełne gesty (m.in. automatyczne podwójne
kliknięcie), pełne dzienniki fabularne, pojemniki i mapa całej kampanii,
serializacja oraz reszta wymagań specyfikacji.

## Etap 3a — osobny model produkcyjny

Trzeci program testów hostowych C/ASan/UBSan: PASS. Obejmuje własność
przedmiotów z walizką i zakazem cykli, oddzielną wiedzę, bariery faz w obu
kolejnościach postaci, wiadomości/doręczenia bez nadania wiedzy, ograniczenia
mapy, pełny snapshot oraz podział wyników zakończeń. Model ma 2464 B na hoście;
biblioteka kompiluje się na 68000 i mieści w asercji 4096 B na stan.

W teście ustawiane są stany wejściowe modelu. Nie jest to przejście zadań
Q01–Q40, nie potwierdza napisania tych reguł i nie zastępuje T01–T04.
Biblioteka nie jest jeszcze używana przez dystrybuowaną demonstrację.
