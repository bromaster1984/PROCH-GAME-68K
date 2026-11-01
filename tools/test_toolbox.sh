#!/usr/bin/env bash
# Extra Toolbox test under Executor. This does not emulate an SE or System 6.
set -euo pipefail
cd "$(dirname "$0")/.."
mode=${1:-source}
executor_dir=${PROCH_EXECUTOR_DIR:-/workspace/tools/executor}
binary="$executor_dir/Executor2000-0.1.0-Linux/bin/executor-headless"
[[ -x $binary ]] || { echo 'Executor 2000 v0.1.0 not installed; see toolchain.lock.json' >&2; exit 1; }
bash tools/build_mac.sh "$mode" ON
image=$(python3 -c 'import json; print(json.load(open("toolchain.lock.json"))["bootstrap_image"])')
target="mac-smoke-$mode"
docker run --rm --network none --entrypoint /bin/bash \
    -v "$PWD:/project" -v "$executor_dir:/executor:ro" -w /project "$image" -lc '
        set -e
        rm -f "build/$1/out" "build/$1/SCREEN.PBM"
        timeout 25s /executor/Executor2000-0.1.0-Linux/bin/executor-headless \
            -bpp 1 -size 512x342 -memory 4M -applzone 2M -nosound -nobrowser "build/$1/PROCH.ad"
        test "$(cat "build/$1/out")" = PROCH_TOOLBOX_SMOKE_PASS
        cat "build/$1/out"
        chmod a+rw "build/$1/out" "build/$1/SCREEN.PBM"
    ' -- "$target"
python3 - "$target" <<'PY'
from pathlib import Path
import sys
from PIL import Image
p=Path('build')/sys.argv[1]/'SCREEN.PBM'
im=Image.open(p)
assert im.size == (512,342) and im.mode == '1'
Path('screenshots').mkdir(exist_ok=True)
im.save('screenshots/etap1-executor2000.png')
print('PASS: native framebuffer 512x342, 1-bit, lossless PBM -> PNG')
PY
