#ifndef PROCH_FONT_MAC_H
#define PROCH_FONT_MAC_H
/* Encoded strings: ASCII plus the explicit 0x80..0x91 Polish table. */
void proch_text(short x, short baseline, const char *encoded);
const char *proch_font_sample(void);
#endif
