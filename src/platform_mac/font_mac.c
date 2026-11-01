#include <Quickdraw.h>
#include "font_mac.h"
#include "font.h"

const char *proch_font_sample(void) { return PROCH_FONT_SAMPLE; }

void proch_text(short x, short baseline, const char *encoded)
{
    BitMap atlas;
    GrafPtr port;
    short start = x;
    const unsigned char *p = (const unsigned char *)encoded;
    atlas.baseAddr = (Ptr)proch_font.data;
    atlas.rowBytes = 12;
    SetRect(&atlas.bounds, 0, 0, 96, 88);
    GetPort(&port);
    while (*p) {
        unsigned char c = *p++;
        short index;
        Rect source, dest;
        if (c == '\n') { baseline += 12; x = start; continue; }
        if (c >= 32 && c <= 126) index = c - 32;
        else if (c >= 0x80 && c <= 0x91) index = 95 + c - 0x80;
        else continue; /* Compiler rejects unsupported text before packaging. */
        SetRect(&source, (index % 16) * 6, (index / 16) * 11,
                (index % 16) * 6 + 6, (index / 16) * 11 + 11);
        SetRect(&dest, x, baseline - 8, x + 6, baseline + 3);
        /* The monochrome black glyph is its own transparent stencil/mask. */
        CopyBits(&atlas, &port->portBits, &source, &dest, srcOr, NULL);
        x += 7;
    }
}
