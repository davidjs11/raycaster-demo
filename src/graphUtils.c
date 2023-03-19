#include "graphUtils.h"

uint32_t packColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return (a << 24) + (b << 16) + (g << 8) + (r << 0);
}

void renderRect(uint32_t *buffer, size_t bufX, size_t bufY, size_t posX,
		size_t posY, size_t sizeX, size_t sizeY, uint32_t color)
{
    int pixel;
    size_t bufSize = bufX * bufY;

    for (int i=0; i<sizeX; i++)
	for(int j=0; j<sizeY; j++)
	{
	    pixel = (posY+j)*bufX + (posX+i);
	    if (pixel < bufSize)
		buffer[pixel] = color;
	}
}

void clearBuffer(uint32_t *buffer, size_t bufX, size_t bufY, uint32_t color)
{
    for (int i=0; i<bufX; i++)
	for (int j=0; j<bufY; j++)
	    buffer[i+j*bufX] = color;
}
