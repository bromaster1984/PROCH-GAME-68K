# Pierwsze ilustracje scen

`art/bg/L33.source.png` i `L34.source.png` są oryginalnymi obrazami źródłowymi
przygotowanymi dla PROCH. Wersje gry w `bg/` mają dokładnie 360×208 pikseli,
tryb 1-bit i wyłącznie czarne oraz białe piksele. Powstały poleceniem:

```sh
convert art/bg/L33.source.png -filter Lanczos -resize '360x208!' -colorspace Gray -threshold 55% -type bilevel bg/L33.png
convert art/bg/L34.source.png -filter Lanczos -resize '360x208!' -colorspace Gray -threshold 55% -type bilevel bg/L34.png
python3 tools/pack_scene_art.py pack
```

`art/packed/*.bin` zawiera wiersze QuickDraw po 46 bajtów, z ostatnim bajtem
każdego wiersza równym zero. `python3 tools/pack_scene_art.py check` potwierdza
zgodność bitmap z PNG. Build generuje z tych plików kod C, bez wymagania
Pillow wewnątrz kontenera Retro68. L33 używa na razie jednego obrazu bazowego;
warianty `L33_alive` i `L33_empty` z manifestu pozostają do przygotowania.
