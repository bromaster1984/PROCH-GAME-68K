# Faza C K — kontrakt implementacyjny Q22–Q24

Kontrakt na podstawie `02_QUESTY.md`, `06_DIALOGI_I_ZAKONCZENIA.md`,
`items.json` i `scenes.json`. Q22 i Q23 są sprawdzone natywnie, a reguły Q24
mają testy hostowe od etapu 3o. Natywna weryfikacja Q24 pozostaje do zrobienia.

## Q22 — sieć i zaufanie (L34, po Q21)

K rozmawia z sąsiadem (L34_H1), ogląda sieć (L34_H2), używa I25, po czym
łączy lewy koniec ze środkowym i środkowy z prawym. Zatwierdzenie wzoru
pozwala ponownie zapytać sąsiada; dopiero jego odpowiedź kończy Q22,
ustawia `PR_SAFE_COURIER` i daje K I27.
Q22 jest opcjonalne i nie może być wymagane przez Q24 ani przejście do D.

Błędne połączenie wyświetla „Oczko się zaciska. Rozplątuję nić” i zeruje
wyłącznie bieżącą układankę. Nie ustawia flagi, nie kończy zadania, nie daje
I27 i nie zużywa I25. Samo użycie I25 nie zastępuje potwierdzenia wzoru.

## Q23 — list „Żyję” (wymaga Q22, L33/L34)

K pisze list do Izydora. Jeśli I10 nie ma w ekwipunku, L33 zapewnia kolejny
czysty arkusz bez limitu. Wybiera treść „Żyję. Nie ufaj wieściom o mojej
śmierci. Przekaż Mikołajowi”, dodaje wspomnienie broszki motyla i przekazuje
I28 sąsiadowi. Ustawia `PR_LETTER_SENT`; K zachowuje odpis, a pojedynczy
fizyczny egzemplarz czeka na przekazanie Florkowi przy wejściu do D. Samo
wysłanie nie daje M wiedzy o życiu K; rozpoznanie następuje w Q26.

## Q24 — powrót (wymaga Q21; Q22/Q23 są niezależne)

Rybak w L33 daje K I29 na podróż niezależnie od naprawienia sieci. W L35
K pokazuje I07 kasjerowi, kupuje bilet i jedzie do Warszawy. W L04 gałąź
z `PR_ADDRESS_LEFT` pozwala Izydorowi od razu podać Wąglany. Bez flagi K
prosi o zgodę na sprawdzenie księgi wysyłek Koreckich, czyta wpis i poznaje
ten sam adres. Podróż kończy się w L08, zadaniem Q24 i gotowością K do D.

Przejście C→D wymaga Q19 oraz Q24. Bez obu zadań stan i faza pozostają bez
zmian; przy spełnionych warunkach wymagane jest osobne potwierdzenie gracza.
Q22, Q23 i `PR_SAFE_COURIER` nie mogą blokować podróży ani tej bariery.

## Przypadki testowe i regresje

- Q22: przed Q21 brak tematów; przed zgodą sąsiada nie ma postępu. Sprawdź
  poprawny wzór w kolejności lewy→środkowy→prawy oraz błędne połączenie
  na każdym kroku. Błąd ma resetować tylko układankę; poprawne zatwierdzenie
  daje Q22, flagę i jedno I27. Powtórne zebranie nie duplikuje I27. I25 zostaje.
- Q23: z blokadą Q22 nie da się wysłać listu. Przy braku I10 gra zapewnia
  papier w L33. Błędna treść lub brak wspomnienia nie tworzą I28 ani flagi.
  Po wysłaniu K nie ma fizycznego I28, ma odpis, ustawia się `PR_LETTER_SENT`,
  a M nadal nie zna treści ani nie wie, że K żyje. W D list trafia do Florka;
  wiedza M powstaje dopiero po poprawnym rozpoznaniu w Q26.
- Q24: ukończ Q21 bez Q22/Q23 i sprawdź, że rybak nadal daje I29, a podróż
  jest dostępna. Sprawdź też obie gałęzie adresu: `PR_ADDRESS_LEFT` i zgodę
  na księgę przy braku flagi; obie prowadzą do L08 bez zmiany tej flagi.
- Bariera C→D: brak Q19 lub brak Q24 nie zmienia stanu; gdy oba są ukończone,
  wywołanie bez potwierdzenia zwraca `PR_CONFIRMATION` bez mutacji, a dopiero
  jawne potwierdzenie zmienia fazę i uruchamia doręczenie oczekujących listów.
