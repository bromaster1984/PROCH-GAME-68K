# Bitmapowa czcionka PROCH

Źródło oryginalnych glifów: `tools/generate_content.py`, funkcja `glyphs()`.
Komórka 6×11, przesunięcie poziome 7 px, interlinia 12 px. Glify mają do pięciu
kolumn atramentu i dodatkowe wiersze na akcenty i ogonki. Rysowanie przez
monochromatyczny CopyBits, bez zależności od liter w systemowym Chicago.

ASCII 0x20–0x7E. Dalej dokładnie:

| Bajty | Litery |
| --- | --- |
| 80 81 | Ą ą |
| 82 83 | Ć ć |
| 84 85 | Ę ę |
| 86 87 | Ł ł |
| 88 89 | Ń ń |
| 8A 8B | Ó ó |
| 8C 8D | Ś ś |
| 8E 8F | Ź ź |
| 90 91 | Ż ż |

Po `python3 tools/generate_content.py` w `build/generated/` powstają atlas
96×88, maska 1-bit, nagłówek fontu oraz etykiety gry. Atlas ma 16 komórek
w wierszu. W masce 1 oznacza atrament; czarny glif jest zarazem swoim szablonem
do operacji srcOr. Atlas i maska są identyczne i nie wymagają dwóch kopii RAM.

UTF-8 jest konwertowane na hoście. Cudzysłowy typograficzne, długie pauzy,
wielokropek i twarda spacja mają jawne normalizacje. Inny nieobsługiwany znak
zatrzymuje kompilację danych. Runtime nie interpretuje UTF-8 ani JSON.

Zweryfikowano próbkę polskich liter w natywnej aplikacji w Mini vMac Plus,
System 6.0.8, 4 MB. Pełne dialogi i ich łamanie wierszy pozostają osobnym etapem.
