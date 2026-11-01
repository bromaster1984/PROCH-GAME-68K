#!/usr/bin/env python3
"""Pack 360x208 monochrome PNGs for QuickDraw and embed packed files in C.

The 46-byte row stride is even, as required by a classic QuickDraw BitMap.
Bit 1 means black in the packed output; the last byte of each row is padding.
The cross-build uses only `embed` and does not require Pillow.
"""
import argparse
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
NAMES = ("L33", "L34")
WIDTH, HEIGHT, STRIDE = 360, 208, 46


def packed_png(name):
    from PIL import Image

    image = Image.open(ROOT / "bg" / (name + ".png"))
    if image.size != (WIDTH, HEIGHT) or image.mode != "1":
        raise ValueError(f"{name}: expected {WIDTH}x{HEIGHT} mode 1")
    data = image.tobytes()
    output = bytearray()
    for y in range(HEIGHT):
        output.extend((byte ^ 0xff) for byte in data[y * 45:(y + 1) * 45])
        output.append(0)
    return bytes(output)


def pack(check):
    for name in NAMES:
        dest = ROOT / "art" / "packed" / (name + ".bin")
        data = packed_png(name)
        if check:
            if not dest.exists() or dest.read_bytes() != data:
                raise ValueError(f"{dest} does not match the 1-bit PNG")
        else:
            dest.parent.mkdir(parents=True, exist_ok=True)
            dest.write_bytes(data)
        print(f"{name}: {len(data)} bytes, PNG and packed bitmap match")


def embed(output):
    lines = ['#include "scene_art.h"', '']
    for name in NAMES:
        data = (ROOT / "art" / "packed" / (name + ".bin")).read_bytes()
        if len(data) != STRIDE * HEIGHT:
            raise ValueError(f"{name}: packed bitmap has wrong size")
        lines.append(f"static const uint8_t art_{name}[{STRIDE * HEIGHT}] = {{")
        for index in range(0, len(data), 16):
            lines.append("    " + ", ".join(f"0x{byte:02x}" for byte in data[index:index + 16]) + ",")
        lines.append("};")
        lines.append("")
    lines += ["const uint8_t *proch_scene_art(unsigned scene)", "{",
              "    if (scene == 33) return art_L33;",
              "    if (scene == 34) return art_L34;",
              "    return 0;", "}", ""]
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text("\n".join(lines))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("command", choices=("pack", "check", "embed"))
    parser.add_argument("output", type=Path, nargs="?")
    args = parser.parse_args()
    if args.command == "embed":
        if args.output is None:
            parser.error("embed requires an output C path")
        embed(args.output)
    else:
        pack(args.command == "check")


if __name__ == "__main__":
    main()
