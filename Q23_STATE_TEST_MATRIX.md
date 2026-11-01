# Q23 — mapa stanów i przypadków testowych

Przygotowanie treści, bez reguł silnika. Kolejność narracyjna: warunek Q22,
papier i szkic, właściwa treść, prywatne wspomnienie broszki, przekazanie
sąsiadowi. Używać istniejących `Q23_WRITE`, `Q23_WORDS`, `Q23_MEMORY`,
`Q23_SEND` i odpowiedzi `Q23_DRAFT_REPLY`, `Q23_MEMORY_REPLY`,
`Q23_SENT_REPLY`. Gdy brakuje I10, etykieta `Q23_TAKE_EXTRA_PAPER` i odpowiedź
`Q23_PAPER_TAKEN` opisują pobranie jednej kartki z nieograniczonego zapasu;
`Q23_EXTRA_PAPER` informuje o jego dostępności. Błędne działania mogą użyć
wspólnej odpowiedzi `NO_EFFECT`.

| Stan lub przypadek | Przygotowanie i akcje | Oczekiwany wynik |
| --- | --- | --- |
| Brak Q22 | K próbuje otworzyć tematy Q23 w L33/L34 lub przekazać list | Tematy niedostępne; stan, przedmioty i flagi bez zmian. |
| I10 obecne | Po Q22 rozpocznij szkic przez `Q23_WRITE`; wybierz `Q23_WORDS` | Szkic powstaje na posiadanym papierze; I10 nie jest wymaganiem do żadnej innej gałęzi Q23. |
| I10 brak | W L33 wybierz `Q23_TAKE_EXTRA_PAPER`, potem napisz szkic | Dostępny jest jeden czysty arkusz; pobranie nie blokuje listu i zapas można uzupełnić ponownie. |
| Błędna treść | Po szkicu wybierz inną treść lub spróbuj wysłać przed poprawną treścią | Wspólne `NO_EFFECT`; brak I28, `PR_LETTER_SENT` i ukończenia Q23. |
| Brak wspomnienia | Przy poprawnej treści pomiń `Q23_MEMORY` i spróbuj przekazać | Przekazanie niedostępne lub odrzucone; brak I28 i zmian stanu zadania. |
| Jeden fizyczny I28 | Ukończ szkic, wybierz poprawną treść i wspomnienie, przekaż `Q23_SEND` | Powstaje jeden I28 na trasie kuriera; K nie ma drugiego fizycznego egzemplarza. Q23 i `PR_LETTER_SENT` ustawiają się raz; I27/I11 pozostają. |
| Przed wejściem do D | Po wysłaniu przełącz na M i sprawdź stan wiadomości oraz wiedzę | I28 nadal czeka u kuriera; M nie zna listu, nie zna życia K i `PR_M_KNOWS_ALIVE` pozostaje wyłączone. |
| Wejście do D | Rozpocznij D po spełnieniu warunków przejścia | Jedyny I28 trafia do Florka. Sama dostawa nie ujawnia listu M; wiedza powstaje dopiero po rozpoznaniu w Q26. |

Przyszłe testy reguł prowadzić przez publiczne `pr_act`; weryfikować brak
mutacji po każdym odrzuconym działaniu, pozycję I28 i wiedzę obu postaci.
