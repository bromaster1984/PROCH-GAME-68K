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
