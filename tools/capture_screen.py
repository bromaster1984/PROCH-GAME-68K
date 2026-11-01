#!/usr/bin/env python3
"""Lossless conversion of a native PBM or `xwd -nobdrs` screenshot, no retouching."""
from pathlib import Path
import struct
import sys
from PIL import Image


def convert(source, dest):
    source = Path(source)
    if source.suffix.lower() == '.xwd':
        data = source.read_bytes()
        h = struct.unpack_from('>25I',data)
        if (h[1],h[4],h[5],h[11],h[14],h[15],h[16]) != (7,512,342,32,0xff0000,0xff00,0xff):
            raise ValueError('Expected a borderless 512x342 XWD screen with 32-bit RGB pixels')
        im = Image.frombytes('RGB',(512,342),data[h[0]+12*h[19]:],
                             'raw','BGRX' if h[7]==0 else 'XRGB',h[12],1)
    else:
        im = Image.open(source).convert('RGB')
    colors = im.getcolors()
    if im.size != (512,342) or colors is None or not {c for n,c in colors} <= {(0,0,0),(255,255,255)}:
        raise ValueError('Screen is not exactly 512x342 black/white; refusing quantization')
    im.convert('1',dither=Image.Dither.NONE).save(dest)


if __name__ == '__main__': convert(sys.argv[1],sys.argv[2])
