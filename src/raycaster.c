#include <stdio.h>
#include <SDL2/SDL.h>
#include "graphUtils.h"
#include "sdlUtils.h"

int main(void)
{
    const size_t screenX = 720;
    const size_t screenY = 720;

    uint32_t framebuffer[screenX*screenY];

    SDL_Window *win;
    SDL_Renderer *rend;
    initSDL("raycaster", &win, &rend, screenX, screenY);

    SDL_Event event;
    uint8_t running = 1;

    while (running)
    {
	// input
	while (SDL_PollEvent(&event))
	{
	    if (event.type == SDL_QUIT)
		running = 0;
	}

	// process image
	for (int i=0; i<screenX; i++)
	    for (int j=0; j<screenY; j++)
		framebuffer[i+j*screenX] = packColor(
				    (i*255)/screenX,
				    (j*255)/screenY,
				    0, 0);

	// render the framebuffer
	for (int i=0; i<screenX; i++)
	    for (int j=0; j<screenY; j++)
	    {
		setColor(rend, framebuffer[i+j*screenX]);
		SDL_RenderDrawPoint(rend, i, j);
	    }


	SDL_RenderPresent(rend);
    }

}
