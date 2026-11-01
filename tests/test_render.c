#include "render_1bit.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    ProchBitmap bitmap, before;
    int x, y, changed = 0;
    const uint8_t *raw = (const uint8_t *)bitmap.words;
    proch_pattern(&bitmap, 0);
    assert(raw[0] == 0x55 && raw[46] == 0xaa);
    for (y = 0; y < PROCH_HEIGHT; ++y) {
        for (x = 0; x < PROCH_WIDTH; ++x)
            assert(proch_pixel(&bitmap, x, y) == ((x + y) & 1));
        assert(raw[y * PROCH_STRIDE + 45] == 0); /* row padding */
    }
    before = bitmap;
    proch_invert(&bitmap, 0, 0);
    for (y = 0; y < PROCH_HEIGHT; ++y)
        for (x = 0; x < PROCH_WIDTH; ++x)
            changed += proch_pixel(&bitmap, x, y) != proch_pixel(&before, x, y);
    assert(changed == 16); /* 7x7 brush clipped to the top-left corner. */
    proch_invert(&bitmap, 0, 0);
    assert(memcmp(&bitmap, &before, sizeof(bitmap)) == 0);
    proch_invert(&bitmap, 359, 207);
    assert(raw[207 * 46 + 45] == 0); /* never paint into padding */
    proch_invert(&bitmap, 359, 207);
    assert(memcmp(&bitmap, &before, sizeof(bitmap)) == 0);
    proch_invert(&bitmap, -100, -100);
    assert(memcmp(&bitmap, &before, sizeof(bitmap)) == 0);
    assert(!proch_pixel(&bitmap, -1, 0) && !proch_pixel(&bitmap, 360, 208));
    proch_pattern(&bitmap, 1);
    assert(!proch_pixel(&bitmap, 7, 7) && proch_pixel(&bitmap, 8, 7));
    puts("PASS: pixel polarity, row alignment, clipping, retained edits (C host)");
    return 0;
}
