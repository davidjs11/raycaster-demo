#include <stdio.h>
#include <SDL2/SDL.h>
#include "graphUtils.h"
#include "sdlUtils.h"

int main(void)
{
    // screen variables
    const size_t winX = 512;
    const size_t winY = 512;
    uint32_t framebuffer[winX * winY];

    for (int i=0; i<winX*winY; i++)
	framebuffer[i] = 0x00000000;

    // map variables
    const size_t mapX = 16;
    const size_t mapY = 16;
    const size_t boxX = winX/mapX;
    const size_t boxY = winY/mapY;
    const char map[] = 
    	"0000000000000000"\
	"1  2           0"\
	"1  2      1111 0"\
	"1  2        1  0"\
	"1  2        1110"\
	"1  2          10"\
	"1  2           0"\
	"1  2333333333  0"\
	"1  2           0"\
	"1  2           0"\
	"1  2222 23333  0"\
	"1     2 2      0"\
	"1  2222 22222 30"\
	"1  2        2330"\
	"1           2  0"\
	"1111111111111111";

    // sdl variables
    SDL_Window *window;
    SDL_Renderer *rend;
    initSDL("raycaster", &window, &rend, winX, winY);
    SDL_Event event;


    // game variables
    uint8_t renderMap = 1;

    uint8_t running = 1;
    while (running)
    {
	// input
	while (SDL_PollEvent(&event))
	{
	    if (event.type == SDL_QUIT)
		running = 0;
	}

	// process framebuffer 
	if (renderMap)
	    for (int i=0; i<mapX; i++)
		for (int j=0; j<mapY; j++)
		    if (map[j*mapX+i] != ' ')
			renderRect(framebuffer, winX, winY, i*boxX, j*boxY,
			    boxX, boxY, 0x000000FF);
/*
	for (int i=0; i<mapX; i++)
	{
	    for (int j=0; j<mapY; j++)
		if (map[i+j*mapX] == 'e')
		printf("%c at (%d, %d)\n", map[i+j*mapX], i, j);
	}
*/
	// render framebuffer
	for (int i=0; i<winX; i++)
	    for (int j=0; j<winY; j++)
	    {
		setColor(rend, framebuffer[i+j*winX]);
		SDL_RenderDrawPoint(rend, i, j);
	    }

	SDL_RenderPresent(rend);
    }

}
