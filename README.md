# PROCH — pakiet dla Codexa, wersja 1.0

Autor powieści: Szymon Broma. Projekt adaptacji przygotowany 1 listopada 2026 zgodnie z ustaleniami rozmowy. Docelowo Macintosh SE/SE30, 4 MB RAM, System 6.0.8, 512×342, 1-bit.

## Jak przekazać Codexowi

Rozpakuj całe archiwum do repozytorium projektu, np. do folderu spec/PROCH_Codex_v1. Otwórz repozytorium w Codex i wklej:

> Zrealizuj grę PROCH zgodnie z pakietem spec/PROCH_Codex_v1. Zacznij od 00_START_DLA_CODEXA.md, przeczytaj wszystkie dokumenty oraz dane JSON. Wykonaj natywną aplikację dla Macintosh SE z 4 MB RAM i Systemem 6.0.8, nie wersję WWW. Pracuj etapami opisanymi w instrukcji aż do pełnej gry. Zachowaj dwie przełączane postacie, wszystkie questy, rozgałęzienia i zakończenia. Weryfikuj postęp testami, a braki narzędzi lub nieprzetestowane wymagania raportuj precyzyjnie.

Jeśli folder ma inną nazwę, zmień tylko ścieżkę w tej wiadomości. Nie trzeba wklejać całej książki do pojedynczego promptu — jest w sources.

## Zawartość

- 00_START_DLA_CODEXA.md — główne polecenie wykonawcze i etapy pracy.
- 01_ZALOZENIA.md — ustalenia autora i świadome odstępstwa adaptacji.
- 02_QUESTY.md — 40 zadań, kroki, błędy i 120 podpowiedzi.
- 03_STAN_I_MAPA.md — czas, przełączanie, transfer informacji, podróże i warunki finałów.
- 04_PRZEDMIOTY.md — 45 przedmiotów i ich przeznaczenie.
- 05_GRAFIKI_I_LOKACJE.md — 43 lokacje, obszary kliknięć, prompty wszystkich bazowych grafik i wariantów.
- 06_DIALOGI_I_ZAKONCZENIA.md — kwestie główne, dokumenty, cztery finały i odpowiedzi systemowe.
- 07_TECHNIKA.md — interfejs, font PL, pamięć, zasoby, zapisy, audio i dystrybucja.
- 08_TESTY_I_PRZEJSCIA.md — ścieżki zakończeń i plan testów.
- quests.json, scenes.json, items.json, assets.json — dane autorskie do przetworzenia przez implementatora.
- validate_spec.py — kontrola referencji danych, nie silnik gry.
- sources/ — oryginalne materiały fabularne.
- reference/ — podgląd stylu, rzeczywiste 512×342 i 1-bit, nie działająca gra.

Pakiet zawiera opisy grafik, nie wyprodukowany komplet ilustracji. Nie zawiera jeszcze skompilowanej gry. Część techniczna jest projektem do weryfikacji prototypem. Dialogi są kompletem głównych kwestii i reguł odpowiedzi, nie transkrypcją powieści. Pola JSON success/requires są opisem autorskim, nie kodem wykonywanym przez grę.
