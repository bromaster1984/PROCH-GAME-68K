#ifndef PROCH_SCENE_ART_H
#define PROCH_SCENE_ART_H
#include <stdint.h>

/* Packed QuickDraw rows, 360x208 pixels, 46 bytes per row; 1 means black. */
const uint8_t *proch_scene_art(unsigned scene);

#endif
