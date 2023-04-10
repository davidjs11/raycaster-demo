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

void processInput(SDL_Event *event, uint8_t *input)
{
    while (SDL_PollEvent(event))
    {
	    if (event->type == SDL_QUIT)
	        input[KEY_QUIT] = 1;

	    if (event->type == SDL_KEYDOWN)
	        if (event->key.keysym.sym == SDLK_q)
		        input[KEY_QUIT] = 1;
	        else if (event->key.keysym.sym == SDLK_w)
		        input[KEY_W] = 1;
	        else if (event->key.keysym.sym == SDLK_a)
		        input[KEY_A] = 1;
	        else if (event->key.keysym.sym == SDLK_s)
		        input[KEY_S] = 1;
	        else if (event->key.keysym.sym == SDLK_d)
		        input[KEY_D] = 1;
	        else if (event->key.keysym.sym == SDLK_m)
		        input[KEY_M] = 1;

	    if (event->type == SDL_KEYUP)
	        if (event->key.keysym.sym == SDLK_q)
		        input[KEY_QUIT] = 0;
	        else if (event->key.keysym.sym == SDLK_w)
		        input[KEY_W] = 0;
	        else if (event->key.keysym.sym == SDLK_a)
		        input[KEY_A] = 0;
	        else if (event->key.keysym.sym == SDLK_s)
		        input[KEY_S] = 0;
	        else if (event->key.keysym.sym == SDLK_d)
		        input[KEY_D] = 0;
	        else if (event->key.keysym.sym == SDLK_m)
		        input[KEY_M] = 0;
    }
}

void renderBuffer(SDL_Renderer *rend, uint32_t *buffer, size_t winX, size_t winY)
{
    for (int i=0; i<winX; i++)
	    for (int j=0; j<winY; j++)
	    {
	        setColor(rend, buffer[i+j*winX]);
	        SDL_RenderDrawPoint(rend, i, j);
	    }
    SDL_RenderPresent(rend);
}
