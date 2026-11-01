#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
mkdir -p build/host
"${CC:-cc}" -std=c99 -Wall -Wextra -Werror -g -fsanitize=address,undefined \
    -Isrc src/render_1bit.c tests/test_render.c -o build/host/test_render
ASAN_OPTIONS=detect_leaks=0 build/host/test_render
"${CC:-cc}" -std=c99 -Wall -Wextra -Werror -g -fsanitize=address,undefined \
    -Isrc src/engine.c tests/test_engine.c -o build/host/test_engine
ASAN_OPTIONS=detect_leaks=0 build/host/test_engine
python3 tools/generate_campaign.py
"${CC:-cc}" -std=c99 -Wall -Wextra -Werror -g -fsanitize=address,undefined \
    -Isrc -Isrc/campaign -Ibuild/generated src/campaign/model.c src/campaign/world.c \
    build/generated/campaign_data.c tests/test_campaign_model.c -o build/host/test_campaign_model
ASAN_OPTIONS=detect_leaks=0 build/host/test_campaign_model
"${CC:-cc}" -std=c99 -Wall -Wextra -Werror -g -fsanitize=address,undefined \
    -Isrc -Isrc/campaign -Ibuild/generated src/campaign/model.c src/campaign/world.c \
    src/campaign/rules.c src/campaign/rules_a.c build/generated/campaign_data.c \
    tests/test_campaign_a.c -o build/host/test_campaign_a
ASAN_OPTIONS=detect_leaks=0 build/host/test_campaign_a
python3 validate_spec.py
