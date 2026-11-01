#include "render_1bit.h"
#include <string.h>

typedef char proch_u16_must_be_two_bytes[sizeof(uint16_t) == 2 ? 1 : -1];
typedef char proch_u32_must_be_four_bytes[sizeof(uint32_t) == 4 ? 1 : -1];
typedef char proch_buffer_must_match_stride[sizeof(ProchBitmap) == 9568 ? 1 : -1];

static uint8_t *bytes(ProchBitmap *bitmap) { return (uint8_t *)bitmap->words; }

uint8_t proch_pixel(const ProchBitmap *bitmap, int16_t x, int16_t y)
{
    const uint8_t *data = (const uint8_t *)bitmap->words;
    if (x < 0 || x >= PROCH_WIDTH || y < 0 || y >= PROCH_HEIGHT) return 0;
    return (data[(uint32_t)y * PROCH_STRIDE + (x >> 3)] >> (7 - (x & 7))) & 1;
}

void proch_pattern(ProchBitmap *bitmap, uint8_t alternate)
{
    int16_t x, y;
    uint8_t *data = bytes(bitmap);
    memset(bitmap, 0, sizeof(*bitmap));
    for (y = 0; y < PROCH_HEIGHT; ++y)
        for (x = 0; x < PROCH_WIDTH; ++x) {
            uint8_t bit = alternate ? ((x / 8 + y / 8) & 1) : ((x + y) & 1);
            if (bit) data[(uint32_t)y * PROCH_STRIDE + (x >> 3)] |= 0x80u >> (x & 7);
        }
}

void proch_invert(ProchBitmap *bitmap, int16_t x, int16_t y)
{
    int16_t dx, dy;
    uint8_t *data = bytes(bitmap);
    for (dy = -3; dy <= 3; ++dy)
        for (dx = -3; dx <= 3; ++dx) {
            int16_t px = x + dx, py = y + dy;
            if (px >= 0 && px < PROCH_WIDTH && py >= 0 && py < PROCH_HEIGHT)
                data[(uint32_t)py * PROCH_STRIDE + (px >> 3)] ^= 0x80u >> (px & 7);
        }
}
