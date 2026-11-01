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
