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
