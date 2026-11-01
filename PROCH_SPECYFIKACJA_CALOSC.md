# PROCH — specyfikacja kompletna, v1.0

# PROCH — instrukcja dla Codexa

Jesteś implementatorem kompletnej gry przygodowej PROCH według powieści Szymona Bromy. Wykonaj projekt z tego pakietu jako natywną aplikację na Macintosh SE: Motorola 68000, 4 MB fizycznego RAM, ekran 512×342, monochromatyczny 1-bit, System 6.0.8. SE/30 i System 7 są dodatkowymi celami testów. To nie jest gra przeglądarkowa ani aplikacja na współczesny macOS. Nie zastępuj celu demonstracją HTML. Hostowy runner logiki jest dozwolony wyłącznie jako narzędzie testowe.

## Co masz wykonać

Zaimplementuj wszystkie 40 zadań, 43 lokacje, 45 identyfikatorów przedmiotów, zakończenia E01–E04, przełączanie Mikołaja/Konstancji, zapis i odczyt, dzienniki, podpowiedzi, okna pojemników, dialogi i interakcje. assets.json opisuje kompletny zestaw ilustracji. Użyj oryginalnej oprawy inspirowanej okienkową mechaniką MacVenture, bez kopiowania cudzych grafik i kodu.

Najpierw przeczytaj wszystkie pliki Markdown. JSON jest uporządkowanym materiałem autorskim, a nie gotowym skompilowanym skryptem gry. Przenieś zawarte w nim działania do deterministycznych reguł silnika; nie interpretuj swobodnego tekstu przez LLM podczas rozgrywki. Żaden model, sieć ani API nie jest potrzebne na docelowym komputerze.

## Kolejność autorytetu

1. Wymagania użytkownika z 01_ZALOZENIA.md i jawne reguły stanu z 03_STAN_I_MAPA.md.
2. Konkretne rozwiązania Q01–Q40, dialogi i zakończenia w tym pakiecie.
3. Rękopis jako materiał stylu i fabuły istniejących rozdziałów.
4. Streszczenie jako materiał dalszego ciągu.
5. Poglądowy plik referencyjny ekranu — nie ma pierwszeństwa przed geometrią interfejsu.

Nie wracaj samowolnie do liniowej fabuły książki, nie usuwaj swobodnego przełączania. Nowe dokumenty i rozwiązania opisane jako adaptacja są świadomą decyzją projektową. Nie dopisuj nowych osób kluczowych dla rozwiązania, magicznych reguł, przypadkowych kodów zamków ani nowego zakończenia. Rutynowe wybory struktury kodu, rozmiarów cache i narzędzi testowych rozstrzygaj sam.

## Etapy implementacji

1. Ustal i zapisz konkretny commit Retro68, skompiluj minimalną aplikację 68000. Zweryfikuj okno, mysz i rysowanie 1-bit na System 6.0.8. Nie deklaruj zgodności wyłącznie na podstawie kompilacji.
2. Wykonaj interfejs w docelowej rozdzielczości, własny font PL, ekwipunek i deterministyczny stan dwóch postaci. Demonstracja techniczna: Q09 i Q12 w L11–L15 oraz fragment K w L33. To etap, nie końcowy produkt.
3. Zaimplementuj całą logikę Q01–Q40 i wszystkie warianty z testowymi, jednoznacznie oznaczonymi grafikami. Przeprowadź automatyczne ścieżki czterech zakończeń.
4. Wytwórz i zintegruj ilustracje z manifestu. Jeśli narzędzie generowania obrazów jest dostępne, użyj go do autorskich obrazów; potem wymuś rozmiar/1-bit i zweryfikuj czytelność. Nie zastępuj ilustracji losowymi prostokątami lub ASCII w wydaniu końcowym. Jeśli generator jest niedostępny, kontynuuj kod i raportuj brak produkcyjnych grafik, nie twierdź, że wersja jest ukończona.
5. Dodaj dźwięki i subtelne warianty scen, sprawdź pamięć i zapisy, zbuduj pakiet HFS/MacBinary zachowujący resource fork. Dodaj instrukcję przeniesienia na rzeczywisty dysk Maca.
6. Dostarcz źródła, przypięte zależności, skrypt budowania, narzędzia konwersji zasobów, działającą aplikację, dane gry, raport testów oraz listę ewentualnych braków. Nie kończ po samej makiecie.

## Wymagane rezultaty

- repo/ z kodem, treścią i testami;
- dist/PROCH.bin — aplikacja MacBinary lub równoważny poprawnie opisany kontener zachowujący oba forki;
- dist/PROCH.dsk — obraz woluminu HFS z aplikacją i danymi, jeżeli narzędzia pozwalają; nie przedstawiaj go automatycznie jako gotowego obrazu urządzenia BlueSCSI z mapą partycji i sterownikiem;
- README_PL z uruchomieniem, sterowaniem i odtwarzalnym buildem;
- TEST_REPORT z konfiguracją emulatora, systemem, pamięcią, wynikami ścieżek oraz wyraźnym rozróżnieniem emulator/sprzęt;
- screenshots/ w rzeczywistych 512×342, bez retuszu.

Nie dołączaj cudzych ROM-ów ani instalacji systemu. Użyj legalnie dostępnych zasobów środowiska testowego. Jeśli ich brak, ukończ możliwe testy hostowe i kompilację, wskaż konkretną niewykonaną weryfikację. Brak ROM-u nie uzasadnia zamiany gry na stronę WWW.

Wersja językowa: polska. Dialogi z pakietu są tekstem bazowym; wolno poprawiać literówki i dopasowywać łamanie wierszy, bez zmiany sensu. Nie skracaj fabuły przez usuwanie zadań. Czas 8–12 godzin to cel projektowy do oceny w playtestach, nie gwarancja.


---

# PROCH — założenia i adaptacja

## Kontrakt użytkownika

Natywna gra na Macintosh SE/SE30, minimum 4 MB RAM, obraz 512×342 1-bit. Styl i mechanika okienkowej przygodówki MacVenture. Instalacja na dysku, bez ograniczenia do dyskietki. Dwie grywalne osoby — Mikołaj Goworek i Konstancja Korecka — jawnie oznaczone, przełączane przez gracza w dowolnym bezpiecznym momencie. Wyjątki tylko w scenach bezpośredniej współzależności, modalnych dialogach i chwilowych sekwencjach zagrożenia. Własne ekwipunki i wiedza. Fabuła nieliniowa, możliwość innych rozwiązań i finałów niż w książce.

Przyjęte przez autora: pierwszeństwo rękopisu, streszczenie dla nienapisanej części; dorosły mroczny ton, przemoc seksualna przez następstwa/narrację bez graficznego przedstawienia; logiczne zagadki, stopniowane podpowiedzi, cofnij po śmierci, brak wielogodzinnych pułapek bez wyjścia. Cel długości 8–12 godzin wymaga playtestów.

## Oś historii

Warszawa 1898. Korecki wykorzystuje ubóstwo Mikołaja i jego związek z Konstancją, wysyłając go do nawiedzanej gorzelni w Wąglanach. Konstancja trafia pod kontrolę Borakowskich. Mikołaj bada ślady Grety; Konstancja odzyskuje samodzielność. Dwie osie kłamstwa — opowieść o rzekomym romansie i wiadomość o śmierci Konstancji — spotykają się ze śmiertelnym niebezpieczeństwem stawu. Po kryzysie ujawnienie spisku, oczyszczenie Mikołaja i decyzja, czy doprowadzić do pochowania Grety. Epilog nie nagradza automatycznie romansem.

## Uzgodnienia redakcyjne wersji 1.0

- W tekście gry konsekwentnie „Greta von Platter”; rękopis używa również „Gretta”. To ujednolicenie pisowni, nie nowa osoba.
- Biblioteka i portret wysoko nad drzwiami pochodzą z rękopisu; nie przenosimy portretu do hallu ze streszczenia.
- Pierwszy staw i widzenie obozu adaptujemy z rękopisu; nie dublujemy go później jako identycznego snu ze streszczenia.
- Mikołaj ma od początku broszkę motyla. Rękopiśmienne zagubienie zastępujemy gwarancją zachowania kluczowej pamiątki, aby nie tworzyć martwej ścieżki.
- Ucieczka z Sopotu uwzględnia atak Ireny i pomoc Adama. Śmierć Ireny jest wydarzeniem fabularnym, nie nagrodą za sprawność gracza. Scena może zostać skrócona przez opcję treści.
- Los Eleonory po brutalnej konfrontacji nie jest w przytoczonym rękopisie definitywnie rozstrzygnięty. Dla dalszego ciągu gry przeżywa i dochodzi do siebie; na przyjęciu ma ślad urazu wyłącznie w wariancie confrontation. To jawny most adaptacyjny, nie twierdzenie o ukończonej powieści.
- Pomoc Adama przy ucieczce może być chwilowo szczera, ale nie usuwa jego późniejszego udziału w oszustwie. Nie traktować jej jako dowodu niewinności całej rodziny.
- Luiza matka Konstancji i Luiza służąca są rozdzielone identyfikatorami, wyglądem i opisami. Matka w tej grze występuje jako fotografia i temat dokumentów.
- Marianna jest znana z plebanii jeszcze przed zakończeniem, dzięki czemu epilog nie wprowadza jej nagle.
- Duch jest realnym doświadczeniem bohatera, ale nie tworzymy systemu magii. Pochówek zamyka nawiedzenie w konwencji opowieści; nie ma rytuału czterech artefaktów.
- Pojawienie się Konstancji w kryzysie nad stawem, możliwość ratunku, korespondencja, kopie dokumentów, alternatywne przyjęcie bez małżeństwa i współpraca obojga są nowymi rozwinięciami gry.
- Finał sądowy i mechanizm oszustwa finansowego są skrótami literackimi. Nie deklarujemy historycznej dokładności prawa, rynku czy konkretnych procedur. Nie dodajemy rzeczywistych firm ani notowań.
- Nie używać marki roweru Łucznik jako detalu historycznego 1898; rysować i nazywać po prostu rowerem. Nie dodawać technologii steampunkowej, której powieść nie wymaga.

## Doświadczenie gracza

Pierwszoosobowe statyczne sceny, badanie przedmiotów, operowanie nimi, rozmowy i dedukcja. Żadnego walkowego RPG, parametrów siły, rzutów kością lub zręcznościowego sterowania postacią. Dźwięki mają wspierać, nigdy przekazywać wyłączną wskazówkę. Wrogie postacie nie są automatami wymiany klucz–przedmiot: najpierw rozmowa, motywacja i dowód.

Przełączanie nie jest teleportacją postaci. Obie mają niezależne miejsce pobytu. Każda wiadomość ma nadawcę, pośrednika, warunek doręczenia i odczytu. Portrety, imię i nagłówek dziennika zawsze pokazują aktywną osobę. Brak globalnego wskaźnika dobra/zła i punktów za traumę.

## Źródła fabularne

Szymon Broma „Proch” V 5.6.9.docx.pdf — 209 stron rękopisu; streszczenie rozdziałów całej powieści, ©2019. Kopie wejściowych PDF w katalogu sources, bez modyfikacji. Specyfikacja jest autorską adaptacją wybranych zdarzeń, nie transkrypcją wszystkich scen powieści. Zatwierdzony podgląd 512×342 służy jako wzorzec tonu i rastra, nie wymiarów każdego panelu.


---

# PROCH — scenariusz wykonawczy i questy

Wersja 1.0, 1 listopada 2026. Q01–Q40 to identyfikatory zadań, a nie rozdziały powieści. Teksty dialogów w krokach są dosłownymi etykietami wyborów. Zadania Q02, Q20, Q22–Q23, Q26–Q27, Q29 są opcjonalne. Q36–Q38 są opcjonalną całością przy dopuszczonym otwartym zakończeniu. Pozostałe są główną ścieżką. Listy wymagań oznaczają AND, z dodatkowymi warunkami opisanymi w dokumencie stanu. Wszystkie rozwinięcia zagadkowe są adaptacją.

## Q01 — Cena obietnicy

Postać: M; etap: A; wymagania: brak; lokacje: L01, L02.

Przedmioty: I01, I02, I03.

1. Porozmawiaj z Koreckim: „Co właściwie mam zbadać?”

2. Obejrzyj umowę na biurku: zatrudnienie w Wąglanach, obietnica zgody na ślub, brak gwarancji bezpieczeństwa.

3. Wybierz „Podejmę się zadania”. Otrzymujesz I01 umowę i I02 bilet.

4. Marian przy drzwiach przekazuje I03 broszkę Konstancji oraz adres redakcji.

**Wynik:** q01_done; M zna cel Wąglany.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Najpierw poznaj warunki.

2. Zapytaj o zadanie i przeczytaj dokument.

3. Przyjmij zlecenie, potem porozmawiaj z Marianem.

## Q02 — Adres zwrotny

Postać: M; etap: A; wymagania: Q01; lokacje: L04.

Przedmioty: I01.

1. Pokaż Izydorowi umowę.

2. Zapytaj „Czy mogę zostawić adres dla Konstancji?”.

3. Wybierz „Zapisz: gorzelnia w Wąglanach, do rąk własnych”.

**Wynik:** q02_done; address_left=true. Zadanie opcjonalne; bez niego K uzyska adres później z księgi korespondencji.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Izydor może być łącznikiem.

2. Pokaż mu dokąd jedziesz.

3. Zostaw adres w redakcji.

## Q03 — Spóźniony podróżny

Postać: M; etap: A; wymagania: Q01; lokacje: L05, L06.

Przedmioty: I02.

1. Obejrzyj rozkład i znajdź połączenie w kierunku Opoczna.

2. Użyj biletu na bramce; konduktor wskazuje przedział.

3. W przedziale porozmawiaj z ciężarną podróżną i zaoferuj miejsce.

4. Gdy pociąg staje, zapytaj konduktora o przyczynę.

**Wynik:** q03_done; dostęp L07; krystyna_saw_kindness=true.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Bilet musi odpowiadać trasie.

2. Pomoc podróżnej rozpocznie rozmowę.

3. Pokaż bilet, ustąp miejsca, zapytaj o postój.

## Q04 — Zawór zamiast sprężarki

Postać: M; etap: A; wymagania: Q03; lokacje: L07.

Przedmioty: I04, I05.

1. Porozmawiaj z maszynistą i uzyskaj zgodę na oględziny.

2. Obejrzyj sprężarkę oraz zawór: narrator wskazuje osad przy zaworze.

3. Poproś maszynistę o odcięcie dopływu i potwierdzenie bezpiecznego stanu maszyny.

4. Weź I04 klucz i I05 szmatę ze skrzynki; użyj klucza na zaworze.

5. Użyj szmaty na wyjętym wkładzie; użyj wkładu na korpusie i klucza do zamknięcia.

6. Poproś o próbę. Zwróć narzędzia; wejdź do przedziału.

**Wynik:** q04_done; train_repaired=true. Abstrakcyjna zagadka, nie instrukcja obsługi prawdziwego parowozu.

**Błędne działania:** Próba odkręcania działającej maszyny: maszynista zatrzymuje rękę. Bez śmierci, bez postępu.

**Podpowiedzi:**

1. Maszyna nie musi być zatarta.

2. Przyjrzyj się zaworowi i osadowi.

3. Po zabezpieczeniu maszyny wyjmij, oczyść i zamontuj wkład.

## Q05 — Przyjazd

Postać: M; etap: A; wymagania: Q04; lokacje: L08, L09.

Przedmioty: I01.

1. Pokaż woźnicy umowę.

2. Wybierz Wąglany.

3. Obejrzyj most i bramę. Zakończ podróż przy karczmie.

**Wynik:** q05_done; M gotowy do etapu B.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Dokument mówi dokąd jedziesz.

2. Woźnica rozpozna nazwę fabryki.

3. Pokaż umowę i wybierz Wąglany.

## Q06 — Własne rzeczy

Postać: K; etap: A; wymagania: brak; lokacje: L03, L25.

Przedmioty: I06, I07, I08.

1. Obejrzyj fotografię Luizy: matka, nie służąca z Seroczyna.

2. Otwórz szkatułkę i zabierz I06 fotografię oraz I07 dokument podróżny.

3. Spakuj je do I08 walizki.

4. Wybierz „Wyjazd”. Przerywnik przenosi K do Seroczyna.

**Wynik:** q06_done; K L25.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Zabierz rzeczy osobiste.

2. Sprawdź szkatułkę.

3. Fotografia i dokument trafiają do walizki.

## Q07 — Furtka to nie wolność

Postać: K; etap: A; wymagania: Q06; lokacje: L25, L26, L27, L28, L29.

Przedmioty: I09.

1. Porozmawiaj z Ireną o spacerze: pozwala wejść do parku, nie poza majątek.

2. W kuchni poproś Luizę służącą o wodę. Otrzymujesz I09 dzban.

3. Zanieś dzban ogrodnikowi; pokazuje niezaryglowaną furtkę gospodarczą.

4. Przejdź na drogę i poproś wieśniaka o podwiezienie.

5. Dowiedz się, że boi się Borakowskich. Wróć do parku i zanotuj, że zależność ekonomiczna blokuje ucieczkę.

**Wynik:** q07_done; pierwsza próba kończy się fabularnie, bez resetu.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Problemem jest także otoczenie dworu.

2. Porozmawiaj ze służbą i człowiekiem na drodze.

3. Zanieś wodę ogrodnikowi, wyjdź furtką, poproś o pomoc.

## Q08 — List, który nie wyszedł

Postać: K; etap: A; wymagania: Q07; lokacje: L25, L26.

Przedmioty: I10, I11.

1. Weź I10 papier i I11 ołówek z kufra.

2. Użyj papieru na ołówku; wybierz adresata „Izydor Jelinek”.

3. Połóż list na stoliku pocztowym i wróć do pokoju.

4. Wróć na korytarz: koperta leży otwarta, bez znaczka. Obejrzyj ją.

5. Zapytaj Irenę o list. Jej odpowiedź potwierdza kontrolę korespondencji.

6. W pokoju wybierz „Jadę do Sopotu”, po ogłoszeniu wyjazdu przez Eleonorę.

**Wynik:** q08_done; K gotowa B; intercepted_letter=true.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Zwykła poczta może nie być prywatna.

2. Sprawdź co stało się z kopertą.

3. Napisz do Izydora, sprawdź stolik i zapytaj Irenę.

## Q09 — Klucze zmarłego stróża

Postać: M; etap: B; wymagania: Q05; lokacje: L11, L13.

Przedmioty: I12, I13, I14.

1. Porozmawiaj z Florkiem o Zenku, pokoju i dostępie do fabryki.

2. Wejdź do pokoju; zabierz I12 mosiężny kluczyk z biurka.

3. Użyj I12 na szufladzie; otwórz ją.

4. Weź I13 pęk kluczy oraz obejrzyj I14 Biblię. Biblię można zabrać.

5. Zapytaj Florka o rower; odblokuj przejazdy między Wąglanami a Białaczowem.

**Wynik:** q09_done; brama i hala dostępne.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Mały klucz otwiera coś bliskiego.

2. Obejrzyj biurko.

3. Otwórz szufladę kluczykiem i zabierz pęk kluczy.

## Q10 — Nie jestem ich człowiekiem

Postać: M; etap: B; wymagania: Q09; lokacje: L10.

Przedmioty: I01.

1. Zapytaj Tolka, dlaczego jest wrogi.

2. Wybierz „Rozumiem, dlaczego im nie ufasz”.

3. Pokaż umowę: zlecenie pochodzi od Koreckiego, nie od policji.

4. Wybierz „Powiem, o co mnie pytali”. Celina zaprasza do stołu.

**Wynik:** q10_done; tavern_trust=true; wskazówka o rannym robotniku.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Nie kupuj zaufania pieniędzmi.

2. Wyjaśnij swoje zlecenie.

3. Wysłuchaj Tolka, pokaż umowę i odpowiedz szczerze.

## Q11 — Ktoś obok ciebie

Postać: M; etap: B; wymagania: Q10; lokacje: L16.

Przedmioty: I15.

1. Porozmawiaj z Marysią: pyta o niewidoczną kobietę.

2. Zapytaj „Jak ma na imię?” zamiast wyśmiewać dziecko.

3. Poproś matkę o rozmowę z poszkodowanym.

4. Zapytaj robotnika, co pamięta: zimno, obecność kobiety, utrata sił.

5. Zapis automatycznie tworzy I15 zeznanie robocze.

**Wynik:** q11_done; M zna imię Greta.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Dziecko patrzy nie na ciebie.

2. Zapytaj o osobę stojącą obok.

3. Poznaj imię Grety i wysłuchaj robotnika.

## Q12 — Nienaruszone wejścia

Postać: M; etap: B; wymagania: Q09; lokacje: L13, L15.

Przedmioty: I16, I17, I18, I19.

1. Weź I16 nitkę, I17 wosk i I18 papierowy pasek z warsztatu.

2. Obejrzyj drzwi i okno pokoju.

3. Użyj paska na drzwiach; wosku i nitki na oknie.

4. Wybierz „Odpocznij do rana”.

5. Obejrzyj oba nienaruszone znaczniki; podnieś I19 koronkę z podłogi.

**Wynik:** q12_done; M posiada pierwszy fizyczny ślad.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Sprawdź hipotezę o intruzie.

2. Oznacz oba wejścia przed snem.

3. Załóż znaczniki, odpocznij, porównaj ich stan i zabierz koronkę.

## Q13 — Imię w ciemności

Postać: M; etap: B; wymagania: Q11, Q12; lokacje: L12.

Przedmioty: I19.

1. Wejdź do korytarza: światło przygasa, wejście się zatrzaskuje.

2. Obejrzyj cień, aby usłyszeć ostrzeżenie narratora: walka nie pomoże.

3. Wybierz Rozmawiaj na cieniu i temat „Greto, chcę poznać twoją historię”.

4. Po ustąpieniu zjawiska otwórz drzwi i wyjdź na dziedziniec.

**Wynik:** q13_done; M gotowy C.

**Błędne działania:** Uderz powoduje odrzucenie i powrót do początku tej sceny, bez utraty przedmiotów. Blokada przełączania wyłącznie na czas sceny.

**Podpowiedzi:**

1. Znasz już jej imię.

2. Spróbuj przemówić zamiast walczyć.

3. Rozmawiaj z cieniem, używając imienia Grety.

## Q14 — Okno na wolność

Postać: K; etap: B; wymagania: Q08; lokacje: L30, L31.

Przedmioty: I07, I08.

1. Rozmowa z Ireną przechodzi w atak; narracyjna sekwencja obrony i wejścia Adama. Irena ginie zgodnie z rękopisem, bez zręcznościowej minigry.

2. Adam otwiera okno; spakuj dokument i walizkę. Brakujące rzeczy Adam podaje automatycznie.

3. Wybierz „Wyjdź teraz” albo „Zostań przy drzwiach”. Pierwszy wariant to wcześniejsza ucieczka; drugi prowadzi do skróconej sceny konfrontacji z Eleonorą z rękopisu.

4. Użyj wyjścia przez okno. Obie drogi prowadzą do ogrodu i Bergen Strasse.

**Wynik:** q14_done; escape_variant=early lub confrontation; Adam pomaga, ale nie otrzymuje automatycznie zaufania.

**Błędne działania:** Nie ma nagrody za przemoc. Sekwencja ma ostrzeżenie treści i przycisk skrócenia; skutki fabularne identyczne. Nie określamy śmierci Eleonory — rękopis jej nie potwierdza.

**Podpowiedzi:**

1. Otwarte okno prowadzi poza dom.

2. Najważniejsze są dokument i wyjście.

3. Spakuj walizkę i wyjdź oknem.

## Q15 — Z dala od świateł

Postać: K; etap: B; wymagania: Q14; lokacje: L31, L32, L33.

Przedmioty: brak.

1. Obejrzyj tabliczkę i wybierz ścieżkę ku odgłosowi morza.

2. Na plaży obejrzyj światła molo: narrator ostrzega o możliwości rozpoznania.

3. Wybierz północną linię brzegu. Wycieńczenie, sieci i ratunek są przerywnikiem.

4. W chacie po przebudzeniu wybierz „Powiem ci, co się stało”.

**Wynik:** q15_done; K bezpieczna; K gotowa C.

**Błędne działania:** Wejście ku molo powoduje zauważenie znajomego powozu i bezpieczny odwrót. Bez śmierci za wybór kierunku.

**Podpowiedzi:**

1. Szukaj morza, potem oddal się od ludzi dworu.

2. Na plaży światła wskazują zabudowania.

3. Idź ku morzu, potem na północ; porozmawiaj z rybakiem.

## Q16 — Wizyta na plebanii

Postać: M; etap: C; wymagania: Q13; lokacje: L17, L18.

Przedmioty: I20.

1. Porozmawiaj z Marianną o siostrze podróżującej pociągiem.

2. Porozmawiaj z proboszczem o nawiedzeniu: nie oferuje magicznego przedmiotu, zaleca świadków i poznanie historii.

3. Na placu porozmawiaj z Krystyną; pokaż koronkę.

4. Przyjmij I20 zaproszenie do pałacowej biblioteki.

**Wynik:** q16_done; dostęp do L19 i L20.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Prześledź rodzinę i historię okolicy.

2. Krystyna może znać stare portrety.

3. Pokaż koronkę Krystynie i przyjmij zaproszenie.

## Q17 — Kobieta nad drzwiami

Postać: M; etap: C; wymagania: Q16; lokacje: L19, L20.

Przedmioty: I19, I20, I21.

1. Pokaż zaproszenie służącemu.

2. Obejrzyj portret; detale sukni są za wysoko.

3. Użyj drabiny na portrecie i wejdź.

4. Użyj koronki na sukni w zbliżeniu: wzór jest identyczny.

5. Zejdź i porozmawiaj z Ludwikiem, który wchodzi: „Kogo przedstawia obraz?”.

6. Obejrzyj katalog pod literą P: karta Platter wskazuje tom III, kartę 27. Weź I21 odpis oznaczenia.

**Wynik:** q17_done; M zna pełną tożsamość Grety von Platter. Portret jednorazowo zmienia się po zejściu.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Dopasuj ślad do sukni.

2. Potrzebujesz drabiny i katalogu.

3. Porównaj koronkę na górze, potem sprawdź katalog Platter.

## Q18 — Historia urwana w połowie

Postać: M; etap: C; wymagania: Q17; lokacje: L20.

Przedmioty: I21, I22.

1. Użyj odpisu katalogowego na regale kronik.

2. Otwórz tom III i wybierz kartę 27.

3. Przeczytaj opowieść o portrecie, wyjeździe narzeczonego i zniknięciu Grety.

4. Obejrzyj margines: stary trakt i staw wskazano na mapie dóbr. Zabierz I22 odrys mapy.

**Wynik:** q18_done; dostęp L22; rodzinna legenda to hipoteza, nie pewna prawda.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Katalog podaje konkretny tom.

2. Przeczytaj także margines.

3. Tom III, karta 27, następnie odrysuj mapę.

## Q19 — Ślad prowadzi do wody

Postać: M; etap: C; wymagania: Q18; lokacje: L22, L23, L24.

Przedmioty: I19, I22, I23.

1. Użyj mapy na ścieżce; odnajdź koronkę na jeżynie.

2. Obejrzyj staw i zwalony pień.

3. Sięgnięcie po koronkę uruchamia krótką kanoniczną sekwencję poślizgnięcia, wydostania się i widzenia obozu; nie jest śmiercią.

4. W widzeniu obejrzyj torbę i stare uzbrojenie, niczego nie zabieraj do rzeczywistego ekwipunku.

5. Idź ku światłu między drzewami. Wracasz na ścieżkę z I23 notatką o korzeniach i uskoku.

**Wynik:** q19_done; pond_seen=true; M gotowy D.

**Błędne działania:** Sekwencja zablokowana dla przełączania; zawsze ma wyjście. Nie przenosi zabytkowej broni do ekwipunku.

**Podpowiedzi:**

1. Ślady są wskazówką i przynętą.

2. Porównaj mapę z lasem.

3. Idź po śladach, obejrzyj pień, po widzeniu wyjdź ku światłu.

## Q20 — Słowo uczciwe

Postać: M; etap: C; wymagania: Q17; lokacje: L18, L20.

Przedmioty: I03.

1. Porozmawiaj z Krystyną o Warszawie.

2. Wybierz „Jestem związany z Konstancją” i pokaż broszkę.

3. Wybierz „Nie chcę budować przyjaźni na kłamstwie”.

**Wynik:** q20_done; honest_krystyna=true. Opcjonalne, dostępne również D przed rozmową w ogrodzie.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Niejasność służy spiskowcom.

2. Powiedz Krystynie o Konstancji.

3. Pokaż broszkę i jasno nazwij związek.

## Q21 — Zwykła suknia

Postać: K; etap: C; wymagania: Q15; lokacje: L33.

Przedmioty: I24, I25, I26.

1. Zapytaj rybaka o ubranie odpowiednie do pracy i podróży.

2. Weź I24 tkaninę oraz I25 igłę z nicią ze skrzyni za jego zgodą.

3. Użyj obu na stole: wybierz prosty krój, zaznacz długość według starej spódnicy, zszyj.

4. Załóż I26 prostą suknię przez użycie na portrecie K.

**Wynik:** q21_done; disguise=true.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Rybak może udostępnić materiał.

2. Pracuj przy stole.

3. Tkanina i igła na stole, potem załóż uszytą suknię.

## Q22 — Sieć i zaufanie

Postać: K; etap: C; wymagania: Q21; lokacje: L34.

Przedmioty: I25, I27.

1. Porozmawiaj z sąsiadem rybaka.

2. Obejrzyj uszkodzoną sieć; trzy luźne końce mają widoczną kolejność od brzegu.

3. Użyj igły i nici na sieci; połącz lewy koniec ze środkowym, środkowy z prawym, zatwierdź.

4. Sąsiad obiecuje przekazać korespondencję poza domem Borakowskich; daje I27 adres swojego krewnego w Warszawie.

**Wynik:** q22_done; safe_courier=true. Opcjonalne; do powrotu niepotrzebne.

**Błędne działania:** Błędne połączenie daje „Oczko się zaciska. Rozplątuję nić” i reset samej układanki.

**Podpowiedzi:**

1. Pomoc buduje zaufanie.

2. Wzór przy brzegu pokazuje układ.

3. Połącz lewy ze środkowym, następnie środkowy z prawym.

## Q23 — Żyję

Postać: K; etap: C; wymagania: Q22; lokacje: L33, L34.

Przedmioty: I10, I11, I27, I28.

1. Napisz list do Izydora na zachowanym papierze; w chacie jest zapas, jeśli papier wykorzystano.

2. Wybierz treść „Żyję. Nie ufaj wieściom o mojej śmierci. Przekaż Mikołajowi”.

3. Dodaj prywatne wspomnienie broszki motyla jako potwierdzenie.

4. Przekaż I28 list sąsiadowi. Otrzymaj ustne potwierdzenie przyjęcia.

**Wynik:** q23_done; letter_sent=true. Doręczenie następuje przy wejściu D, nie po realnym czasie.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Potrzebujesz zaufanej drogi.

2. Izydor zna oboje, a broszka potwierdzi autora.

3. Przekaż przez sąsiada list do Izydora ze wspomnieniem motyla.

## Q24 — Powrót z wybrzeża

Postać: K; etap: C; wymagania: Q21; lokacje: L33, L35, L05, L04.

Przedmioty: I07, I29.

1. Powiedz rybakowi o zamiarze odnalezienia Mikołaja.

2. Przyjmij I29 pieniądze na podróż; rybak nie uzależnia pomocy od naprawy sieci.

3. Pokaż dokument kasjerowi i kup bilet do Warszawy.

4. W redakcji zapytaj Izydora o Mikołaja. Jeśli address_left, dostajesz adres natychmiast; inaczej otwórz za zgodą księgę wysyłek pod Wąglany i znajdź korespondencję Koreckiego.

5. Wybierz podróż do Opoczna.

**Wynik:** q24_done; K L08; K gotowa D.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Rybak chce pomóc.

2. Adres można ustalić u Izydora.

3. Kup bilet i sprawdź w redakcji wpis Wąglany.

## Q25 — Fotografia nie mówi wszystkiego

Postać: K; etap: D; wymagania: Q24; lokacje: L09, L10.

Przedmioty: I30.

1. Zapytaj Tolka o Mikołaja i Krystynę.

2. Porozmawiaj z fotografem; obejrzyj I30 odbitkę z jarmarku.

3. Zapytaj „Czy słyszał pan, że są zaręczeni?”. Fotograf przyznaje, że tylko zrobił zdjęcie.

4. Wybierz „Sprawdzę to sama”. Zachowaj odbitkę wypożyczoną za zgodą fotografa.

**Wynik:** q25_done; K rozróżnia obserwację i plotkę.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Zdjęcie pokazuje spotkanie, nie obietnicę.

2. Zapytaj, co fotograf naprawdę wie.

3. Obejrzyj odbitkę i zapytaj o źródło informacji o zaręczynach.

## Q26 — Wiadomość do rąk własnych

Postać: M; etap: D; wymagania: Q19; lokacje: L11, L13.

Przedmioty: I28.

1. Porozmawiaj z Florkiem po wejściu D. Jeśli letter_sent, przekazuje list od Izydora.

2. Otwórz list i przeczytaj wzmiankę o broszce.

3. Wybierz „To jej słowa”.

**Wynik:** q26_done; m_knows_alive=true. Dostępne tylko letter_sent, opcjonalne.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Florek ma dla ciebie pocztę.

2. Sprawdź osobisty szczegół.

3. Przeczytaj cały list i rozpoznaj wspomnienie broszki.

## Q27 — Przygotowanie nad staw

Postać: M; etap: D; wymagania: Q19; lokacje: L15, L17, L23.

Przedmioty: I23, I31, I32.

1. Pokaż proboszczowi notatkę o korzeniach; zaleca nie wchodzić do wody samotnie.

2. Weź I31 linę i I32 hak z warsztatu za zgodą Florka.

3. Na brzegu obejrzyj głaz: stabilny punkt na suchym gruncie.

4. Użyj liny na głazie; hak pozostaje w ekwipunku, a zamocowana lina w świecie.

**Wynik:** q27_done; rescue_rig=true. Opcjonalne, informacja o linie dostępna także K w sekwencji ratunkowej.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Staw ma uskok i splątane korzenie.

2. Przygotuj pomoc z brzegu.

3. Weź linę i hak; umocuj linę przy głazie.

## Q28 — Rozmowa za żywopłotem

Postać: M; etap: D; wymagania: Q19; lokacje: L21.

Przedmioty: I28.

1. Wejdź w ogród i obejrzyj żywopłot: słyszysz urywek o otruciu Konstancji.

2. Jeśli m_knows_alive, wybierz „Mam jej list” i pokaż go. Jeśli honest_krystyna, wybierz „Krystyno, powiedz mi prawdę”; Krystyna przyznaje, że Konstancja uciekła.

3. Bez tych flag dostępne „Uwierzę” lub „Sprawdzę u Izydora”. Sprawdzenie przywraca swobodę i otwiera Q29, nie zużywa czasu.

4. Gdy wybierzesz „Idę nad staw”, pojawia się jawny komunikat zamknięcia etapu. M czeka na zakończenie Q25 przez K.

5. Zatwierdź przejście: ustaw crisis_mode=calm, jeśli m_knows_alive lub honest_krystyna lub direct_contact; inaczej despair.

**Wynik:** q28_done; uruchamia Q30. Wymuszona postać tylko od rozpoczęcia kryzysu.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Urywki rozmowy nie muszą być prawdą.

2. List, szczerość Krystyny lub kontakt z Konstancją mogą obalić plotkę.

3. Pokaż list, poproś Krystynę o prawdę albo odłóż wyjazd i sprawdź u Izydora.

## Q29 — Spotkanie zamiast plotki

Postać: K; etap: D; wymagania: Q25; lokacje: L11, L13.

Przedmioty: I30.

1. Zapytaj Florka o pokój Mikołaja.

2. Wybierz „Zostawię wiadomość, że czekam w karczmie”.

3. Przełącz na M i odczytaj wiadomość w pokoju.

4. Jako M wejdź do karczmy i porozmawiaj z K: wyjaśnij zdjęcie i zadanie Koreckiego.

**Wynik:** q29_done; direct_contact=true; m_knows_alive=true. Dostępne przed zatwierdzeniem Q28; M może zakończyć Q28 dopiero po powrocie do ogrodu.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Można dotrzeć do samego Mikołaja.

2. Florek wie, gdzie go znaleźć.

3. Zostaw wiadomość w pokoju, odczytaj jako M i spotkaj się w karczmie.

## Q30 — Martwa woda

Postać: MK; etap: D; wymagania: Q25, Q28; lokacje: L23.

Przedmioty: I31, I32.

1. W crisis_mode=calm M pozostaje na brzegu. Krystyna ujawnia spisek; po wezwaniu zjawy podchodzi do wody i osuwa się. W despair M jest w wodzie, Krystyna próbuje go wyprowadzić i osuwa się z uskoku.

2. Automatycznie K dociera na ścieżkę, widząc konia Krystyny; sterowanie przechodzi na K. Komunikat „Teraz: Konstancja — ratunek”.

3. Jeśli rescue_rig, wybierz linę, potem „Podaj Krystynie”. Hak z warsztatu został przy linie jako element przygotowania.

4. Jeśli brak rescue_rig, zbadaj korzeń na brzegu: leży tam długi suchy konar. Użyj go jako podpory, wezwij M do współpracy, podaj koniec Krystynie.

5. Gracz może zamiast tego wybrać „Biegnij po pomoc”, z jasnym ostrzeżeniem o utracie kontaktu z tonącą. Drugie potwierdzenie prowadzi do wariantu tragicznego.

6. Przy ratowaniu wybierz „Ciągnij razem z Mikołajem” dopiero po podaniu podpory. Wynik: Krystyna żyje; przy odejściu: ginie, M zostaje zatrzymany.

**Wynik:** q30_done; krystyna_alive=true/false; etap E. Ani szybkość klikania, ani przypadek nie decydują.

**Błędne działania:** Wejście K do wody: śmierć z natychmiastowym Cofnij przed wyborem. Niepowiązane akcje nie przybliżają śmierci. Odejście to świadomy wybór fabularny, nie zwykła przegrana.

**Podpowiedzi:**

1. Pozostań na stabilnym brzegu.

2. Lina albo długi konar pozwolą sięgnąć do tonącej.

3. Podaj podporę, wezwij M do współpracy i ciągnij razem.

## Q31 — Zaproszenie do pułapki

Postać: K; etap: E; wymagania: Q30; lokacje: L02, L03, L36.

Przedmioty: I33.

1. Po śmierci Krystyny: scena oskarżenia M, powrotu K i oświadczyn. K może przyjąć ślub (book_marriage=true) albo przyjąć jedynie zaproszenie na przyjęcie jako pretekst (false). Po uratowaniu: K odmawia małżeństwa, ale dostaje zaproszenie od ojca.

2. Porozmawiaj z Klarą: radzi sprawdzić, dlaczego rodzina tak pilnie potrzebuje zgody.

3. Weź I33 zaproszenie i użyj przy wejściu do sali.

4. W obu wersjach celem jest zdobycie dowodów, nie obowiązkowe zawarcie małżeństwa.

**Wynik:** q31_done; przyjęcie/wesele dostępne; M w areszcie albo na plebanii.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Oficjalne przyjęcie daje dostęp do domu.

2. Klara zna rodzinne naciski.

3. Porozmawiaj z Klarą i użyj zaproszenia.

## Q32 — Za bocznymi drzwiami

Postać: K; etap: E; wymagania: Q31; lokacje: L36, L37.

Przedmioty: I34, I35.

1. Obejrzyj drzwi bocznego gabinetu; usłysz imię Mikołaja.

2. Wybierz Nasłuchuj w menu Obejrzyj. Trzy wypowiedzi ujawniają oszustwo dotyczące romansu, plan finansowy i wątpliwości co do ojcostwa Karola.

3. Po odejściu rozmówców wejdź do gabinetu; otwórz teczkę na biurku.

4. Weź I34 kopię zlecenia i I35 list Borakowskich z odniesieniem do fałszywej informacji o Konstancji. Dokumenty dopisane dla gry.

5. Wybierz „Skopiuj szczegóły do dziennika” — kopia wiedzy chroni przed utratą przedmiotu.

**Wynik:** q32_done; conspiracy_evidence=true; K wie, że Karol nie jest biologicznym ojcem, nie zna jeszcze tożsamości Mariana.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Usłyszysz znajome imię.

2. Podsłuchaj całość, potem sprawdź teczkę.

3. Zbierz oba dokumenty i zrób notatki.

## Q33 — Do północy

Postać: K; etap: E; wymagania: Q32; lokacje: L36, L04.

Przedmioty: I34, I35.

1. Wybierz „Ostrzegę Karola” albo „Nie powstrzymam jego decyzji”.

2. Przy ostrzeżeniu pokaż kopię zlecenia i list; Karol zleca wstrzymanie transakcji. karol_ruined=false.

3. Przy odmowie wybierz przy zegarze „Zostań do północy”. Dopiero ta czynność uruchamia wiadomość o katastrofie finansowej. karol_ruined=true.

4. Wyjdź przez przedpokój i jedź do Izydora z dowodami.

**Wynik:** q33_done; etap F po krótkiej reakcji M. Finansowy mechanizm to uproszczenie świata fikcyjnego, nie symulacja historycznej giełdy.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Zegar rusza fabularnie dopiero na twoją decyzję.

2. Możesz ostrzec Karola dokumentami.

3. Pokaż dowody albo świadomie zaczekaj do północy, potem idź do Izydora.

## Q34 — Świadkowie zamiast pogłosek

Postać: K; etap: F; wymagania: Q33; lokacje: L04, L17, L38.

Przedmioty: I15, I35, I36.

1. Pokaż Izydorowi list spiskowców; uzyskujesz jego pomoc i dostęp do rozmowy z M.

2. Porozmawiaj z M w pokoju rozmów; poznaj dokładną kolejność wydarzeń nad stawem.

3. Poproś proboszcza o zeznanie o wcześniejszych spotkaniach; otrzymaj I36 oświadczenie.

4. Jeśli Krystyna żyje, poproś ją o podpis pod własnym zeznaniem; zastępuje sporne relacje osób trzecich.

**Wynik:** q34_done; dossier_ready=true.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Potrzebujesz faktów i świadków.

2. Izydor pomoże je uporządkować.

3. Zbierz relację M i oświadczenie proboszcza; dołącz zeznanie Krystyny, jeśli żyje.

## Q35 — Rozprawa

Postać: K; etap: F; wymagania: Q34; lokacje: L39.

Przedmioty: I35, I36.

1. Przed sądem wybierz „Wyjaśnię pochodzenie fałszywej wiadomości” i przedstaw I35.

2. Przedstaw oświadczenie proboszcza i relację M.

3. Jeśli Krystyna żyje, przywołaj jej zeznanie; sprawa dotyczy manipulacji i zdarzenia nad stawem. Jeśli nie żyje, jest to obrona M przed oskarżeniem o zabójstwo.

4. Na pytanie o fotografię odpowiedz „Potwierdza spotkanie, nie zaręczyny”.

5. Sąd kończy etap: M odzyskuje wolność lub zostaje oczyszczony z podejrzeń.

**Wynik:** q35_done; m_free=true. Procedura jest literackim skrótem, nie rekonstrukcją prawa.

**Błędne działania:** Błędna odpowiedź wywołuje pytanie uzupełniające; można poprawić. Brak losowego wyroku lub trwałej blokady.

**Podpowiedzi:**

1. Oddziel dowód od interpretacji.

2. List wyjaśnia manipulację; świadkowie opisują zdarzenia.

3. Pokaż list, przedstaw świadków i wyjaśnij ograniczenia fotografii.

## Q36 — Ostatni ślad

Postać: M; etap: F; wymagania: Q35; lokacje: L17, L20.

Przedmioty: I21, I22, I37.

1. Zapytaj proboszcza, jak zakończyć sprawę stawu.

2. W bibliotece użyj odpisu katalogowego i otwórz dalszą kartę tomu: Krystyna przed kryzysem zostawiła zakładkę, także w wariancie jej śmierci.

3. Przeczytaj notę o zbrodni i nieodnalezionym ciele. Nie pokazuj sceny napaści.

4. Połącz mapę z notą w dzienniku: staw jest miejscem poszukiwania szczątków, nie portalem.

5. Utwórz I37 dossier Grety.

**Wynik:** q36_done; greta_history=true.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Rodzinna legenda była niepełna.

2. Sprawdź dalsze karty i zakładkę.

3. Połącz notę, mapę i portret w dossier.

## Q37 — Nie schodź tam sam

Postać: M; etap: F; wymagania: Q36; lokacje: L11, L15, L23.

Przedmioty: I37, I38.

1. Pokaż Florkowi dossier; poproś o strażaków i pompę. Zespół zgadza się pomóc.

2. W warsztacie przygotuj I38 zestaw do wypompowania: sprawdź uszczelkę, połącz dwa oznaczone odcinki węża z odpowiadającymi gniazdami.

3. Na brzegu wskaż wylot z dala od stanowiska i poczekaj na sygnał strażaka.

4. Wybierz „Rozpocznij wypompowywanie”. Przerywnik stopniowo odsłania dno.

5. Strażacy wydobywają ciało Grety; w wariancie tragicznym również Krystyny uwikłanej w korzenie.

**Wynik:** q37_done; remains_recovered=true.

**Błędne działania:** Nie pozwalaj graczowi nurkować; M mówi, że nie powtórzy dawnego błędu. Zagadka techniczna jest umowna.

**Podpowiedzi:**

1. Potrzebna jest pomoc ludzi i sprzęt.

2. Florek może zorganizować ekipę.

3. Pokaż dossier, przygotuj węże i uruchom pracę zespołu.

## Q38 — Imię na kamieniu

Postać: M; etap: F; wymagania: Q37; lokacje: L40.

Przedmioty: I19, I37.

1. Pokaż dossier proboszczowi przy grobowcu.

2. Wybierz zapis „Greta von Platter”.

3. Połóż koronkę przy trumnie, nie jako magiczną ofiarę, lecz świadectwo tożsamości.

4. Wybierz „Pozostań do końca pogrzebu”. Cichnie motyw nawiedzenia.

**Wynik:** q38_done; haunting_resolved=true.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Przywróć zmarłej tożsamość.

2. Dossier wyjaśnia kim była.

3. Przekaż dokumenty i koronkę, zostań na pogrzebie.

## Q39 — Prawdziwy ojciec

Postać: K; etap: F; wymagania: Q35; lokacje: L04, L41.

Przedmioty: I06.

1. Zapytaj Izydora o Mariana.

2. Na Pradze porozmawiaj z Karolem: jeśli zrujnowany, siedzi pod murem; inaczej wychodzi z lokalu w stanie upokorzenia.

3. Marian podchodzi. Pokaż fotografię Luizy i zapytaj o wiadomość zasłyszaną na weselu.

4. Marian przyznaje, że jest ojcem Konstancji. K może go przyjąć albo powiedzieć „Potrzebuję czasu”; oba warianty pozwalają kontynuować.

5. Wobec Karola wybierz pomoc albo odejście; zapisuje tylko ton epilogu, nie moralny wynik punktowy.

**Wynik:** q39_done; father_known=true; marian_accepted=true/false; helped_karol=true/false.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Izydor zna dawne kontakty.

2. Połącz fotografię z rozmową na przyjęciu.

3. Znajdź Mariana i zapytaj wprost o Luizę.

## Q40 — Co zostaje po nas

Postać: MK; etap: F; wymagania: Q35, Q39; lokacje: L17, L33, L34, L42, L43.

Przedmioty: I39, I40.

1. Jako M na plebanii wybierz przyszłość: „Spróbuję odbudować więź z Konstancją” lub „Nasze drogi się rozeszły”.

2. Przy pierwszym wyborze przełącz na K i odpowiedz na list M: „Porozmawiajmy” albo „Chcę osobnej drogi”. Związek wymaga obu zgód, jest możliwy tylko gdy Krystyna żyje i book_marriage=false; w innych stanach M oferuje pojednanie bez związku.

3. Jako K wróć na wybrzeże. Sąsiad informuje o śmierci rybaka i przekazuje I39 zapis jego ostatniej woli. Pies pozostaje pod opieką sąsiada i przechodzi do K.

4. Odwiedź Klarę w Warszawie. Otrzymujesz I40 poszlaki dotyczące losu matki: wątek otwarty, bez dopisanego rozwiązania.

5. Wybierz „Zakończ opowieść”. Jeśli Q38 nieukończone, wyraźnie potwierdź pozostawienie sprawy stawu; możesz zamiast tego wrócić do M.

**Wynik:** q40_done; wybór E01/E02/E03/E04 zgodnie z tabelą zakończeń.

**Błędne działania:** Nieprawidłowa czynność nie zmienia stanu. Przedmioty kluczowe nie są zużywane.

**Podpowiedzi:**

1. Losy bohaterów nie muszą skończyć się wspólnym życiem.

2. Domknij sprawy rodzinne i zdecyduj o stawie.

3. Odwiedź Mariana, wybrzeże i Klarę; uzgodnij przyszłość obu postaci.

## Uściślenia identyfikatorów

Q04 używa I41 (wkład zaworu). Q27 kończy się dopiero po odłożeniu I31 i I32 na brzegu. Q29 wykonują obie postacie i tworzy I43. Q30 ma alternatywny I42. Q34 może tworzyć I44, Q40 tworzy I45. Wszystkie są w items.json. Reguły 03_STAN_I_MAPA.md są nadrzędne w kwestii dostępności lokacji i przejścia etapów.


---

# PROCH — stan, czas, przejścia i zakończenia

## Model danych i kolejność instrukcji

To dokument normatywny. Każde Q ma stały substep od 0 do liczby opisanych kroków, albo jawnie rozpisane alternatywy. Krok w quests.json może obejmować kilka akcji UI; implementator rozbija je na osobne deterministyczne reguły, nie zmieniając kolejności i skutków. Podniesienie widocznego dostępnego przedmiotu przed rozpoczęciem zadania jest legalne i nie blokuje jego ukończenia. Test kroku sprawdza stan, nie tylko ostatnie kliknięcie.

State: schema_version, content_version, phase A..F, active M|K, hero[M/K]{location, inventory[], worn[], knowledge_bitset, journal[], last_safe_location}, world{item_locations, container_open, scene_variants, npc_presence}, quests{Q01..Q40: status, substep, hint_level}, flags poniżej, crisis_substep, pending_messages[], ending_decisions, safe_snapshot. Knowledge nie jest współdzielone; oznaczaj wpisy jako „wiem”, „usłyszałem”, „podejrzewam”. Nie wstawiaj do narracji M informacji poznanej wyłącznie przez K.

Wszystkie booleany domyślnie false. Flagi: address_left, krystyna_saw_kindness, train_repaired, intercepted_letter, tavern_trust, pond_seen, honest_krystyna, disguise, safe_courier, letter_sent, m_knows_alive, rescue_rig, direct_contact, conspiracy_evidence, karol_ruined, dossier_ready, m_free, greta_history, remains_recovered, haunting_resolved, father_known, marian_accepted, helped_karol. Trójstanowe: krystyna_alive=unknown/true/false, book_marriage=unknown/true/false. Enum escape_variant=unknown/early/confrontation, crisis_mode=unknown/calm/despair. Każde Q po ukończeniu ustawia qNN_done. Flagi zapisane w success są dodatkowymi skutkami, nie komunikatami dla gracza.

Przy Q04 wkład to I41. Q27 przenosi zarówno I31, jak i I32 z ekwipunku M do L23 po zamocowaniu zestawu. I42 pojawia się zawsze w Q30, gdy nie ma zestawu. Q29 tworzy I43 i wymaga przełączenia z K na M; dzienniki obu pokazują tylko swoje części zadania. Q34 w wariancie żywej Krystyny tworzy I44. Q40 tworzy I45, fizycznie dostarczany przy przełączeniu na K na początku jej epilogu.

## Wspólny czas fabularny

Nie ma globalnego zegara real-time ani liczników ruchów. Oglądanie, dialogi, podpowiedzi i zmiana bohatera nie postarzają świata. Pory dnia to warianty lokacji wywołane krokami Q. Filmowe pominięcia dni/tygodni są jawnie opisane planszą; nie jest to kalendarz symulowany.

- A start: M L01, K L03, przełączanie dostępne po zamknięciu początkowej planszy; startowe ekwipunki puste, przedmioty dostaje się w Q01/Q06.
- A→B: Q05 AND Q08. Gotowy M czeka przy karczmie, gotowa K kończy pakowanie w Seroczynie. Komunikat „Ta część podróży jest przygotowana. Możesz wrócić do drugiej postaci.” Nie ujawnia jej wydarzeń.
- B start: M L09; K L30. B→C: Q13 AND Q15. Q10/Q11/Q12 wynikają z zależności Q13.
- C start: M L11, K L33. C→D: Q19 AND Q24. Obie postacie mają przycisk „Dalej” dopiero po ukończeniu swej ścieżki. Globalne przejście wymaga potwierdzenia: „Zamknąć ten etap? Opcjonalnych spraw na wybrzeżu nie będzie można już teraz dokończyć.” W dzienniku widoczne niezakończone znane cele. Q20 pozostaje dostępne w D do kryzysu.
- D start: M L13, K L08. Jeśli letter_sent, I28 zostaje przekazany Florkowi. Samo wejście D nie daje wiedzy M; musi wykonać Q26.
- D→kryzys: ukończone Q25 i sekwencja decyzji Q28. Gracz zatwierdza przejście. Jeśli Q25 brak, M pozostaje w ogrodzie, można wrócić do innych działań i K. Żaden list nie jest już potem doręczany wstecz.
- Q30: krótka sekwencja bez swobodnego przełączania. Najpierw M, potem wymuszone K; tytuł i portret zmieniają się jawnie. Przygotowana lina zmienia dostępne narzędzie, ale jej brak nie wymusza tragedii. Decyzje nie są ograniczone czasem.
- E start: krystyna_alive=false → M L38; true → M L17. K L03. M może rozmawiać, czytać i oglądać pamiątki; nie ma niewidzialnego ruchu poza celę. Przełączanie dostępne, żeby obejrzeć jego reakcję, lecz główny postęp należy do K. E→F po Q33.
- F: Q34/Q35 przywraca M pełną swobodę. Q36–38 można wykonywać równolegle z Q39 i częściami Q40. Zakończenie wyłącznie przez jawne „Zakończ opowieść” po Q35, Q39 i obowiązkowych etapach epilogu Q40. Brak Q38 wymaga potwierdzenia pozostawienia sprawy Grety; nadal można wrócić do śledztwa.

## Domknięcie Q40 — szczegółowe warunki

Zmienne m_future=unset/reconnect/separate, k_future=unset/reconnect/separate, coast_legacy=false, klara_seen=false. M na plebanii ustawia m_future. I45 dociera do K przez Izydora bez zagadki kurierskiej; K musi przeczytać i odpowiedzieć, ustawiając k_future. Jeśli M wybiera separate, K może również potwierdzić separate bez otrzymywania propozycji związku. Po Q39 K jedzie nad morze: coast_legacy=true po przyjęciu I39 i rozmowie o psie. Po powrocie do Klary: klara_seen=true. Q40 wymaga wszystkich czterech wartości ustalonych. Można najpierw odwiedzić Klarę, potem morze; związek ustala się dopiero po obu odpowiedziach.

pair_reunited := krystyna_alive AND NOT book_marriage AND m_future=reconnect AND k_future=reconnect. Jeśli para nie może się połączyć z powodu ślubu lub tragedii, opcja UI brzmi „Pojednajmy się, choć osobno”, a nie obiecuje romansu. Epilog M z Marianną jest skokiem o kilka lat, nie automatycznym romansem po jednym dialogu. W gałęzi krystyna_alive nie umiera Ludwik i nie zostawia spadku; M podejmuje pracę, a gospodarstwo pojawia się dopiero jako zakup po kilku latach. W gałęzi tragicznej dziedziczy zgodnie ze streszczeniem.

## Rozstrzyganie zakończenia, w tej kolejności

1. NOT haunting_resolved → E04 Niespokojna woda, niezależnie od innych flag. Stan Krystyny i relacji jest zachowany w akapitach epilogu.
2. haunting_resolved AND NOT krystyna_alive → E01 Proch. book_marriage decyduje, czy K odchodzi od męża, czy od niedoszłej rodziny. W pełnej ścieżce książkowej book_marriage=true i karol_ruined=true.
3. haunting_resolved AND krystyna_alive AND pair_reunited → E02 Przerwane kłamstwo.
4. haunting_resolved AND krystyna_alive AND NOT pair_reunited → E03 Osobne brzegi.

karol_ruined, marian_accepted i helped_karol zmieniają wskazane akapity, nie numer zakończenia. Nie istnieje ukryty wynik punktowy.

## Mapa i ograniczenia podróży

scenes.json links określa sąsiedztwo produkcyjne, nie bezwarunkową teleportację. W obrębie dostępnego regionu połączenia są dwukierunkowe, chyba że to podróż scenariuszowa. Silnik normalizuje lokalne krawędzie i usuwa duplikaty. Wymaganie postaci i etapu zawsze sprawdzane przed wyświetleniem przejścia. F rozszerza dostęp M do L11,L13,L15,L19,L20,L22,L23 na potrzeby Q36–38, nawet jeśli lista phase w scenes.json nie zawiera F. Dostęp do pokoju M przez K w D tylko jako złożenie wiadomości w Q29, bez przeszukiwania jego rzeczy. L23 dostępne K wyłącznie Q30 i później F. L20 dostępne M po Q16, dostępne K po Q35 w towarzystwie Krystyny, bez nowych questów. L21 dostępne M po Q19, K po Q25; K nie uruchamia podsłuchu M.

Podróże specjalne (przycisk mapy z nazwą celu, nie chodzenie przez wszystkie ekrany): Q06 L03→L25; Q08 przy przejściu B L25→L30; Q15 L32→L33; Q24 L35→L05→L04→L08; D L11→L22; E L03→L36; E/F L04↔L38; F L08↔L17↔L39, L04↔L41↔L42, L05↔L35↔L34. F M może wybrać L43 dopiero po epilogu, wcześniej nie jest jego gospodarstwem. Podróże z M do K nie przekazują ekwipunku, jeśli nie opisano konkretnego transferu. Nie wymaga się płacenia za każdą kolejną podróż.

Pociąg L06/L07 nie jest dostępny po Q05. Seroczyn L25–L29 nie jest dostępny po etapie A. Dom w Sopocie L30 nie jest dostępny po ucieczce. Przed zamknięciem tych miejsc wszystkie wymagane rzeczy są w posiadaniu postaci lub zapewnione fabularnie. Dodatkowe przejście L31→L30 jest zamknięte po Q14. Nie wpuszczaj K do stróżówki w B/C ani M do domu Borakowskich.

## Ogólne reguły interakcji

Ważne przedmioty nie mogą być niszczone, sprzedawane ani pozostawiane w zamykanym rozdziale. Odkładanie dopuszczone na stół w bieżącym bezpiecznym pokoju; obiekt zapisany z lokacją. Przed zamknięciem regionu wymagany przedmiot wraca do walizki z komunikatem „Pakuję swoje rzeczy”. Nie wymuszaj teleportacji nieprzenośnego zestawu pompy.

Wiedza zostaje po obejrzeniu dokumentu, lecz okazanie oryginału wymaga przedmiotu albo jawnie dozwolonego odpisu. Zapis można wykonać w dowolnym bezpiecznym stanie; podczas przejścia animacji zapis następuje po zakończeniu, podczas kryzysu zapisuje również substep. Przy śmierci przywracaj pełny snapshot sprzed decyzji, włącznie ze stanem drugiej postaci.

Zły wybór rozmowy daje możliwość sprostowania. Nie zamyka permanentnie ścieżki. Świadomy wybór odejścia po pomoc w Q30 ma osobne potwierdzenie, ponieważ to rozgałęzienie fabularne. Przed takim wyborem powstaje osobny zapis „Przed stawem”.

## Opisy a dane produkcyjne

Pole description lokacji jest instrukcją dla grafika, nie tekstem narratora. Przy wejściu wyświetl nazwę lokacji i pierwszą odpowiednią kwestię zadania z 06; przy powrocie samą nazwę. Pole examine hotspotu jest etykietą awaryjną. Szczegółowe badanie kluczowych obiektów zawsze stosuje tekst i wskazówkę podaną w odpowiednim kroku Q. Nie czytaj graczowi poleceń „po lewej”, „wariant” ani opisów masek.


---

# PROCH — katalog przedmiotów

## I01 — Umowa Koreckiego

Właściciel: M. Źródło: Q01, L01

Wygląd: Złożony arkusz, podpis i pieczęć.

Funkcja i stan: Dowód zatrudnienia, adres Wąglan; nie dowodzi niewinności.

## I02 — Bilet do Opoczna

Właściciel: M. Źródło: Q01, L01

Wygląd: Wąski kartonik z wyciętym narożnikiem.

Funkcja i stan: Q03; po kontroli zachowany jako skasowany.

## I03 — Broszka motyl

Właściciel: M. Źródło: Q01, L02

Wygląd: Symetryczny motyl, jasne skrzydła i czarny owal pośrodku.

Funkcja i stan: Q20 i uwierzytelnienie listu; nigdy nie ginie losowo.

## I04 — Klucz warsztatowy

Właściciel: M. Źródło: Q04, L07

Wygląd: Duży klucz o otwartej szczęce.

Funkcja i stan: Narzędzie lokalne, wraca do skrzynki przed odjazdem.

## I05 — Szmata

Właściciel: M. Źródło: Q04, L07

Wygląd: Złożona tkanina z ciemnym rogiem.

Funkcja i stan: Czyszczenie wkładu, zwrot przy odjeździe.

## I06 — Fotografia Luizy

Właściciel: K. Źródło: Q06, L03

Wygląd: Owalny portret kobiety na prostokątnym kartoniku.

Funkcja i stan: Pamiątka i rozmowa z Marianem; nie magiczny dowód pokrewieństwa.

## I07 — Dokument podróżny

Właściciel: K. Źródło: Q06, L03

Wygląd: Składany papier z widoczną pieczęcią.

Funkcja i stan: Przejazdy; zawsze odzyskiwany przy ucieczce.

## I08 — Walizka

Właściciel: K. Źródło: Q06, L03

Wygląd: Prostokątny neseser z uchwytem.

Funkcja i stan: Pojemnik; po ucieczce wersja zabrudzona, bez zmiany pojemności.

## I09 — Dzban wody

Właściciel: K. Źródło: Q07, L27

Wygląd: Jasny dzban z czarnym uchwytem.

Funkcja i stan: Zanoszony ogrodnikowi, wraca pusty do kuchni.

## I10 — Papier

Właściciel: K. Źródło: Q08, L25; zapas L33

Wygląd: Dwa czyste arkusze.

Funkcja i stan: Pisanie listów; zapas nieograniczony, bez gry ekonomicznej.

## I11 — Ołówek

Właściciel: K. Źródło: Q08, L25

Wygląd: Gruby ukośny ołówek.

Funkcja i stan: Nie zużywa się.

## I12 — Mosiężny kluczyk

Właściciel: M. Źródło: Q09, L13

Wygląd: Mały klucz z okrągłym uchem.

Funkcja i stan: Tylko szuflada stróżówki.

## I13 — Pęk kluczy

Właściciel: M. Źródło: Q09, L13

Wygląd: Trzy różne klucze na kółku.

Funkcja i stan: Brama, hala, warsztat; dobór właściwego automatyczny.

## I14 — Biblia

Właściciel: M. Źródło: Q09, L13

Wygląd: Księga z krzyżem na okładce.

Funkcja i stan: Przedmiot osobisty, dialog o wierze; nie broń przeciw Grecie.

## I15 — Relacja robotnika

Właściciel: M. Źródło: Q11, L16

Wygląd: Kartka z trzema krótkimi liniami.

Funkcja i stan: Wpis w dzienniku; kopia dostępna K przez M w Q34.

## I16 — Nitka

Właściciel: M. Źródło: Q12, L15

Wygląd: Szpulka z odwiniętym końcem.

Funkcja i stan: Znacznik okna; po użyciu pozostaje w scenie.

## I17 — Wosk

Właściciel: M. Źródło: Q12, L15

Wygląd: Krótka świeca i bryłka.

Funkcja i stan: Mocowanie znacznika; zapas warsztatowy odnawialny.

## I18 — Pasek papieru

Właściciel: M. Źródło: Q12, L15

Wygląd: Długi cienki pasek z zagięciem.

Funkcja i stan: Znacznik drzwi, lokalny po użyciu.

## I19 — Koronka Grety

Właściciel: M. Źródło: Q12, L13

Wygląd: Nieregularny biały fragment z trzema czarnymi oczkami.

Funkcja i stan: Portret, dossier, pogrzeb; kolejne skrawki scalają się w ten sam stos.

## I20 — Zaproszenie Krystyny

Właściciel: M. Źródło: Q16, L18

Wygląd: Mała karta z inicjałem K.

Funkcja i stan: Dostęp do biblioteki.

## I21 — Odpis katalogu

Właściciel: M. Źródło: Q17, L20

Wygląd: Karta z dużym III i 27.

Funkcja i stan: Dokładna sygnatura, wiedza nie znika po odłożeniu.

## I22 — Mapa dóbr

Właściciel: M. Źródło: Q18, L20

Wygląd: Rzeka jako krzywa, staw jako owal, krzyżyk przy trakcie.

Funkcja i stan: Odblokowanie lasu i dossier Grety.

## I23 — Notatka o stawie

Właściciel: M. Źródło: Q19, L23

Wygląd: Szkic uskoku i splątanych korzeni.

Funkcja i stan: Ostrzeżenie i przygotowanie ratunku.

## I24 — Tkanina

Właściciel: K. Źródło: Q21, L33

Wygląd: Zwinięty materiał o grubym rastrze.

Funkcja i stan: Zużywana tylko po poprawnym uszyciu sukni.

## I25 — Igła z nicią

Właściciel: K. Źródło: Q21, L33

Wygląd: Powiększona igła i pętla nici.

Funkcja i stan: Suknia i sieć; nie zużywa się.

## I26 — Prosta suknia

Właściciel: K. Źródło: Q21, L33

Wygląd: Prosty strój bez krynoliny i koronek.

Funkcja i stan: Po założeniu jako wyposażenie K; ikonę można obejrzeć.

## I27 — Adres pośrednika

Właściciel: K. Źródło: Q22, L34

Wygląd: Mały kartonik z symbolem koperty.

Funkcja i stan: Bezpieczny kanał przez sąsiada do Izydora.

## I28 — List „Żyję”

Właściciel: K>M. Źródło: Q23, L34; Q26, L11

Wygląd: Zamknięta potem otwarta koperta.

Funkcja i stan: Jedyny fizyczny egzemplarz przechodzi courier>Florek>M; K zachowuje tylko odpis.

## I29 — Pieniądze na bilet

Właściciel: K. Źródło: Q24, L33

Wygląd: Sakiewka i dwie monety.

Funkcja i stan: Wystarczają na podróże fabularne; nie symulować cen ani biedy blokującej grę.

## I30 — Zdjęcie z jarmarku

Właściciel: K. Źródło: Q25, L10

Wygląd: Dwie stojące osoby i tło straganu.

Funkcja i stan: Obejrzenie nie dowodzi romansu; możliwy zwrot po Q35.

## I31 — Lina

Właściciel: M>świat. Źródło: Q27, L15

Wygląd: Zwinięty zwój z czytelnym końcem.

Funkcja i stan: Po zamocowaniu pozostaje na brzegu; dostępna K w Q30.

## I32 — Hak

Właściciel: M>świat. Źródło: Q27, L15

Wygląd: Długi trzonek i łagodny hak.

Funkcja i stan: Kładziony przy linie po zakończeniu Q27; nie służy do przemocy.

## I33 — Zaproszenie na przyjęcie

Właściciel: K. Źródło: Q31, L03

Wygląd: Elegancka karta z ramką.

Funkcja i stan: Wariant napisów: wesele/przyjęcie; ten sam identyfikator.

## I34 — Kopia zlecenia finansowego

Właściciel: K. Źródło: Q32, L37

Wygląd: Tabela i duży podpis na dole.

Funkcja i stan: Decyzja o ostrzeżeniu Karola; fikcyjna spółka opisana bez nazwy historycznej.

## I35 — List Borakowskich

Właściciel: K. Źródło: Q32, L37

Wygląd: Arkusz z podpisem i zagiętym rogiem.

Funkcja i stan: Dowód uzgodnionego kłamstwa; tekst podany w katalogu dokumentów.

## I36 — Oświadczenie proboszcza

Właściciel: K. Źródło: Q34, L17

Wygląd: Arkusz z małą pieczęcią.

Funkcja i stan: Opisuje spotkania i stan M; nie zaświadcza z góry o jego niewinności.

## I37 — Dossier Grety

Właściciel: M. Źródło: Q36, L20

Wygląd: Teczka z wystającą mapą.

Funkcja i stan: Połączenie informacji, nie zużywa źródeł.

## I38 — Zestaw pompy

Właściciel: świat. Źródło: Q37, L15

Wygląd: Dwa węże, uszczelka i pompa ręczna.

Funkcja i stan: Nie mieści się w kieszeni: transport wykonuje ekipa Florka.

## I39 — Ostatnia wola rybaka

Właściciel: K. Źródło: Q40, L34

Wygląd: Prosty podpisany arkusz.

Funkcja i stan: Narracyjne przekazanie chaty i łodzi, bez zagadki prawnej.

## I40 — Papiery Luizy

Właściciel: K. Źródło: Q40, L42

Wygląd: Dwie kartki o sprzecznych datach i fotografia.

Funkcja i stan: Tylko poszlaka mistyfikacji śmierci; otwarte zakończenie.

## I41 — Wkład zaworu

Właściciel: świat. Źródło: Q04, L07

Wygląd: Krótki walec z osadem.

Funkcja i stan: Stany zamontowany/brudny wyjęty/czysty wyjęty/zamontowany czysty.

## I42 — Długi konar

Właściciel: świat. Źródło: Q30, L23

Wygląd: Gruby rozwidlony konar na suchym brzegu.

Funkcja i stan: Alternatywny ratunek bez wcześniejszej liny; pozostaje na brzegu.

## I43 — Wiadomość w pokoju

Właściciel: K>M. Źródło: Q29, L13

Wygląd: Kartka z prostym podpisem K.

Funkcja i stan: „Żyję. Czekam w karczmie. Konstancja.” M musi ją przeczytać.

## I44 — Zeznanie Krystyny

Właściciel: K. Źródło: Q34, L17

Wygląd: Podpisany arkusz z inicjałami.

Funkcja i stan: Dostępne tylko gdy żyje; przyznaje udział w spisku i opisuje wypadek.

## I45 — List o przyszłości

Właściciel: M>K. Źródło: Q40, L17

Wygląd: Otwarta koperta z piórem obok.

Funkcja i stan: Wybór przyszłości, odpowiedź K wymaga przełączenia postaci.


---

# PROCH — pełny katalog lokacji i grafik

## Wspólna reguła obrazu

Scena ma 360×208 pikseli, ekran 512×342. PNG to format źródłowy; runtime dostaje własne bitmapy 1-bit. Kolory wyłącznie 0 i 255. Kreska 1 px; drobiny nie zastępują czytelnych przedmiotów. Raster regularny, bez antyaliasingu. Interfejs i tekst zawsze rysuje silnik, nie generator obrazów. Przygotuj grafiki w docelowej rozdzielczości i sprawdź w skali 1:1. Generowanie dużego konceptu wymaga ręcznej lub narzędziowej redukcji i korekty, nie gwarantuje poprawnego finalnego pixelartu.

Prostokąty hotspots w scenes.json to zamknięty projekt startowy interakcji. Ilustracja ma komponować cele w tych obszarach. Są szerokie, by uniknąć polowania na piksel. Wolno skorygować współrzędne do gotowego obrazu, zachowując znaczenie obiektu, bez zmiany questów. Przy nakładaniu celów użyj jawnego z-order i masek. Wyjścia są osobnymi przyciskami panelu Przejścia; nie trzeba zgadywać pikseli drzwi.

Każdy obiekt przenośny rysowany na scenie to osobna bitmapa + maska, po zabraniu znika. Jeśli generator umieścił go w tle, usuń go z tła przed wydaniem. Dla każdej postaci portret 48×48 jest obowiązkowy; sylwetka w lokacji może być stała. Dla M/K dodaj wariant spokojny, zmęczony i alarmowy poprzez brwi/usta; nie zmieniaj tożsamości. Dla K strój elegancki i prosty; dla Grety normalna i zjawa. Dla Krystyny mokra sylwetka po ratunku, bez erotyzacji. Obiekty wskazane w Q, a nieobecne na liście głównych hotspots (np. kartka w kufrze), są w oknie pojemnika otwieranym przez obiekt nadrzędny.

## Manifest

assets.json zawiera każdy bazowy obraz lokacji, wariant fabularny, ikonę, portret i zbliżenie wraz z nazwą pliku i dokładnym opisem. Nazwy nie zależą od polskich znaków. Wariant nie może zmieniać położenia nieruchomych obiektów. Bitmapa bazowa jest stanem domyślnym, warianty nakładaj według nadrzędności: kryzys > skutek > pora > bazowy.

### L01 — Gabinet Koreckiego

Ciężkie biurko po lewej, okno z tramwajem konnym w głębi, fotel gospodarza po prawej. Deszcz na szybie. Papier umowy leży na jasnym fragmencie blatu.

Postać: M; etapy: A. Połączenia topologiczne: L02.

Cele: L01_H1 Korecki [12, 65, 106, 188]; L01_H2 umowa [128, 35, 235, 178]; L01_H3 okno [252, 45, 348, 192]

### L02 — Przedpokój Koreckich

Wysokie lustro, wieszak, drzwi do gabinetu i kufer podróżny. Marian przy bocznych drzwiach.

Postać: MK; etapy: A,E,F. Połączenia topologiczne: L01, L03, L04.

Cele: L02_H1 Marian [12, 65, 106, 188]; L02_H2 kufer [128, 35, 235, 178]; L02_H3 drzwi [252, 45, 348, 192]

### L03 — Pokój Konstancji w Warszawie

Toaletka przy oknie, mała szkatułka na stole, podróżna walizka i fotografia matki. Bez luksusowego nadmiaru drobiazgów.

Postać: K; etapy: A,E,F. Połączenia topologiczne: L02.

Cele: L03_H1 szkatułka [12, 65, 106, 188]; L03_H2 fotografia Luizy [128, 35, 235, 178]; L03_H3 walizka [252, 45, 348, 192]

### L04 — Redakcja Izydora

Biurko publicysty, szuflada korespondencji, szpalty gazety. Izydor w kamizelce, puste miejsce na przekazywane dokumenty.

Postać: MK; etapy: A,C,E,F. Połączenia topologiczne: L02, L05, L38.

Cele: L04_H1 Izydor [12, 65, 106, 188]; L04_H2 poczta [128, 35, 235, 178]; L04_H3 próbna gazeta [252, 45, 348, 192]

### L05 — Dworzec warszawski

Kasa po lewej, tablica odjazdów centralnie, wejście na peron po prawej. Para za oknem, kufry, stalowe wiązary.

Postać: MK; etapy: A,C,E,F. Połączenia topologiczne: L04, L06.

Cele: L05_H1 kasjer [12, 65, 106, 188]; L05_H2 rozkład [128, 35, 235, 178]; L05_H3 bramka [252, 45, 348, 192]

### L06 — Przedział pociągu

Drewniane ławki, ciężarna podróżna przy oknie, drzwi na pomost. Krystyna widoczna w osobnym kadrze rozmowy.

Postać: M; etapy: A. Połączenia topologiczne: L05, L07, L08.

Cele: L06_H1 podróżna [12, 65, 106, 188]; L06_H2 konduktor [128, 35, 235, 178]; L06_H3 drzwi na pomost [252, 45, 348, 192]

### L07 — Postój przy parowozie

Bok maszyny, uproszczona sprężarka i trzy czytelne elementy: dopływ, zawór, przewód. Maszynista stoi z dala od mechanizmu.

Postać: M; etapy: A. Połączenia topologiczne: L06.

Cele: L07_H1 maszynista [12, 65, 106, 188]; L07_H2 sprężarka [128, 35, 235, 178]; L07_H3 skrzynka narzędzi [252, 45, 348, 192]

### L08 — Stacja Opoczno

Niski budynek stacyjny, drogowskaz Wąglany, wóz przy studni. Otwarte niebo, szeroka biała przestrzeń.

Postać: MK; etapy: A,C,E,F. Połączenia topologiczne: L06, L09.

Cele: L08_H1 woźnica [12, 65, 106, 188]; L08_H2 drogowskaz [128, 35, 235, 178]; L08_H3 ławka [252, 45, 348, 192]

### L09 — Droga i most w Wąglanach

Mostek nad wodą, młyn w tle, po prawej brama fabryki. Las odcina horyzont zwartą czernią.

Postać: MK; etapy: B,C,D,F. Połączenia topologiczne: L08, L10, L11, L16, L18.

Cele: L09_H1 drogowskaz [12, 65, 106, 188]; L09_H2 młyn [128, 35, 235, 178]; L09_H3 most [252, 45, 348, 192]

### L10 — Karczma

Tolek przy stole, Celina za ladą; wolne miejsce dla fotografa w etapie D. Belki, jasne naczynia na ciemnym tle.

Postać: MK; etapy: B,C,D. Połączenia topologiczne: L09.

Cele: L10_H1 Tolek [12, 65, 106, 188]; L10_H2 Celina [128, 35, 235, 178]; L10_H3 fotograf [252, 45, 348, 192]

### L11 — Dziedziniec gorzelni

Biały dawny dworek, brama, komin i niewykończony budynek. Florek obok stojaka na rowery.

Postać: MK; etapy: B,C,D,F. Połączenia topologiczne: L09, L12, L14, L15.

Cele: L11_H1 Florek [12, 65, 106, 188]; L11_H2 brama [128, 35, 235, 178]; L11_H3 rower [252, 45, 348, 192]

### L12 — Korytarz stróżówki

Drzwi do pokoju, ciemny koniec korytarza, okno nad ławką. W nawiedzeniu światło pod drzwiami znika.

Postać: M; etapy: B,C,D. Połączenia topologiczne: L11, L13.

Cele: L12_H1 drzwi pokoju [12, 65, 106, 188]; L12_H2 okno [128, 35, 235, 178]; L12_H3 cień [252, 45, 348, 192]

### L13 — Pokój Mikołaja

Biurko po lewej, zamknięte okno centralnie, łóżko i budzik po prawej, piec w rogu. Biała koronka kontrastuje z ciemną podłogą.

Postać: M; etapy: B,C,D. Połączenia topologiczne: L12.

Cele: L13_H1 biurko [10, 28, 170, 104]; L13_H2 okno [190, 28, 350, 104]; L13_H3 łóżko [10, 119, 170, 199]; L13_H4 koronka [190, 119, 350, 199]

### L14 — Hala browaru

Kadzie i rury, mokre kamienne posadzki, małe górne okna. Żadnych elektrycznych mierników.

Postać: M; etapy: B,C. Połączenia topologiczne: L11, L15.

Cele: L14_H1 kadź [12, 65, 106, 188]; L14_H2 rura [128, 35, 235, 178]; L14_H3 ślady na podłodze [252, 45, 348, 192]

### L15 — Warsztat i skład

Stół z imadłem, kołki na ścianie, bęben liny, hak, lampa. Każde narzędzie ma osobny obrys.

Postać: MK; etapy: B,C,D,F. Połączenia topologiczne: L11, L14.

Cele: L15_H1 stół [10, 28, 170, 104]; L15_H2 lina [190, 28, 350, 104]; L15_H3 hak [10, 119, 170, 199]; L15_H4 lampa [190, 119, 350, 199]

### L16 — Dom poszkodowanego robotnika

Furtka, mała Marysia, matka w progu; w środku łóżko chorego za kotarą. Obecność Grety jedynie przez spojrzenie dziecka.

Postać: M; etapy: B. Połączenia topologiczne: L09.

Cele: L16_H1 Marysia [12, 65, 106, 188]; L16_H2 matka [128, 35, 235, 178]; L16_H3 robotnik [252, 45, 348, 192]

### L17 — Plebania

Stół, księgi i okno, proboszcz w głębi. Marianna przy drzwiach do kuchni. Spokojne jasne wnętrze.

Postać: MK; etapy: B,C,D,F. Połączenia topologiczne: L18.

Cele: L17_H1 proboszcz [12, 65, 106, 188]; L17_H2 Marianna [128, 35, 235, 178]; L17_H3 księga [252, 45, 348, 192]

### L18 — Plac przy kościele

Kościół i ławka; rozgałęzienie do pałacu i cmentarza. Krystyna czeka przy bramce tylko przed umówionym spotkaniem.

Postać: MK; etapy: B,C,D,F. Połączenia topologiczne: L09, L17, L19, L40.

Cele: L18_H1 Krystyna [12, 65, 106, 188]; L18_H2 ławka [128, 35, 235, 178]; L18_H3 drogowskaz [252, 45, 348, 192]

### L19 — Hall pałacu w Białaczowie

Schody, duże drzwi biblioteki, służący. Jasne ściany i czarne drewniane płyciny.

Postać: MK; etapy: C,D,F. Połączenia topologiczne: L18, L20, L21.

Cele: L19_H1 służący [12, 65, 106, 188]; L19_H2 drzwi biblioteki [128, 35, 235, 178]; L19_H3 schody [252, 45, 348, 192]

### L20 — Biblioteka

Pięciokątny pokój, obraz wysoko nad drzwiami, ruchoma drabina, katalog pod oknem i oznaczony regał kronik.

Postać: M; etapy: C,D. Połączenia topologiczne: L19.

Cele: L20_H1 portret [10, 28, 170, 104]; L20_H2 drabina [190, 28, 350, 104]; L20_H3 katalog [10, 119, 170, 199]; L20_H4 kronika [190, 119, 350, 199]

### L21 — Ogród pałacowy

Żywopłot przesłania rozmówców, ścieżka biegnie ku otwartemu placowi. Trzy sylwetki w kadrze podsłuchu.

Postać: MK; etapy: C,D. Połączenia topologiczne: L19.

Cele: L21_H1 żywopłot [10, 28, 170, 104]; L21_H2 Ludwik [190, 28, 350, 104]; L21_H3 Korecki [10, 119, 170, 199]; L21_H4 Krystyna [190, 119, 350, 199]

### L22 — Leśna ścieżka

Jeżyny na pierwszym planie, blady fragment tkaniny na kolcu, wydeptana ścieżka znikająca w ciemności.

Postać: MK; etapy: C,D,F. Połączenia topologiczne: L11, L23.

Cele: L22_H1 jeżyny [12, 65, 106, 188]; L22_H2 koronka [128, 35, 235, 178]; L22_H3 ścieżka [252, 45, 348, 192]

### L23 — Brzeg stawu

Nieruchoma woda, korzenie, zwalony pień po lewej i stabilny głaz po prawej. Biała koronka na wodzie; odległy brzeg tonie w czerni.

Postać: MK; etapy: C,D,F. Połączenia topologiczne: L22, L24.

Cele: L23_H1 pień [10, 28, 170, 104]; L23_H2 woda [190, 28, 350, 104]; L23_H3 głaz [10, 119, 170, 199]; L23_H4 korzenie [190, 119, 350, 199]

### L24 — Widzenie dawnego obozu

Małe ognisko, dwie szable, skórzana torba, stare naczynia. Zarys postaci za drzewami, bez obrazu przemocy seksualnej.

Postać: M; etapy: C. Połączenia topologiczne: L23.

Cele: L24_H1 ognisko [12, 65, 106, 188]; L24_H2 torba [128, 35, 235, 178]; L24_H3 światło między drzewami [252, 45, 348, 192]

### L25 — Pokój w Seroczynie

Łóżko, kufer, dzwonek, okno na park. Walizka stoi gotowa, drzwi prowadzą do pilnowanego korytarza.

Postać: K; etapy: A. Połączenia topologiczne: L26.

Cele: L25_H1 kufer [12, 65, 106, 188]; L25_H2 dzwonek [128, 35, 235, 178]; L25_H3 okno [252, 45, 348, 192]

### L26 — Korytarz Borakowskich

Trzy drzwi, stolik na korespondencję, schody do salonu. Irena blokuje główne wyjście.

Postać: K; etapy: A. Połączenia topologiczne: L25, L27, L28.

Cele: L26_H1 Irena [12, 65, 106, 188]; L26_H2 stolik [128, 35, 235, 178]; L26_H3 drzwi kuchni [252, 45, 348, 192]

### L27 — Kuchnia w Seroczynie

Stół, dzban, okno gospodarcze i dwa zamki w drzwiach. Luiza, służąca, jest odrębną osobą od matki Konstancji.

Postać: K; etapy: A. Połączenia topologiczne: L26.

Cele: L27_H1 Luiza służąca [12, 65, 106, 188]; L27_H2 dzban [128, 35, 235, 178]; L27_H3 drzwi gospodarcze [252, 45, 348, 192]

### L28 — Park Borakowskich

Gęste drzewa, ławka, ogrodzenie i furtka ku wsi. Dominuje ciemny żywopłot, nie labirynt.

Postać: K; etapy: A. Połączenia topologiczne: L26, L29.

Cele: L28_H1 furtka [12, 65, 106, 188]; L28_H2 ogrodnik [128, 35, 235, 178]; L28_H3 ławka [252, 45, 348, 192]

### L29 — Droga pod Seroczynem

Błotnista droga i wóz wieśniaka; dwór nadal widoczny. Brak bezpiecznej drogi dalszej ucieczki na tym etapie.

Postać: K; etapy: A. Połączenia topologiczne: L28.

Cele: L29_H1 wieśniak [12, 65, 106, 188]; L29_H2 wóz [128, 35, 235, 178]; L29_H3 droga [252, 45, 348, 192]

### L30 — Pokój w Sopocie

Walizka, okno na ogród, drzwi pilnowane przez Irenę. Trzy stany: przed przemocą, po interwencji Adama, otwarte okno.

Postać: K; etapy: B. Połączenia topologiczne: L31.

Cele: L30_H1 Irena [10, 28, 170, 104]; L30_H2 Adam [190, 28, 350, 104]; L30_H3 walizka [10, 119, 170, 199]; L30_H4 okno [190, 119, 350, 199]

### L31 — Ogród i Bergen Strasse

Niska skarpa, krzewy, piaszczysta uliczka i tabliczka. Widoczne przejście ku wydmom.

Postać: K; etapy: B. Połączenia topologiczne: L30, L32.

Cele: L31_H1 skarpa [12, 65, 106, 188]; L31_H2 tabliczka [128, 35, 235, 178]; L31_H3 ścieżka ku morzu [252, 45, 348, 192]

### L32 — Plaża z sieciami

Paliki, sieci, ciemne morze po prawej, molo daleko z lewej. Pies o białej sierści i czarnych łatkach w wariancie porannym.

Postać: K; etapy: B,C,F. Połączenia topologiczne: L31, L33, L34.

Cele: L32_H1 sieci [12, 65, 106, 188]; L32_H2 pies [128, 35, 235, 178]; L32_H3 linia brzegu [252, 45, 348, 192]

### L33 — Chata rybaka

Piec, ława, stół do szycia, skrzynia, małe okno. Rybak i pies; bezpieczna przestrzeń z dużą ilością bieli.

Postać: K; etapy: B,C,F. Połączenia topologiczne: L32.

Cele: L33_H1 rybak [12, 65, 106, 188]; L33_H2 stół do szycia [128, 35, 235, 178]; L33_H3 skrzynia [252, 45, 348, 192]

### L34 — Przystań rybacka

Łódź na piasku, podarte sieci, rybak sąsiad przy paliku. Horyzont morski.

Postać: K; etapy: C,F. Połączenia topologiczne: L32, L35.

Cele: L34_H1 sąsiad [12, 65, 106, 188]; L34_H2 sieć [128, 35, 235, 178]; L34_H3 łódź [252, 45, 348, 192]

### L35 — Stacja w Sopocie

Kasa, rozkład, tor z odjeżdżającym składem. Podróż do Warszawy jest przejściem fabularnym.

Postać: K; etapy: C. Połączenia topologiczne: L34, L05.

Cele: L35_H1 kasjer [12, 65, 106, 188]; L35_H2 rozkład [128, 35, 235, 178]; L35_H3 peron [252, 45, 348, 192]

### L36 — Sala weselna

Muzycy w tle, stoły, drzwi bocznego gabinetu, zegar. W wariancie uratowanej Krystyny jest to przyjęcie zaręczynowe.

Postać: K; etapy: E. Połączenia topologiczne: L02, L37.

Cele: L36_H1 Adam [12, 65, 106, 188]; L36_H2 zegar [128, 35, 235, 178]; L36_H3 drzwi gabinetu [252, 45, 348, 192]

### L37 — Gabinet przy sali

Biurko z teczką, drzwi z przeszkleniem i kredens. Rozmowa Borakowskich dociera przez uchylone drzwi.

Postać: K; etapy: E. Połączenia topologiczne: L36.

Cele: L37_H1 drzwi [12, 65, 106, 188]; L37_H2 teczka [128, 35, 235, 178]; L37_H3 biurko [252, 45, 348, 192]

### L38 — Areszt i pokój rozmów

Stół przed kratą, strażnik w głębi, Mikołaj po drugiej stronie. Po ocaleniu Krystyny ten sam pokój służy do zeznań bez krat na pierwszym planie.

Postać: MK; etapy: E,F. Połączenia topologiczne: L04, L39.

Cele: L38_H1 Mikołaj [12, 65, 106, 188]; L38_H2 strażnik [128, 35, 235, 178]; L38_H3 stół na dokumenty [252, 45, 348, 192]

### L39 — Sala rozpraw

Ława świadka, stół sądu, miejsce na dokumenty; przeciwnicy jako sylwetki w tle.

Postać: K; etapy: F. Połączenia topologiczne: L38, L08.

Cele: L39_H1 sąd [12, 65, 106, 188]; L39_H2 świadkowie [128, 35, 235, 178]; L39_H3 dokumenty [252, 45, 348, 192]

### L40 — Rodzinny grobowiec

Kamienny grobowiec, otwarte miejsce na inskrypcję Grety. W żałobnym wariancie drugi wieniec dla Krystyny.

Postać: MK; etapy: F. Połączenia topologiczne: L18.

Cele: L40_H1 płyta [12, 65, 106, 188]; L40_H2 proboszcz [128, 35, 235, 178]; L40_H3 wieniec [252, 45, 348, 192]

### L41 — Praska ulica

Mokra kostka, kałuża, przygasła witryna, Karol siedzący pod murem. Marian wyłania się z przejścia.

Postać: K; etapy: F. Połączenia topologiczne: L04, L42.

Cele: L41_H1 Karol [12, 65, 106, 188]; L41_H2 Marian [128, 35, 235, 178]; L41_H3 przejście [252, 45, 348, 192]

### L42 — Pokój Klary

Klara przy stole, dokumenty Luizy i stara fotografia. Świt za oknem.

Postać: K; etapy: F. Połączenia topologiczne: L41.

Cele: L42_H1 Klara [12, 65, 106, 188]; L42_H2 dokumenty [128, 35, 235, 178]; L42_H3 fotografia [252, 45, 348, 192]

### L43 — Gospodarstwo Mikołaja

Niewielki dom, płot i jasne pole. Marianna w progu wyłącznie w odpowiednim epilogu.

Postać: M; etapy: F. Połączenia topologiczne: L17.

Cele: L43_H1 dom [12, 65, 106, 188]; L43_H2 Marianna [128, 35, 235, 178]; L43_H3 droga [252, 45, 348, 192]

## Opisy wszystkich zasobów

### BG_L01 — bg/L01.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Ciężkie biurko po lewej, okno z tramwajem konnym w głębi, fotel gospodarza po prawej. Deszcz na szybie. Papier umowy leży na jasnym fragmencie blatu. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Korecki: [12, 65, 106, 188]; umowa: [128, 35, 235, 178]; okno: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L02 — bg/L02.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Wysokie lustro, wieszak, drzwi do gabinetu i kufer podróżny. Marian przy bocznych drzwiach. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Marian: [12, 65, 106, 188]; kufer: [128, 35, 235, 178]; drzwi: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L03 — bg/L03.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Toaletka przy oknie, mała szkatułka na stole, podróżna walizka i fotografia matki. Bez luksusowego nadmiaru drobiazgów. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: szkatułka: [12, 65, 106, 188]; fotografia Luizy: [128, 35, 235, 178]; walizka: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L04 — bg/L04.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Biurko publicysty, szuflada korespondencji, szpalty gazety. Izydor w kamizelce, puste miejsce na przekazywane dokumenty. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Izydor: [12, 65, 106, 188]; poczta: [128, 35, 235, 178]; próbna gazeta: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L05 — bg/L05.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Kasa po lewej, tablica odjazdów centralnie, wejście na peron po prawej. Para za oknem, kufry, stalowe wiązary. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: kasjer: [12, 65, 106, 188]; rozkład: [128, 35, 235, 178]; bramka: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L06 — bg/L06.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Drewniane ławki, ciężarna podróżna przy oknie, drzwi na pomost. Krystyna widoczna w osobnym kadrze rozmowy. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: podróżna: [12, 65, 106, 188]; konduktor: [128, 35, 235, 178]; drzwi na pomost: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L07 — bg/L07.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Bok maszyny, uproszczona sprężarka i trzy czytelne elementy: dopływ, zawór, przewód. Maszynista stoi z dala od mechanizmu. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: maszynista: [12, 65, 106, 188]; sprężarka: [128, 35, 235, 178]; skrzynka narzędzi: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L08 — bg/L08.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Niski budynek stacyjny, drogowskaz Wąglany, wóz przy studni. Otwarte niebo, szeroka biała przestrzeń. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: woźnica: [12, 65, 106, 188]; drogowskaz: [128, 35, 235, 178]; ławka: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L09 — bg/L09.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Mostek nad wodą, młyn w tle, po prawej brama fabryki. Las odcina horyzont zwartą czernią. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: drogowskaz: [12, 65, 106, 188]; młyn: [128, 35, 235, 178]; most: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L10 — bg/L10.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Tolek przy stole, Celina za ladą; wolne miejsce dla fotografa w etapie D. Belki, jasne naczynia na ciemnym tle. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Tolek: [12, 65, 106, 188]; Celina: [128, 35, 235, 178]; fotograf: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L10_photographer.png: fotograf przy stole i odbitka w jego dłoni

### BG_L11 — bg/L11.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Biały dawny dworek, brama, komin i niewykończony budynek. Florek obok stojaka na rowery. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Florek: [12, 65, 106, 188]; brama: [128, 35, 235, 178]; rower: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L11_day.png: praca robotników
- bg/L11_night.png: puste podwórko
- bg/L11_pumping.png: ekipa strażaków z pompą

### BG_L12 — bg/L12.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Drzwi do pokoju, ciemny koniec korytarza, okno nad ławką. W nawiedzeniu światło pod drzwiami znika. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: drzwi pokoju: [12, 65, 106, 188]; okno: [128, 35, 235, 178]; cień: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L12_normal.png: światło pod drzwiami
- bg/L12_haunted.png: czarna szczelina, blada stopa na skraju kadru

### BG_L13 — bg/L13.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Biurko po lewej, zamknięte okno centralnie, łóżko i budzik po prawej, piec w rogu. Biała koronka kontrastuje z ciemną podłogą. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: biurko: [10, 28, 170, 104]; okno: [190, 28, 350, 104]; łóżko: [10, 119, 170, 199]; koronka: [190, 119, 350, 199]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L13_day.png: bez koronki
- bg/L13_night.png: puste wnętrze, zamknięte okno
- bg/L13_sealed.png: pasek na drzwiach i nitka na oknie
- bg/L13_morning_lace.png: nienaruszone znaczniki i koronka na podłodze
- bg/L13_note.png: wiadomość K na biurku

### BG_L14 — bg/L14.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Kadzie i rury, mokre kamienne posadzki, małe górne okna. Żadnych elektrycznych mierników. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: kadź: [12, 65, 106, 188]; rura: [128, 35, 235, 178]; ślady na podłodze: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L15 — bg/L15.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Stół z imadłem, kołki na ścianie, bęben liny, hak, lampa. Każde narzędzie ma osobny obrys. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: stół: [10, 28, 170, 104]; lina: [190, 28, 350, 104]; hak: [10, 119, 170, 199]; lampa: [190, 119, 350, 199]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L16 — bg/L16.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Furtka, mała Marysia, matka w progu; w środku łóżko chorego za kotarą. Obecność Grety jedynie przez spojrzenie dziecka. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Marysia: [12, 65, 106, 188]; matka: [128, 35, 235, 178]; robotnik: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L17 — bg/L17.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Stół, księgi i okno, proboszcz w głębi. Marianna przy drzwiach do kuchni. Spokojne jasne wnętrze. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: proboszcz: [12, 65, 106, 188]; Marianna: [128, 35, 235, 178]; księga: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L18 — bg/L18.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Kościół i ławka; rozgałęzienie do pałacu i cmentarza. Krystyna czeka przy bramce tylko przed umówionym spotkaniem. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Krystyna: [12, 65, 106, 188]; ławka: [128, 35, 235, 178]; drogowskaz: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L19 — bg/L19.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Schody, duże drzwi biblioteki, służący. Jasne ściany i czarne drewniane płyciny. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: służący: [12, 65, 106, 188]; drzwi biblioteki: [128, 35, 235, 178]; schody: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L20 — bg/L20.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Pięciokątny pokój, obraz wysoko nad drzwiami, ruchoma drabina, katalog pod oknem i oznaczony regał kronik. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: portret: [10, 28, 170, 104]; drabina: [190, 28, 350, 104]; katalog: [10, 119, 170, 199]; kronika: [190, 119, 350, 199]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L20_normal.png: czysta suknia na portrecie
- bg/L20_haunted.png: podarta suknia, zaburzona twarz
- bg/L20_ladder.png: drabina pod portretem

### BG_L21 — bg/L21.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Żywopłot przesłania rozmówców, ścieżka biegnie ku otwartemu placowi. Trzy sylwetki w kadrze podsłuchu. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: żywopłot: [10, 28, 170, 104]; Ludwik: [190, 28, 350, 104]; Korecki: [10, 119, 170, 199]; Krystyna: [190, 119, 350, 199]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L21_meeting.png: trzy osoby za żywopłotem
- bg/L21_empty.png: pusty ogród

### BG_L22 — bg/L22.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Jeżyny na pierwszym planie, blady fragment tkaniny na kolcu, wydeptana ścieżka znikająca w ciemności. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: jeżyny: [12, 65, 106, 188]; koronka: [128, 35, 235, 178]; ścieżka: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L23 — bg/L23.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Nieruchoma woda, korzenie, zwalony pień po lewej i stabilny głaz po prawej. Biała koronka na wodzie; odległy brzeg tonie w czerni. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: pień: [10, 28, 170, 104]; woda: [190, 28, 350, 104]; głaz: [10, 119, 170, 199]; korzenie: [190, 119, 350, 199]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L23_calm.png: nieruchoma woda
- bg/L23_vision.png: palce przy koronce
- bg/L23_rigged.png: lina przy głazie i hak obok
- bg/L23_crisis.png: Krystyna w wodzie, twarz ponad powierzchnią
- bg/L23_saved.png: dwie postacie na brzegu
- bg/L23_aftermath.png: pusty brzeg i ludzie w tle
- bg/L23_drained.png: odsłonięte korzenie i sylwetka pod płótnem

### BG_L24 — bg/L24.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Małe ognisko, dwie szable, skórzana torba, stare naczynia. Zarys postaci za drzewami, bez obrazu przemocy seksualnej. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: ognisko: [12, 65, 106, 188]; torba: [128, 35, 235, 178]; światło między drzewami: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L25 — bg/L25.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Łóżko, kufer, dzwonek, okno na park. Walizka stoi gotowa, drzwi prowadzą do pilnowanego korytarza. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: kufer: [12, 65, 106, 188]; dzwonek: [128, 35, 235, 178]; okno: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L26 — bg/L26.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Trzy drzwi, stolik na korespondencję, schody do salonu. Irena blokuje główne wyjście. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Irena: [12, 65, 106, 188]; stolik: [128, 35, 235, 178]; drzwi kuchni: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L27 — bg/L27.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Stół, dzban, okno gospodarcze i dwa zamki w drzwiach. Luiza, służąca, jest odrębną osobą od matki Konstancji. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Luiza służąca: [12, 65, 106, 188]; dzban: [128, 35, 235, 178]; drzwi gospodarcze: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L28 — bg/L28.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Gęste drzewa, ławka, ogrodzenie i furtka ku wsi. Dominuje ciemny żywopłot, nie labirynt. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: furtka: [12, 65, 106, 188]; ogrodnik: [128, 35, 235, 178]; ławka: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L29 — bg/L29.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Błotnista droga i wóz wieśniaka; dwór nadal widoczny. Brak bezpiecznej drogi dalszej ucieczki na tym etapie. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: wieśniak: [12, 65, 106, 188]; wóz: [128, 35, 235, 178]; droga: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L30 — bg/L30.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Walizka, okno na ogród, drzwi pilnowane przez Irenę. Trzy stany: przed przemocą, po interwencji Adama, otwarte okno. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Irena: [10, 28, 170, 104]; Adam: [190, 28, 350, 104]; walizka: [10, 119, 170, 199]; okno: [190, 119, 350, 199]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L30_guarded.png: Irena przy łóżku
- bg/L30_escape.png: otwarte okno i Adam za nim
- bg/L30_aftermath.png: przewrócone krzesło, ciemna plama, bez zbliżenia zwłok

### BG_L31 — bg/L31.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Niska skarpa, krzewy, piaszczysta uliczka i tabliczka. Widoczne przejście ku wydmom. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: skarpa: [12, 65, 106, 188]; tabliczka: [128, 35, 235, 178]; ścieżka ku morzu: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L32 — bg/L32.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Paliki, sieci, ciemne morze po prawej, molo daleko z lewej. Pies o białej sierści i czarnych łatkach w wariancie porannym. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: sieci: [12, 65, 106, 188]; pies: [128, 35, 235, 178]; linia brzegu: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L32_storm.png: wiatr i sieci
- bg/L32_dawn.png: pies przy sieciach
- bg/L32_peace.png: spokojne morze

### BG_L33 — bg/L33.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Piec, ława, stół do szycia, skrzynia, małe okno. Rybak i pies; bezpieczna przestrzeń z dużą ilością bieli. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: rybak: [12, 65, 106, 188]; stół do szycia: [128, 35, 235, 178]; skrzynia: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L33_alive.png: rybak przy stole
- bg/L33_empty.png: puste krzesło, pies przy progu

### BG_L34 — bg/L34.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Łódź na piasku, podarte sieci, rybak sąsiad przy paliku. Horyzont morski. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: sąsiad: [12, 65, 106, 188]; sieć: [128, 35, 235, 178]; łódź: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L35 — bg/L35.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Kasa, rozkład, tor z odjeżdżającym składem. Podróż do Warszawy jest przejściem fabularnym. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: kasjer: [12, 65, 106, 188]; rozkład: [128, 35, 235, 178]; peron: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L36 — bg/L36.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Muzycy w tle, stoły, drzwi bocznego gabinetu, zegar. W wariancie uratowanej Krystyny jest to przyjęcie zaręczynowe. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Adam: [12, 65, 106, 188]; zegar: [128, 35, 235, 178]; drzwi gabinetu: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L36_wedding.png: welon K, weselny stół
- bg/L36_reception.png: K w zwykłej sukni, brak symboli ślubu

### BG_L37 — bg/L37.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Biurko z teczką, drzwi z przeszkleniem i kredens. Rozmowa Borakowskich dociera przez uchylone drzwi. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: drzwi: [12, 65, 106, 188]; teczka: [128, 35, 235, 178]; biurko: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L38 — bg/L38.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Stół przed kratą, strażnik w głębi, Mikołaj po drugiej stronie. Po ocaleniu Krystyny ten sam pokój służy do zeznań bez krat na pierwszym planie. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Mikołaj: [12, 65, 106, 188]; strażnik: [128, 35, 235, 178]; stół na dokumenty: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L38_arrest.png: krata między bohaterami
- bg/L38_statement.png: rozmowa przy stole, bez kraty

### BG_L39 — bg/L39.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Ława świadka, stół sądu, miejsce na dokumenty; przeciwnicy jako sylwetki w tle. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: sąd: [12, 65, 106, 188]; świadkowie: [128, 35, 235, 178]; dokumenty: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L40 — bg/L40.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Kamienny grobowiec, otwarte miejsce na inskrypcję Grety. W żałobnym wariancie drugi wieniec dla Krystyny. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: płyta: [12, 65, 106, 188]; proboszcz: [128, 35, 235, 178]; wieniec: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L40_two.png: wieńce Grety i Krystyny
- bg/L40_one.png: wieniec Grety, Krystyna wśród żałobników

### BG_L41 — bg/L41.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Mokra kostka, kałuża, przygasła witryna, Karol siedzący pod murem. Marian wyłania się z przejścia. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Karol: [12, 65, 106, 188]; Marian: [128, 35, 235, 178]; przejście: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L41_ruined.png: Karol pod ścianą
- bg/L41_warned.png: Karol stojący przy wejściu

### BG_L42 — bg/L42.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Klara przy stole, dokumenty Luizy i stara fotografia. Świt za oknem. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: Klara: [12, 65, 106, 188]; dokumenty: [128, 35, 235, 178]; fotografia: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.



### BG_L43 — bg/L43.png

360×208. Oryginalna ilustracja przygodówki PROCH, Polska 1898, widok z pierwszej osoby. Niewielki dom, płot i jasne pole. Marianna w progu wyłącznie w odpowiednim epilogu. Czysty 1-bit, tylko #000000/#ffffff, regularny raster 25/50/75%, duże czytelne kontury; żadnych szarych pikseli, wygładzania ani interfejsu w ilustracji. Rozdzielczość dostawy dokładnie 360×208. Zaprojektuj najważniejsze cele w obszarach: dom: [12, 65, 106, 188]; Marianna: [128, 35, 235, 178]; droga: [252, 45, 348, 192]. Prostokąty to obszary interakcji, nie ramki rysowane na obrazie. Przy obiektach nakładających się stosuj maski. Pierwszeństwo czytelnego kliknięcia przed dekoracją.

- bg/L43_alone.png: M w progu
- bg/L43_marianna.png: Marianna w progu
- bg/L43_together.png: M i K obok siebie

### ICON_I01 — items/I01.png

24×24. Złożony arkusz, podpis i pieczęć. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I02 — items/I02.png

24×24. Wąski kartonik z wyciętym narożnikiem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I03 — items/I03.png

24×24. Symetryczny motyl, jasne skrzydła i czarny owal pośrodku. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I04 — items/I04.png

24×24. Duży klucz o otwartej szczęce. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I05 — items/I05.png

24×24. Złożona tkanina z ciemnym rogiem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I06 — items/I06.png

24×24. Owalny portret kobiety na prostokątnym kartoniku. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I07 — items/I07.png

24×24. Składany papier z widoczną pieczęcią. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I08 — items/I08.png

24×24. Prostokątny neseser z uchwytem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I09 — items/I09.png

24×24. Jasny dzban z czarnym uchwytem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I10 — items/I10.png

24×24. Dwa czyste arkusze. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I11 — items/I11.png

24×24. Gruby ukośny ołówek. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I12 — items/I12.png

24×24. Mały klucz z okrągłym uchem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I13 — items/I13.png

24×24. Trzy różne klucze na kółku. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I14 — items/I14.png

24×24. Księga z krzyżem na okładce. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I15 — items/I15.png

24×24. Kartka z trzema krótkimi liniami. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I16 — items/I16.png

24×24. Szpulka z odwiniętym końcem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I17 — items/I17.png

24×24. Krótka świeca i bryłka. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I18 — items/I18.png

24×24. Długi cienki pasek z zagięciem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I19 — items/I19.png

24×24. Nieregularny biały fragment z trzema czarnymi oczkami. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I20 — items/I20.png

24×24. Mała karta z inicjałem K. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I21 — items/I21.png

24×24. Karta z dużym III i 27. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I22 — items/I22.png

24×24. Rzeka jako krzywa, staw jako owal, krzyżyk przy trakcie. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I23 — items/I23.png

24×24. Szkic uskoku i splątanych korzeni. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I24 — items/I24.png

24×24. Zwinięty materiał o grubym rastrze. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I25 — items/I25.png

24×24. Powiększona igła i pętla nici. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I26 — items/I26.png

24×24. Prosty strój bez krynoliny i koronek. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I27 — items/I27.png

24×24. Mały kartonik z symbolem koperty. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I28 — items/I28.png

24×24. Zamknięta potem otwarta koperta. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I29 — items/I29.png

24×24. Sakiewka i dwie monety. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I30 — items/I30.png

24×24. Dwie stojące osoby i tło straganu. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I31 — items/I31.png

24×24. Zwinięty zwój z czytelnym końcem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I32 — items/I32.png

24×24. Długi trzonek i łagodny hak. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I33 — items/I33.png

24×24. Elegancka karta z ramką. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I34 — items/I34.png

24×24. Tabela i duży podpis na dole. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I35 — items/I35.png

24×24. Arkusz z podpisem i zagiętym rogiem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I36 — items/I36.png

24×24. Arkusz z małą pieczęcią. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I37 — items/I37.png

24×24. Teczka z wystającą mapą. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I38 — items/I38.png

24×24. Dwa węże, uszczelka i pompa ręczna. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I39 — items/I39.png

24×24. Prosty podpisany arkusz. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I40 — items/I40.png

24×24. Dwie kartki o sprzecznych datach i fotografia. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I41 — items/I41.png

24×24. Krótki walec z osadem. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I42 — items/I42.png

24×24. Gruby rozwidlony konar na suchym brzegu. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I43 — items/I43.png

24×24. Kartka z prostym podpisem K. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I44 — items/I44.png

24×24. Podpisany arkusz z inicjałami. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### ICON_I45 — items/I45.png

24×24. Otwarta koperta z piórem obok. Czysta ikona 1-bit na białym tle, czarny kontur grubości 1 px, rozmiar 24×24. Bez tekstu. Maska osobnym obrazem, identyczny rozmiar.



### POR_M — portraits/M.png

48×48. Mikołaj Goworek: młody dorosły mężczyzna, szczupła twarz, falowane ciemne włosy, skromna marynarka i koszula; bez narzucania podobieństwa do osoby rzeczywistej. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_K — portraits/K.png

48×48. Konstancja Korecka: młoda dorosła kobieta, ciemne włosy upięte, wyraźne oczy i zdecydowane spojrzenie; strój początkowo elegancki, potem prosty. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_KR — portraits/KR.png

48×48. Krystyna: młoda dorosła hrabianka, upięte włosy, strój do jazdy konnej, pewne spojrzenie; w późniejszych scenach skrucha. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_GR — portraits/GR.png

48×48. Greta von Platter: dorosła kobieta w historycznej koronkowej sukni, długie ciemne włosy; wersja portretowa pogodna, zjawa wyniszczona, nie erotyzowana. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_KA — portraits/KA.png

48×48. Karol Korecki: dojrzały zamożny mężczyzna, szeroka sylwetka, wąs, kamizelka, twardy wyraz twarzy. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_IZ — portraits/IZ.png

48×48. Izydor Jelinek: dojrzały publicysta, schludny zarost, kamizelka, czujne zmęczone oczy. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_MA — portraits/MA.png

48×48. Marian: starszy służący, skromny ubiór, łagodne oczy i wyprostowana sylwetka. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_FL — portraits/FL.png

48×48. Florek: starszy brygadzista, maciejówka, wąs, robocza kurtka, pogodna lecz zmęczona twarz. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_AD — portraits/AD.png

48×48. Adam Borakowski: młody dorosły, staranny ubiór, gładka twarz, zmienny uśmiech. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_EL — portraits/EL.png

48×48. Eleonora Borakowska: dojrzała kobieta o spiętej twarzy, surowa fryzura, ciężka suknia. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_IR — portraits/IR.png

48×48. Irena: dorosła służąca, gładko spięte włosy, fartuch i nieruchome spojrzenie. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_RY — portraits/RY.png

48×48. Rybak: sędziwy mężczyzna, broda, grube brwi, wełniany sweter, czapka. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_PR — portraits/PR.png

48×48. Proboszcz: dojrzały ksiądz, sutanna, spokojna twarz. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_MI — portraits/MI.png

48×48. Marianna: dorosła kobieta w prostym stroju kuchennym, spokojny wyraz twarzy, bez idealizacji. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_KL — portraits/KL.png

48×48. Klara: dojrzała kobieta, miękkie rysy, prosta elegancka suknia. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_LU — portraits/LU.png

48×48. Ludwik: dojrzały hrabia, bokobrody, surdut i staranny kołnierz. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_TO — portraits/TO.png

48×48. Tolek: dorosły karczmarz, wąs, podwinięte rękawy. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_CE — portraits/CE.png

48×48. Celina: dorosła gospodyni w fartuchu, czujne spojrzenie. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_MY — portraits/MY.png

48×48. Marysia: mała dziewczynka z jasnymi warkoczykami, zwykły dziecięcy strój, ciekawość. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_LS — portraits/LS.png

48×48. Luiza służąca: dorosła kobieta w roboczym fartuchu; nie przypomina portretu matki Konstancji. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_BO — portraits/BO.png

48×48. Borakowski senior: dojrzały mężczyzna w surducie, ciężkie brwi; zawsze ubrany w ilustracjach gry. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_RO — portraits/RO.png

48×48. Ranny robotnik: dorosły mężczyzna odpoczywający na łóżku, blada twarz. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_MT — portraits/MT.png

48×48. Matka Marysi: dorosła kobieta z chustką i śladem mąki na fartuchu. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_SN — portraits/SN.png

48×48. Sąsiad rybaka: dojrzały mężczyzna, czapka, roboczy sweter. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_FO — portraits/FO.png

48×48. Fotograf: dorosły mężczyzna, futerał z odbitkami pod pachą. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_ME — portraits/ME.png

48×48. Maszynista: dorosły mężczyzna w roboczej czapce i kurtce. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_WO — portraits/WO.png

48×48. Woźnica: dorosły mężczyzna w płaszczu z wysokim kołnierzem. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_OG — portraits/OG.png

48×48. Ogrodnik: dorosły mężczyzna w kapeluszu i fartuchu. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_SD — portraits/SD.png

48×48. Sędzia: starszy urzędnik za stołem, powściągliwa twarz. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_ST — portraits/ST.png

48×48. Strażnik: dorosły mężczyzna w umownym mundurze epoki; bez wymyślonych szczegółowych insygniów. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_SL — portraits/SL.png

48×48. Służący pałacowy: dorosły mężczyzna w schludnym ciemnym ubraniu. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_KS — portraits/KS.png

48×48. Kasjer: dorosły urzędnik za okienkiem. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_KN — portraits/KN.png

48×48. Konduktor: dorosły kolejarz w czapce. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### POR_PD — portraits/PD.png

48×48. Podróżna: dorosła ciężarna kobieta w skromnym płaszczu. Portret głowa i ramiona, 48×48, 1-bit, czytelna sylwetka, bez mikroszczegółów. Projekt plastyczny adaptacji, nie deklaracja dokładnego opisu powieści.



### Z01 — closeups/Z01.png

360×208. Portret Grety. Pełny portret z czytelnym pasem koronki na dole; alternatywa z podartą suknią i zranioną twarzą. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z02 — closeups/Z02.png

360×208. Zawór. Korpus, pokrywa, wkład: trzy oddzielne duże części, wyraźny osad; wariant czysty. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z03 — closeups/Z03.png

360×208. Katalog. Szufladka P, karta Platter, trzy pola: tom III, karta 27, Mapa dóbr. Litery renderuje silnik. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z04 — closeups/Z04.png

360×208. Mapa. Trakt, rzeka, młyn, staw; cztery duże symbole, legenda renderowana tekstem. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z05 — closeups/Z05.png

360×208. Sieć. Trzy luźne końce, trzy sąsiednie poprawne oczka jako przykład; warianty po pierwszym i drugim połączeniu. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z06 — closeups/Z06.png

360×208. Pompa. Dwa węże z oznaczeniami A i B, odpowiadające gniazda, duża uszczelka; tekst nakładany przez silnik. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z07 — closeups/Z07.png

360×208. Fotografia jarmarku. Mikołaj i Krystyna obok straganu, zwykła rozmowa, brak fizycznego znaku zaręczyn. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z08 — closeups/Z08.png

360×208. Dokument. Wspólna ramka papieru, niewielka pieczęć; pełną treść wyświetla silnik, nie generować drobnych pseudo-liter. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z09 — closeups/Z09.png

360×208. Fotografia matki. Owalny portret Luizy, matki Konstancji, dorosła kobieta w eleganckiej sukni. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.



### Z10 — closeups/Z10.png

360×208. Tytuł. Słowo PROCH renderowane silnikiem; sylwetka dworu i stawu, motyw białej koronki w rogu. Wyłącznie czerń/biel; raster; 360×208; osobna warstwa masek dla ruchomych elementów.


---

# PROCH — teksty, dokumenty i zakończenia

Teksty poniżej są nowymi tekstami adaptacji, z wyjątkiem krótkiej sentencji przywołanej w książce. Nie są cytatami z rękopisu. Kwestie w krokach questów to dokładne opcje dialogowe. Stosować odpowiedzi poniżej; dodatkowe kliknięcie danego tematu powtarza skróconą odpowiedź, nigdy nie przyznaje ponownie nagrody. Rozmowa ma 2–4 widoczne tematy i zawsze „Zakończ rozmowę”. Nowy temat pojawia się dopiero po poznaniu wskazówki przez aktywnego bohatera.

## Otwarcie

„Warszawa, 1898. Karol Korecki zna cenę niemal wszystkiego. Uczucie swojej córki również chciałby wpisać do rachunku. Mikołaj ma otrzymać szansę: mały zakład w Wąglanach, uciekający robotnicy i pogłoski, których nikt nie chce potwierdzić.”

Po przełączeniu po raz pierwszy na K: „Konstancja. Ten sam czas, inny pokój. Podróż już za nią postanowiono. Pozostaje zdecydować, co zabrać — i czego nie pozwolić sobie odebrać.”

## Dialogi główne, według zadań

Q01 Korecki: „Ludzie porzucają pracę. Mówią o strachach, zamiast pilnować swoich obowiązków. Pan ustali przyczynę. Wtedy wrócimy do rozmowy o mojej córce.” M: „Chcę, aby obietnica była równie wyraźna jak pańskie żądanie.” Korecki: „Ma pan dokument. I bilet.” Marian: „Proszę nie zapomnieć, dla kogo pan jedzie. A gdyby trzeba było przekazać wiadomość, niech pan pamięta o Izydorze.”

Q02 Izydor: „Adres jest czasem ważniejszy od obietnicy. Zapiszę go. Jeżeli Konstancja przyjdzie, nie odeślę jej z niczym.”

Q03 Podróżna: „Dziękuję. Już myślałam, że do końca drogi będę musiała udawać, że nie jestem zmęczona.” Konduktor po postoju: „Kłopot przy maszynie. Proszę zostać w przedziale, chyba że maszynista zgodzi się pana przyjąć.”

Q04 Maszynista przed oględzinami: „Pan twierdzi, że warto obejrzeć zawór? Dobrze. Ale przy działającej maszynie niczego pan nie rozkręci.” Po oczyszczeniu: „Ruszyła. Wygląda na to, że znaleźliśmy przyczynę. Wracajmy, ludzie czekają.”

Q05 Woźnica: „Wąglany? Pojadę tam. Niech pan tylko nie pyta, czemu inni nie chcą.”

Q06 K do fotografii: „Ciebie zabiorę. Choć tyle mogę jeszcze postanowić sama.”

Q07 Irena: „Spacerować wolno w parku. O wyjeździe decyduje pani.” Luiza służąca: „Wody nie odmówię. Ale proszę nie mówić, że to ode mnie.” Ogrodnik: „Furtka gospodarcza nie jest zamknięta. Ja nic nie widziałem.” Wieśniak: „Pani wróci do Warszawy, a my tu zostaniemy. Nie mogę.” K po powrocie: „Mur nie kończy się na ogrodzeniu.”

Q08 Irena: „Listy przegląda pani. Tak jest przyjęte w tym domu.” K: „Zatem nie list mam napisać lepiej. Muszę znaleźć inną drogę.” Eleonora: „Jedziemy do Sopotu. Powietrze dobrze ci zrobi.”

Q09 Florek: „W szufladzie są klucze. Pokój był Zenka. Rower też. Dbaj o rzeczy i o siebie.” O Biblii: „Nie wszystko, co człowiek trzyma blisko, służy do walki.”

Q10 Tolek: „Widziałem cię z nimi. Tu człowiek za cudzą rozmowę też potrafi zapłacić.” Po wyjaśnieniu: „Dobrze. Posłucham. Ale nie próbuj robić ze mnie głupca.” Celina: „Usiądźcie. Łatwiej rozmawiać, kiedy nikt nie stoi nad drugim.”

Q11 Marysia: „Ta pani stoi obok ciebie. Powiedziała, że jest Gleta.” Matka: „Proszę jej nie straszyć. A mąż mówił już wszystkim, co pamięta.” Robotnik: „Nie słyszałem kroków. Najpierw zimno. Potem tak, jakby nie było czym oddychać. Kobieta była blisko, choć nie wiem, skąd się wzięła.”

Q12 M rano: „Papier cały. Nitka na miejscu. A tego wczoraj tutaj nie było.” Po obejrzeniu koronki: „Drobny wzór. Nie wygląda na część roboczego ubrania.”

Q13 M: „Greto. Chcę poznać twoją historię.” Narrator: „Ciemność nie odpowiada słowami. Cofa się o krok. Pod drzwiami wraca pas światła.”

Q14 Adam: „Widziałem. Broniłaś się. Teraz trzeba stąd wyjść.” K: „Nie wiem już, komu wierzyć.” Adam: „Nie musisz mi wierzyć. Okno jest otwarte.” Przycisk skrócenia sceny: „Pomiń szczegółowy opis”. Skrót: „Irena atakuje Konstancję. W szarpaninie, przerwanej wejściem Adama, Irena doznaje śmiertelnego urazu. Adam otwiera okno. Konstancja musi opuścić dom.” W konfrontacji z Eleonorą narracja ograniczona do walki, walizki i wyrwania się; bez zbliżeń obrażeń.

Q15 Rybak: „Najpierw ogrzej ręce. Opowieść nie ucieknie.” K: „Ja uciekłam. To na razie wszystko, co umiem powiedzieć.” Rybak: „Na razie wystarczy.”

Q16 Marianna: „Siostra wspominała kogoś, kto pomógł jej w pociągu. Teraz pan usiądzie.” Proboszcz: „Nie zamieniaj strachu w pewność. Pytaj tych, którzy coś widzieli, i oddziel ich słowa od pogłosek.” Krystyna: „Taka koronka… W domu mamy stare portrety. Mogę pokazać panu bibliotekę.”

Q17 Ludwik: „Greta von Platter. Proszę nie zdejmować obrazu. Katalog jest pod oknem.” Po zmianie portretu M: „Przed chwilą suknia była cała.” Ludwik: „Widzę stary obraz. Nic więcej.”

Q18 M: „Portret miał być prezentem. Potem ruszyła za człowiekiem, którego kochała. Opowieść rodziny kończy się właśnie tam, gdzie powinna zacząć wyjaśniać.”

Q19 M przy obozie: „Te przedmioty nie należą do naszego czasu. Nie chcę ich zabierać. Chcę wrócić.” Po wyjściu: „Woda przy brzegu jest głęboka. Korzenie znikają pod powierzchnią. Następnym razem nie przyjdę bez przygotowania.”

Q20 Krystyna: „Powinien pan był powiedzieć wcześniej.” M: „Mówię teraz. Konstancja nie może stać się tematem, który omijamy.” Krystyna: „Rozumiem. Choć nie jest to dla mnie obojętne.”

Q21 Rybak: „W skrzyni jest materiał. Strój nie musi być piękny, żeby był twój.” K: „Chcę móc wyjść bez pytania, kto mnie zobaczy.”

Q22 Sąsiad: „Dobra robota. Jeżeli list ma ominąć cudze ręce, dam go człowiekowi, którego znam. Resztę musi pani napisać jasno.”

Q23 K przy składaniu listu: „Nie proszę, żeby uwierzył plotce. Proszę, żeby rozpoznał moje słowa.” Sąsiad: „Przyjąłem. Przekażę do redakcji.”

Q24 Rybak: „Nie zatrzymam cię wdzięcznością. Weź na drogę.” Izydor przy address_left: „Zostawił adres. Wąglany.” Bez address_left: „Nie podał mi go osobiście. Ale korespondencja Koreckiego musi być w księdze.”

Q25 Fotograf: „Zrobiłem zdjęcie. O zaręczynach niczego nie słyszałem od nich samych.” K: „A więc widział pan dwoje ludzi, nie ich zamiary.”

Q26 Florek: „Przyszło z Warszawy. Podobno ważne.” M po odczycie: „Motyl. Ona pamięta. Żyje.”

Q27 Proboszcz: „Niech ktoś wie, dokąd idziesz. Żadna odpowiedź nie wymaga, żebyś szukał jej pod wodą.” Florek: „Linę i hak weź. Przywiąż na suchym, stabilnym brzegu. Nie do spróchniałego pnia.”

Q28 urywek: Korecki: „…że się otruła. Tę wiadomość miał otrzymać.” M bez potwierdzenia: „Co pan powiedział o Konstancji?” Korecki: „To, co musiał pan w końcu usłyszeć.” Z listem: M: „Otrzymałem jej własne słowa. Proszę wyjaśnić swoje.” Przy honest_krystyna Krystyna: „Nie. Nie mogę dalej milczeć. Uciekła. Nie wiemy, gdzie jest. To miało pana od niej odsunąć.” Przycisk sprawdzenia: „Nie uwierzę bez sprawdzenia”.

Q29 K: „Pokazano mi fotografię. Powiedz mi sam, co znaczy.” M: „Spotkanie. I coś, o czym powinienem był mówić uczciwie. Ale nie oddałem nikomu prawa do decydowania za nas.” K: „Nie obiecuję, że to wszystko naprawi. Wiem przynajmniej, że rozmawiam z tobą.”

Q30 przed upadkiem Krystyna: „Mój ojciec i Korecki chcieli, żebym odwróciła pana od Konstancji. Pozwoliłam na to. Potem przestało być grą.” Po upadku: „Korzenie… nie mogę ruszyć nogą!” K: „Mikołaju, pomóż mi z brzegu!” M: „Trzymam. Podaj jej koniec.” Po ratunku Krystyna: „Nie wiem, czy zasługuję na waszą pomoc.” K: „Nie musisz na nią zasługiwać, żebyśmy cię wyciągnęli.” Ostrzeżenie przy odejściu: „Jeśli odejdziesz, nie będzie nikogo, kto utrzyma ją przy powierzchni. Biec po pomoc mimo to?” Po tragedii: „Woda zamyka się. Mikołaj jeszcze przez chwilę trzyma ręce tak, jakby wciąż mógł kogoś dosięgnąć.”

Q31 Klara: „Gdy wszyscy nalegają na szybkie szczęście, sprawdź, komu najbardziej się spieszy.” K przy przyjęciu bez ślubu: „Przyjdę. To nie jest zgoda na małżeństwo.”

Q32 Borakowski: „Karol podpisał. Uwierzył, że wie wcześniej niż inni.” Eleonora: „Jak zawsze uwierzył temu, co chciał usłyszeć.” Adam: „A Mikołaj? Nadal wierzy, że to wszystko zbieg okoliczności?” Dalszy urywek: „Jeszcze myśli, że wychował własną córkę…” K: „Nie wyjdę stąd tylko z ich słowami. Potrzebuję czegoś, czego jutro się nie wyprą.”

Q33 Karol po dowodach: „Skąd to masz?” K: „To teraz najmniej ważne. Jeszcze możesz zatrzymać swoją decyzję.” Po bankructwie narrator: „Tym razem rachunek nie pozostawia mu miejsca na targowanie.” Nie pokazywać minigry strzelania ani pościgu z pistoletem; wydarzenia streszczenia można podać w krótkim raporcie Izydora.

Q34 Izydor: „Ułóżmy to od początku. Kto coś widział, kto coś usłyszał, a kto tylko powtarza cudzą wersję?” Proboszcz: „Opiszę nasze rozmowy. Nie będę twierdził, że widziałem to, czego nie widziałem.” Krystyna, jeśli żyje: „Podpiszę. Także to, co mnie obciąża.”

Q35 Sąd: „Co dokładnie potwierdza przedstawiona fotografia?” K poprawnie: „Że byli razem na jarmarku. Niczego więcej sama fotografia nie rozstrzyga.” Błędnie „Dowodzi zdrady”: Sąd: „Czy widoczny jest na niej taki dowód? Proszę oddzielić wniosek od obserwacji.” Zakończenie: „Sąd nie podziela zarzutu, który postawiono Mikołajowi.” Bez udawania kompletnej sentencji prawnej.

Q36 M: „Nie szukała drogi do pałacu. Jej historia urwała się przy wodzie.” Proboszcz: „W takim razie zacznijmy od przywrócenia jej imienia i miejsca wśród zmarłych.”

Q37 Florek: „Zrobimy to razem. Nikt więcej nie pójdzie tam sam.” Strażak: „Połączenia gotowe. Odsunąć się od brzegu.” Przy odkryciu Grety narrator: „Pod osadem zachowała się suknia. Ten sam wzór, który Mikołaj trzymał tyle razy w dłoni.”

Q38 M: „Greta von Platter. Nie legenda. Nie strach, którym uciszano robotników. Człowiek.” Narrator: „Kiedy ostatnia garść ziemi opada, nie wydarza się nic nadzwyczajnego. Po raz pierwszy ta zwyczajność przynosi ulgę.”

Q39 Marian: „Byłem blisko i wciąż nie umiałem powiedzieć prawdy. Luiza była twoją matką. Ja jestem twoim ojcem.” K przy przyjęciu: „Nie odzyskamy tamtych lat. Możemy nie stracić następnych.” Przy dystansie: „Potrzebuję czasu. Nie chcę kolejnej prawdy, którą mam przyjąć na czyjeś żądanie.” Do Karola przy odejściu: „Wszystkich zrównuje proch. Rodzimy się nierówni, równi umieramy.” Przy pomocy: „Pomogę ci wstać. To nie znaczy, że wrócę pod twoją władzę.”

Q40 sąsiad: „Zostawił chatę dla ciebie. Mówił, że dom powinien czekać na kogoś, kto go potrzebuje.” Klara: „Są daty, które się nie zgadzają. I ludzie, których nikt o nic nie zapytał. Nie mogę obiecać, że twoja matka żyje. Nie mogę już też powiedzieć, że wszystko wiemy.”

## Pełne treści dokumentów używanych w zagadkach

I01: „Mikołaj Goworek podejmuje zadanie zbadania przyczyn zakłóceń pracy zakładu w Wąglanach. Po wyjaśnieniu sprawy Karol Korecki zobowiązuje się powrócić do ustalonej zgody na związek z Konstancją. Podpis: Karol Korecki.” Nie dodawać kodu ani ukrytych cyfr.

I21: „PLATTER — kronika rodu, tom III, karta 27. Aneks: mapa dóbr i dawnego traktu do Wąglan.”

I28: „Izydorze, żyję. Uciekłam i znalazłam bezpieczne schronienie. Proszę przekazać Mikołajowi, żeby nie wierzył wiadomościom o mojej śmierci. Niech zachowa motyla, którego dostał przed wyjazdem. Powiem mu sama, co się wydarzyło. Konstancja.”

I34: „Zlecenie nabycia udziałów za środki przekazane przez Karola Koreckiego. Podstawą decyzji jest informacja dostarczona przez rodzinę Borakowskich. Realizacja zgodnie z dyspozycją złożoną w dniu przyjęcia.” Dane finansowe nie są zagadką rachunkową.

I35: „Trzeba podtrzymać wiadomość o śmierci Konstancji i nie dopuścić do bezpośredniej rozmowy młodych. Fotografia pomoże przekonać dziewczynę, że Goworek znalazł lepszą partię. Sprawy udziałów dopilnujemy podczas przyjęcia. Niech Karol wierzy, że to dowód naszej wdzięczności. Podpis: Borakowski.” Dokument dopisany do adaptacji jako materialny ślad spisku, nie cytat z książki.

I36: „Mikołaj odwiedzał plebanię i opowiadał o niepokojących wydarzeniach przy zakładzie. Szukał pomocy i wyjaśnienia. Opisuję wyłącznie własne spotkania i rozmowy; nie byłem świadkiem wypadku nad stawem.”

I37: „Greta von Platter. Rozpoznanie portretu przez wzór koronki. Rodzinna kronika wskazuje wyjazd ku Wąglanom. Dalsza nota opisuje napaść i śmierć przy stawie. Mapa potwierdza położenie. Wniosek: należy szukać szczątków przy dawnym trakcie i przywrócić zmarłej tożsamość.”

I39: „Jeśli Konstancja wróci, niech wie, że chciałem zostawić jej chatę i łódź. Niech ma dokąd wracać.” Formalności spadkowe załatwiono poza ekranem, dokument to osobiste świadectwo woli.

I40: „Notatka Klary: data w zawiadomieniu o śmierci nie zgadza się z późniejszą wzmianką w korespondencji. Brak rozstrzygającego świadectwa. Trzeba odnaleźć autora listu.” Nie generować rozwiązania zagadki matki.

I44: „Uczestniczyłam w działaniach, które miały rozdzielić Mikołaja i Konstancję. Nad stawem próbowałam wyznać prawdę. Osunęłam się z brzegu. Mikołaj i Konstancja wyciągnęli mnie z wody. Podpis: Krystyna.”

I45 przy reconnect: „Nie chcę obiecywać, że zapomnimy. Chciałbym wiedzieć, czy zechcesz ze mną rozmawiać o tym, co dalej. Mikołaj.” Przy separate: „Dziękuję, że pomogłaś przywrócić prawdę. Nie chcę, aby wdzięczność stała się kolejnym zobowiązaniem. Życzę ci własnej drogi. Mikołaj.”

## Teksty zakończeń

E01 PROCH: „Krystyny nie udało się ocalić. Jej śmierć nie stała się jednak wygodną wersją wydarzeń napisaną przez innych. Mikołaj odzyskał wolność. Greta odzyskała imię i grób. Cisza nad stawem przyszła za późno dla jednej z nich.” Następnie: „Ludwik nie podniósł się po śmierci córki. W testamencie zostawił Mikołajowi niewielkie gospodarstwo. Dopiero po latach, u boku Marianny, Mikołaj nauczył się rozpoznawać spokój bez lęku, że zaraz zostanie mu odebrany.” Przy book_marriage: „Konstancja odeszła od Adama.” Bez: „Konstancja nie została żoną Adama.” Dalej wspólne bloki.

E02 PRZERWANE KŁAMSTWO: „Tym razem wiadomość, pytanie i wyciągnięta ręka okazały się silniejsze niż cudzy plan. Krystyna przeżyła i opowiedziała o własnym udziale w spisku. Gretę pochowano pod jej imieniem.” „Mikołaj i Konstancja nie wrócili do dawnej obietnicy, jakby nic się nie wydarzyło. Wybrali rozmowę, a później wspólne życie. Nikt już nie miał udzielać im na nie zgody.” Ludwik pozostaje przy życiu, brak spadku; plansza po latach pokazuje skromny dom kupiony dzięki pracy obojga.

E03 OSOBNE BRZEGI: „Krystyna ocalała. Greta spoczęła w grobie. Nie każda uratowana historia musiała jednak kończyć się dawnym związkiem.” „Mikołaj i Konstancja rozstali się bez kłamstwa. On pozostał blisko Wąglan; po latach związał się z Marianną. Ona wróciła nad morze, gdzie po raz pierwszy mogła zamknąć drzwi dlatego, że sama tego chciała.” Ludwik żyje, nie ma dziedziczenia.

E04 NIESPOKOJNA WODA: „Ludzkie kłamstwa zostały nazwane. Sprawa Grety pozostała otwarta. Nocą nikt nie zatrzymywał się przy stawie na dłużej, niż musiał.” Przy krystyna_alive: „Krystyna przeżyła. O tym, co ciągnęło ją w dół, mówiła rzadko.” W przeciwnym razie: „Krystynę wydobyto i pochowano podczas późniejszych działań ratunkowych. Głębsza część stawu pozostała niezbadana.” To jawna adaptacja otwartego końca; nie zakłada ciała pozostawionego bez końca w wodzie. Przy pair_reunited wspólny dom; inaczej osobne życie, bez twierdzenia, że duch został pokonany.

Blok Karol: jeśli karol_ruined: „Karol stracił majątek, na którym opierał swoją władzę nad innymi.” Inaczej: „Konstancja ocaliła go przed finansową katastrofą. Nie oddała mu jednak prawa do decydowania o swoim życiu.” Jeśli helped_karol: „Pomoc nie oznaczała pojednania bez warunków.”

Blok Marian: jeśli marian_accepted: „Marian zamieszkał z Konstancją nad morzem.” Przy pair_reunited: „Marian pozostał blisko Konstancji; chata rybaka stała się ich miejscem spotkań.” Jeśli odmowa: „Marian uszanował jej potrzebę czasu. Po raz pierwszy czekanie nie było wymuszone.”

Blok rybak: „Rybak nie doczekał powrotu dziewczyny. Zostawił jej dom, łódź i wspomnienie pomocy, za którą nie żądał niczego.”

Ostatnia plansza wszystkich finałów: „Klara rozłożyła na stole papiery Luizy. Jedna data przeczyła drugiej. Konstancja czytała powoli. Historia jej matki być może jeszcze się nie skończyła.” Potem tytuł zakończenia i przyciski Wczytaj / Menu. Brak reklamy obiecywanego sequela.

## Globalne odpowiedzi, bez pustych kliknięć

Nieprzydatna kombinacja: „Nie widzę związku między tymi rzeczami.” Obiekt za daleko: „Stąd nie mogę przyjrzeć się szczegółom.” Zamknięty pojemnik: „Najpierw trzeba go otworzyć.” Przedmiot cudzy: „Nie zabiorę tego bez pozwolenia.” Atak na postać neutralną: „Przemoc nie rozwiąże tej rozmowy.” Spożyj niejadalne: „To nie nadaje się do jedzenia.” Użycie przedmiotu z niewłaściwego ekwipunku jest niemożliwe, nie generuje dowcipu. Powtórzenie ukończonej czynności: „To już zostało zrobione.” Brak wiedzy: „Nie mam jeszcze podstaw, żeby o to zapytać.”

Po ukończeniu Q narrator wyświetla ludzkie podsumowanie ostatniego kroku, a dziennik wpisuje nazwę zadania z oznaczeniem zakończenia i poznane fakty. Nie wyświetla identyfikatorów, booli, warunków ani tekstu success z JSON. Examine dla dekoracji używa opisu sceny/obiektu; przy kluczowych obiektach szczegół z kroku Q ma pierwszeństwo. Żadnych losowych odpowiedzi LLM.


---

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


---

# PROCH — plan weryfikacji i kompletne ścieżki

To plan testów implementacji, nie raport uruchomienia gry. validate_spec.py sprawdza tylko integralność danych autorskich i podstawowy graf zależności. Nie dowodzi poprawności przyszłego silnika.

## Cztery przejścia akceptacyjne

W każdym Q wykonaj wszystkie kroki z 02_QUESTY.md, jeśli nie opisano wariantu. Między zadaniami przełączaj postacie dowolnie w ramach etapu. Kolejność poniżej jest jedną poprawną, nie jedyną.

T01 Książkowy: A M Q01,Q03,Q04,Q05; K Q06,Q07,Q08. B M Q09,Q10,Q11,Q12,Q13; K Q14 confrontation,Q15. C M Q16,Q17,Q18,Q19; K Q21,Q24, pomiń list i Q20. D K Q25; M Q28 „Uwierzę”, pomiń Q26,Q27,Q29; w Q30 K „Biegnij po pomoc”, potwierdź. E K Q31 ślub, Q32,Q33 nie ostrzegaj. F Q34,Q35,Q36,Q37,Q38,Q39 przyjmij Mariana, odejdź od Karola; Q40 osobne drogi, morze, Klara. Oczekuj E01, Krystyna martwa, Karol zrujnowany, M wolny, nawiedzenie zakończone, K odchodzi od Adama.

T02 Przerwane kłamstwo: A M Q01,Q02,Q03,Q04,Q05; K Q06,Q07,Q08. B jak T01, Q14 early. C M Q16–Q19 i Q20; K Q21,Q22,Q23,Q24. D M Q26,Q27; K Q25; M Q28 pokaż list; Q30 uratuj liną. E Q31 przyjęcie bez ślubu, Q32,Q33 ostrzeż. F Q34–Q39; Q40 obie postacie reconnect, morze, Klara. Oczekuj E02, Krystyna żyje, Karol nie zbankrutował, nawiedzenie zakończone, brak spadku po Ludwiku.

T03 Osobne brzegi bez przygotowania: A/B jak T01. C M Q16–Q19; K Q21,Q24. D K Q25,Q29 pierwszy fragment; M odczytaj I43 i spotkaj K, dokończ Q29, następnie Q28. Bez Q27 uratuj Krystynę konarem I42 w Q30. E Q31 przyjęcie,Q32,Q33 nie ostrzegaj. F Q34–Q39, Q40 M reconnect/K separate. Oczekuj E03, Krystyna żyje, lina nie była wymagana, niezależna decyzja K zachowana.

T04 Otwarta tajemnica: jak T02 do Q35. Pomiń Q36–38; wykonaj Q39,Q40 z separate dla obojga; potwierdź pozostawienie sprawy stawu. Oczekuj E04. Dostępne cofnięcie przed końcem pozwala jednak ukończyć Q36–38 i otrzymać E03.

## Testy przeciwdziałania blokadom

- Zmieniaj postać po każdym bezpiecznym substepie Q09,Q12,Q21,Q23,Q29. Po powrocie dokładnie ten sam stan, bez powielania itemów.
- Zakończ całą dostępną ścieżkę M przed rozpoczęciem K i odwrotnie. Na barierze etapów zawsze można przełączyć, żaden dzień nie upływa automatycznie.
- Nigdy nie wykonuj Q02: Q24 nadal znajduje adres w księdze.
- Wyślij list, nie przeczytaj go jako M: m_knows_alive pozostaje false.
- Przeczytaj informację wyłącznie jako K: temat w dialogu M nie pojawia się do transferu.
- Zrób Q29 przed ogrodem i po urywku rozmowy, lecz przed zatwierdzeniem Q28. Obie kolejności prowadzą do calm.
- Przygotuj linę, potem porzuć hak w warsztacie przed zakończeniem Q27: Q27 nie kończy się, dopóki komplet nie jest przy głazie. Nie ustawiaj rescue_rig przedwcześnie.
- Nie przygotuj liny: konar zawsze dostępny w Q30. Przyglądanie się mu 100 razy nie zabija Krystyny.
- Wejdź K do wody, wybierz Cofnij: przywrócony cały stan obu postaci i wyposażenie. Nie przywracaj tylko aktywnej postaci.
- Nie zabieraj Biblii: wszystkie zakończenia pozostają osiągalne.
- Odłóż dokument w bezpiecznym pokoju, zamknij etap: rzeczy osobiste wracają do walizki. I38 nie teleportuje do kieszeni.
- Czytaj dokument ponownie: brak duplikatów nagród, flag, listów i wpisów.
- Próba ponownego ślubu w ścieżce żywej Krystyny jest niedostępna, bo book_marriage=false ustawiono jawnie.
- W E przełącz do M w areszcie: widzisz M i kraty, bez dostępu do pałacu. Możesz zawsze wrócić do K.
- Zachowanie Karola w epilogu odpowiada Q33; nie wyświetlaj bankructwa po ostrzeżeniu.
- Przy śmierci Krystyny i otwartym zakończeniu jej pochówek jest wspomniany, lecz Greta pozostaje nieodnaleziona.

## Testy platformowe i zasobów

1. Kompilacja 68000 i uruchomienie z 4 MB na SE/System6.0.8; raport wolnej sterty, rozmiaru partition i maksymalnego zużycia po 200 przejściach lokacji.
2. Ten sam build na SE/30 i dostępnym System7, bez użycia rozszerzeń specyficznych dla tego sprzętu.
3. Wszystkie tła 360×208, dwa kolory; ikony24×24, portrety48×48; brak ukrytej palety szarości i alfa innych niż maska 0/1.
4. Wszystkie napisy z ĄąĆćĘęŁłŃńÓóŚśŹźŻż; brak zastępczych krzaczków na angielskim systemie.
5. Każdy hotspot w obrazie, kliknięcie po krawędzi rozstrzygane jednoznacznie; widoczne przedmioty znikają po zabraniu.
6. Save/load przy każdym zakończeniu Q, po doręczeniu przed odczytem listu, po złożeniu wiadomości K i po podaniu liny w Q30. Stan po odczycie równoważny sprzed zapisu.
7. Uszkodzony CRC, skrócony pakiet, brak pliku, niezgodna wersja save i pełny dysk: czytelny błąd, brak crasha, nie kasuj starego save.
8. UI tylko jedną myszą, wyciszony dźwięk i wyłączone animacje: cała gra nadal przechodnia.
9. Brak stale aktywnej pętli obciążającej CPU i wczytywania całego katalogu ilustracji. Sprawdź ścieżki podczas częstego przełączania postaci.
10. Playtest bez znajomości rozwiązania: mierzyć czas, liczbę podpowiedzi, powtarzające się niejasności. Cel 8–12 godzin zweryfikować dopiero wtedy. Nie sztucznie wydłużać dialogów, marszu i ładowania.

## Definicja ukończenia

Wszystkie Q i zakończenia działają; pełne polskie teksty; wszystkie wymagane sceny, ikony i warianty gotowe; instalowalny build zachowujący forki; kompletne przejście co najmniej w emulatorze SE z 4 MB i System6.0.8; raport mówi uczciwie, czy był test fizycznego SE. Placeholdery są dozwolone w etapach, nie w wersji oznaczonej jako finalna.
