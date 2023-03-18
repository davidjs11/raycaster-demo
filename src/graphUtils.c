#include "graphUtils.h"

uint32_t packColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return (a << 24) + (b << 16) + (g << 8) + (r << 0);
}
