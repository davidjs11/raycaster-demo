#ifndef GRAPH_UTILS
#define GRAPH_UTILS

#include <stdint.h>
#include <stdio.h>

// creates a 32-bit int with 4 color keys (RGBA). Used in the framebuffer
uint32_t packColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

// renders a rect in the framebuffer
void renderRect(uint32_t *buffer, size_t bufX, size_t bufY, size_t posX,
		size_t posY, size_t sizeX, size_t sizeY, uint32_t color);

#endif
