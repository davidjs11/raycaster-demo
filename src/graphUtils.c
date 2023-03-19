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

void renderMap(uint32_t *buffer, const char *map, size_t mapX, size_t mapY,
	       size_t winX, size_t winY, size_t boxX, size_t boxY)
{
    char wall;
    uint32_t color = 0x00000000;

    for (int i=0; i<mapX; i++)
	for (int j=0; j<mapY; j++)
	{
	    wall = map[i+j*mapX];
	    if (wall == ' ')
		color = 0x00000000; 
	    else if (wall == '0')
		color = 0x0000FFFF;
	    else if (wall == '1')
		color = 0x000000FF;
	    else if (wall == '2')
		color = 0x0000FF00;
	    else if (wall == '3')
		color = 0x00FF0000;

	    renderRect(buffer, winX, winY, i*boxX, j*boxY,
		    boxX, boxY, color);
	}
}
