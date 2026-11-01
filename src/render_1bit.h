#ifndef PROCH_RENDER_1BIT_H
#define PROCH_RENDER_1BIT_H
#include <stdint.h>
enum { PROCH_WIDTH = 360, PROCH_HEIGHT = 208, PROCH_STRIDE = 46,
       PROCH_SCENE_BYTES = PROCH_STRIDE * PROCH_HEIGHT };
/* Word-aligned storage for the QuickDraw BitMap. MSB leftmost; 1 = black. */
typedef struct { uint16_t words[PROCH_SCENE_BYTES / 2]; } ProchBitmap;
void proch_pattern(ProchBitmap *bitmap, uint8_t alternate);
void proch_invert(ProchBitmap *bitmap, int16_t x, int16_t y);
uint8_t proch_pixel(const ProchBitmap *bitmap, int16_t x, int16_t y);
#endif
