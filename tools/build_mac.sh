#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
repo_dir=$PWD
dist_dir=${PROCH_DIST_DIR:-dist}
mode=${1:-source}
smoke=${2:-OFF}
[[ $mode == source || $mode == bootstrap ]] || { echo 'Usage: build_mac.sh [source|bootstrap] [ON|OFF]' >&2; exit 2; }
[[ $smoke == ON || $smoke == OFF ]] || exit 2
image=$(python3 -c 'import json; print(json.load(open("toolchain.lock.json"))["bootstrap_image"])')
build_dir=${PROCH_TOOLCHAIN_BUILD:-/workspace/toolchains/Retro68-build}
container_args=()
prefix=/Retro68-build/toolchain
if [[ $mode == source ]]; then
    expected=$(python3 -c 'import json; print(json.load(open("toolchain.lock.json"))["retro68_commit"])')
    [[ -f "$build_dir/proch-source-commit" && $(cat "$build_dir/proch-source-commit") == "$expected" ]] || {
        echo 'Pinned source toolchain not ready; run tools/build_toolchain.sh. bootstrap mode is explicitly provisional.' >&2; exit 1;
    }
    container_args=(-v "$build_dir:/build:ro")
    prefix=/build/toolchain
fi
target=mac
[[ $smoke == OFF ]] || target=mac-smoke
docker run --rm --network none --user "$(id -u):$(id -g)" --entrypoint /bin/bash \
    -v "$repo_dir:/project" "${container_args[@]}" -w /project "$image" -lc '
        set -e
        cmake -S . -B "build/$1" -DCMAKE_TOOLCHAIN_FILE="$2/m68k-apple-macos/cmake/retro68.toolchain.cmake" \
            -DPROCH_AUTOTEST="$3" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
        cmake --build "build/$1" --parallel 4
    ' -- "$target-$mode" "$prefix" "$smoke"
if [[ $smoke == OFF ]]; then
    python3 tools/check_artifacts.py "build/$target-$mode"
    mkdir -p "$dist_dir"
    cp "build/$target-$mode/PROCH.bin" "build/$target-$mode/PROCH.dsk" "$dist_dir/"
fi
