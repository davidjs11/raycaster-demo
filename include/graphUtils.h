#ifndef GRAPH_UTILS
#define GRAPH_UTILS
#include <stdint.h>
// creates a 32-bit int with 4 color keys (RGBA). Used in the framebuffer
uint32_t packColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#endif
