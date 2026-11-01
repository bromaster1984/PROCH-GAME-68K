#!/usr/bin/env bash
# Out-of-tree source build. Preserve existing checkouts; never reset them.
set -euo pipefail
repo_dir=$(cd "$(dirname "$0")/.." && pwd)
tools_dir=${PROCH_TOOLS_DIR:-/workspace/toolchains}
source_dir="$tools_dir/Retro68"
build_dir="$tools_dir/Retro68-build"
read_lock() { python3 -c 'import json,sys; print(json.load(open(sys.argv[1]))[sys.argv[2]])' "$repo_dir/toolchain.lock.json" "$1"; }
commit=$(read_lock retro68_commit)
image=$(read_lock bootstrap_image)
new_checkout=0
mkdir -p "$tools_dir" "$build_dir"
if [[ ! -e "$source_dir" ]]; then
    git clone --depth 1 --no-checkout "$(read_lock retro68_repository)" "$source_dir"
    new_checkout=1
fi
if [[ $new_checkout == 1 ]]; then
    git -C "$source_dir" fetch --depth 1 origin "$commit"
    git -C "$source_dir" checkout --detach "$commit"
fi
[[ $(git -C "$source_dir" rev-parse HEAD) == "$commit" ]] || {
    echo "Existing Retro68 checkout has another revision; use a separate PROCH_TOOLS_DIR." >&2; exit 1;
}
[[ -z $(git -C "$source_dir" diff --name-only HEAD) ]] || {
    echo "Retro68 source has local changes; preserve them and use a separate PROCH_TOOLS_DIR." >&2; exit 1;
}
git -C "$source_dir" submodule update --init --depth 1
[[ $(git -C "$source_dir/multiversal" rev-parse HEAD) == "$(read_lock multiversal_commit)" ]]
if [[ ${1:-} != --refresh && -f "$build_dir/proch-source-commit" &&
      $(cat "$build_dir/proch-source-commit") == "$commit" &&
      -x "$build_dir/toolchain/bin/Rez" &&
      -x "$build_dir/toolchain/bin/m68k-apple-macos-gcc" ]]; then
    echo "Reusing pinned source toolchain: $build_dir (use --refresh to rebuild)"
    exit 0
fi
# Network is unnecessary during compilation. Docker pull and Git retain TLS verification.
docker image inspect "$image" >/dev/null 2>&1 || docker pull "$image"
docker run --rm --network none --user "$(id -u):$(id -g)" --entrypoint /bin/bash \
    -v "$source_dir:/src/Retro68" -v "$build_dir:/build" -w /build \
    -e CMAKE_BUILD_PARALLEL_LEVEL=4 "$image" \
    -lc '/src/Retro68/build-toolchain.bash --no-ppc --multiversal && chmod -R a+rX /build/toolchain'
printf '%s\n' "$commit" > "$build_dir/proch-source-commit"
echo "Toolchain source build complete: $build_dir"
