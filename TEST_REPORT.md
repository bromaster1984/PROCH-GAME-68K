# PROCH — raport testów

## Bieżące wydanie: etap 3n, Q23 Konstancji w fazie C

`dist/PROCH.bin` SHA256
`c580ace9fa28f3dcffee79dfbe1e01227da91eaf23ddd80236944d80fe030d3a`.
MacBinary 85 376 B, zasoby 85 126 B, HFS 819 200 B. Kontrola forków,
zasobów i HFS PASS; suma aplikacji zgadza się z uruchomioną kopią.

Mini vMac Plus/System 6.0.8/4 MB: Q01–Q15 obu postaci, Q16–Q20 Mikołaja
oraz Q21–Q23 Konstancji PASS, 101 kontroli pikseli. Runner sprawdził
napisanie listu, właściwą treść, wspomnienie broszki, przekazanie sąsiadowi
i wpis „Żyję” w dzienniku. Raport `tests/results/stage3-c-q23-native.json`,
zrzut `screenshots/stage3-c-q23-journal.png` (512×342, 1-bit). Profil
`/workspace/testing/stage3c-q23-candidate1`; emulowany Macintosh Plus.

Host C/ASan/UBSan PASS: publiczne `pr_act` sprawdza Q23 oraz regresje Q01–Q22;
9 testów Python i cross-build 68000 PASS. Hostowy test modelu potwierdza,
że I28 czeka u kuriera do D, trafia wtedy do Florka i Mikołaj nie otrzymuje
wiedzy przed Q26. Ten test dostawy używa testowego spełnienia bramki Q24,
bo Q24 nie jest jeszcze zaimplementowane.

Źródła etapu 3o przechodzą hostowy test Q24 obu gałęzi adresu, podróży bez
Q22/Q23 i potwierdzenia C→D. `dist/` nadal zawiera natywnie sprawdzone Q23.

Niezweryfikowane/niewykonane: natywna dostawa I28 w D, natywne Q24, Q25–Q40,
dostępność Q20 w D, T01–T04, zapis/odczyt, produkcyjne ilustracje, audio,
całkowite zużycie pamięci i test SE.

## Archiwum: etap 3k, Q22 Konstancji w fazie C

Archiwalny `PROCH.bin` SHA256
`146675f3dd2636f0ae91fbd7dc8b0f379f0ddf53800bd6aa5cc4698527f8d3a1`.
MacBinary 83 840 B, zasoby 83 711 B, HFS 819 200 B. Kontrola forków,
zasobów i HFS PASS. Pełny przebieg natywny do Q22 PASS, 95 kontroli.
Raport `tests/results/stage3-c-q22-native.json`, zrzut
`screenshots/stage3-c-q22-journal.png` (512×342, 1-bit).

## Archiwum: etap 3i, Q21 Konstancji w fazie C

Archiwalny `PROCH.bin` SHA256
`f7c70232d10ebf26f64a7039eaefb1851755320e16445ac70e2d6b72a00b3180`.
80 512 B MacBinary, zasoby 80 313 B, HFS 819 200 B. Kontrola forków,
zasobów i HFS PASS; suma aplikacji zgadza się z uruchomioną kopią.

Mini vMac Plus/System 6.0.8/4 MB: pełny natywny przebieg Q01–Q15 obu
postaci, Q16–Q20 Mikołaja i Q21 Konstancji PASS, 86 kontroli obrazu.
Runner używa myszy i klawiatury. W Q21 sprawdził zgodę rybaka, otwarcie
skrzyni, pobranie tkaniny i igły, szycie przy stole, założenie I26 na
portrecie i wpis „Zwykła suknia”. Profil `stage3c-q21-candidate1`, raport
`tests/results/stage3-c-q21-native.json`, zrzut dziennika
`screenshots/stage3-c-q21-journal.png` (512×342, 1-bit).

Host C/ASan/UBSan PASS: Q21 przez publiczne `pr_act`, także odmowy
przedwczesnych działań, własność i niezużywanie I24/I25, noszenie I26,
ustawienie `PR_DISGUISE` po założeniu oraz pozostanie w fazie C.
Regresje Q01–Q20, 9 testów Python i cross-build 68000 PASS.

Niezweryfikowane/niewykonane: Q22–Q40, dostępność Q20 w D,
T01–T04, zapis/odczyt, produkcyjne ilustracje, audio, pomiary pamięci
i test SE/sprzętu fizycznego.

## Archiwum: etap 3g, Q01–Q20 M w fazie C

Archiwalny `PROCH.bin` SHA256
`bacef93fca4b43fcf455fd72a814ec5da869fb8ab8bb9d31b27e1824957dcdb6`.
78 336 B MacBinary, zasoby 78 185 B, HFS 819 200 B. Kontrola forków,
zasobów i HFS PASS. To pliki oryginalnego builda, a suma aplikacji zgadza
się z kopią uruchomioną w emulatorze.

Mini vMac Plus/System 6.0.8/4 MB: pełne natywne przejście Q01–Q15 obu
postaci, następnie Q16–Q20 Mikołaja PASS, 84 kontrole pikseli. Runner używa
myszy i klawiatury, nie zmienia stanu silnika. Profil `stage3c-q20-final2`,
raport `tests/results/stage3-c-m-q20-native.json`, zrzut dziennika
`screenshots/stage3-c-q20-journal.png` (512×342, 1-bit).
Sprawdzono wejście do biblioteki, portret i drabinę, wskazówki katalogu,
kronikę, trasę nad staw, widzenie, wyjście ku światłu, rozmowę o Warszawie,
pokazanie broszki I03 i wpis „Słowo uczciwe”.

Host C/ASan/UBSan PASS: pełne Q16–Q20 oraz dwa przejścia pomijające Q20.
Sprawdzono błędne akcje bez zmian stanu, zachowanie I03, flagę dopiero po
ostatniej deklaracji, niezależność wiedzy K i pozostanie w fazie C.
Pozostałe regresje C i 9 testów Python PASS. Cross-build pełnej aplikacji
68000 PASS.

Niezweryfikowane/niewykonane: dostępność Q20 w D (wymagana specyfikacją),
Q21–Q40, cała ścieżka K w fazie C,
T01–T04, zapis/odczyt, produkcyjne ilustracje, audio, pomiary pamięci
i test SE/sprzętu fizycznego. Plus nie zastępuje SE.

## Archiwum: etap 3f, Q01–Q19 M

`PROCH.bin` SHA256 `76da6b3a8364211d0f6a5d115c561e4268e8892d9343bd622bba94da120b5a41`,
80 natywnych kontroli Q01–Q15 obu postaci i Q16–Q19 M. Raport
`tests/results/stage3-c-m-native.json`.

## Archiwum: etap 3d, fazy A–B

Archiwalny `PROCH.bin` SHA256
`b6cc3532f2a31ff9709552e0f3574e4bfad99f3cbfac5d1648a868b3aa6df60b`.
70 400 B MacBinary, zasoby 70 163 B; HFS 819 200 B. Kontrola artefaktów PASS.
Końcowe przejście Q01–Q15 w Mini vMac Plus/System 6.0.8/4 MB PASS,
63 kontrole pikseli, bez wywołań wewnętrznego silnika. Profil `stage3b-final`,
raport `tests/results/stage3-ab-native.json`, obrazy `stage3-b-*.png`.

Nowe kontrole: Q09 ze szufladą i Biblią pozostawioną, Q10/Q11 z zeznaniem,
Q12 z widoczną koronką i przeciąganiem, Q13 z odrzuceniem, zachowaniem
rzeczy i blokadą Tab, Q14 z ostrzeżeniem, pominięciem opisu i konfrontacją,
Q15 z odwrotem od molo i wejściem obojga do C. To jedna kolejność natywna;
cztery przejścia hostowe obejmują też odwrotną kolejność M/K i Q11/Q12,
Biblię zabraną, wariant early i pełny opis Ireny. Regresje C i 9 Python PASS.

Niezweryfikowane w tym snapshocie: Q16–Q40, T01–T04, produkcyjne ilustracje,
audio, zapis/odczyt, profilowanie pamięci i test SE/sprzętu fizycznego.
Poniżej pozostają historyczne wyniki wcześniejszych snapshotów.

## Archiwum: etap 3c, początek kampanii

Archiwalny `PROCH.bin`: SHA256
`a9afaecc0600cff8ca4d7b6fc3f315a911ff8d4d67a5262c15ad9d0b03b98482`.
58 880 B MacBinary, fork zasobów 58 726 B; HFS 819 200 B. Kontrola forków,
zasobów CODE/DATA/RELA/SIZE i nagłówka HFS PASS. Zawartość aplikacji dokładnie
odpowiada snapshotowi uruchomionemu w profilu `stage3a-candidate2`.

Mini vMac Plus/4 MB/System 6.0.8: pełna sekwencja działań Q01–Q08 PASS.
Runner klika i przeciąga, nie ma dostępu do stanu silnika. 31 kontroli pikseli:
pełne czytanie umowy, wpis Q01, dojście przez naprawę do Opoczna i Q05,
ścieżka Konstancji z pakowaniem, Seroczynem i listem, wejście obu do B oraz
ponowny odczyt dziennika M. Surowy wynik `tests/results/stage3-a-native.json`,
zrzuty `screenshots/stage3-a-*.png`. Nie badano tu kolejności K jako pierwszej;
obie kolejności i opcjonalny adres pokrywają cztery przejścia hostowe.

W próbach wykryto i poprawiono własność zawartości walizki podczas pakowania
oraz odrysowanie celów po zmianie mikroczynności. Runner miał także błędny
wiersz dziennika, poprawiony po inspekcji rzeczywistego ekranu. Końcowe pełne
powtórzenie PASS wykonano po poprawkach, na nowym profilu.

Nadal niewykonane: pełne Q09–Q40 w modelu kampanii, cztery zakończenia
T01–T04, zapis/odczyt, produkcyjne ilustracje, audio i profilowanie pamięci.
Nie ma potwierdzenia działania na SE ani sprzęcie fizycznym. Historyczne
raporty poniżej zachowują zakres ówczesnych wersji.

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

## Archiwum: System 6.0.8 na Plusie, toolchain ze źródeł i font PL

Retro68 i Multiversal z commitów w locku są zbudowane ze źródeł i użyte do
ówczesnego `dist/`. Pierwszy fork zasobów z tego toolchaina był identyczny
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
- test natywny Executor 2000 z tego etapu: PASS;
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
