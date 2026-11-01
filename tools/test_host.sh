#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
mkdir -p build/host
"${CC:-cc}" -std=c99 -Wall -Wextra -Werror -g -fsanitize=address,undefined \
    -Isrc src/render_1bit.c tests/test_render.c -o build/host/test_render
ASAN_OPTIONS=detect_leaks=0 build/host/test_render
python3 validate_spec.py
