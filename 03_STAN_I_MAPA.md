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
