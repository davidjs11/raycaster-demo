#include <SDL2/SDL.h>
#include "sdlUtils.h"

int initSDL(const char *name, SDL_Window **win, SDL_Renderer **rend,
	    size_t screenWidth, size_t screenHeight)
{
    int tmp;
    tmp = SDL_Init(SDL_INIT_VIDEO);
    if (tmp < 0)
	return -1;

    *win = SDL_CreateWindow(name,
	    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	    screenWidth, screenHeight, 0);
    if (*win == NULL)
	return -1;

    *rend = SDL_CreateRenderer(*win, SDL_RENDERER_ACCELERATED, 0);
    if (*rend == NULL)
	return -1;

    return 0;
}

void setColor(SDL_Renderer *rend, uint32_t color)
{
    SDL_SetRenderDrawColor(rend,
	    (color >> 0)  & 255,
	    (color >> 8)  & 255,
	    (color >> 16) & 255,
	    (color >> 24) & 255);
}
