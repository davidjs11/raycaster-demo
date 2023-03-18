#include <stdio.h>
#include <math.h>
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
    float playerX = 3.1415;
    float playerY = 2.7182;
    float playerAngle = 0;
    float viewAngle = 0;
    float castX = 0, castY = 0;
    float fov = M_PI/3.0; // 60º

    uint8_t running = 1;
    while (running)
    {
	// input
	while (SDL_PollEvent(&event))
	{
	    if (event.type == SDL_QUIT)
		running = 0;

	    if (event.type == SDL_KEYDOWN)
	    {
		if (event.key.keysym.sym == SDLK_w)
		{
		    playerX += 0.1*cos(playerAngle);
		    playerY += 0.1*sin(playerAngle);
		}
		if (event.key.keysym.sym == SDLK_s)
		{
		    playerX += 0.1*cos(3.141592+playerAngle);
		    playerY += 0.1*sin(3.151592+playerAngle);
		}
		if (event.key.keysym.sym == SDLK_a)
		    playerAngle-=0.1;
		if (event.key.keysym.sym == SDLK_d)
		    playerAngle+=0.1;
	    }
	}

	// render background
	renderRect(framebuffer, winX, winY, 0, 0, winX, winY, 0x00000000);

	viewAngle = playerAngle;
	
	// render the map 
	if (renderMap)
	{
	    // render rects
	    for (int i=0; i<mapX; i++)
		for (int j=0; j<mapY; j++)
		    if (map[j*mapX+i] != ' ')
			renderRect(framebuffer, winX, winY, i*boxX, j*boxY,
			    boxX, boxY, 0x00FFFFFF);   

	    // render player
	    renderRect(framebuffer, winX, winY, playerX*boxX, playerY*boxY,
			    5, 5, 0x00FFFFFF);
	}

	// cast winX rays from playerAngle-fov/2 to playerAngle+fov/2
	// by increasing fov*(winX/winX)=fov
	for (int i=0; i<winX; i++)
	{
	    float distance = 0;
	    viewAngle = playerAngle-fov/2 + fov*i/winX;
	    for (float i=0; i<16; i+=0.05)
	    {
		castX = playerX + i*cos(viewAngle);
		castY = playerY + i*sin(viewAngle);
		if (map[(int)castX + (int)castY*mapX] != ' ') break;

		int pX = castX * boxX;
		int pY = castY * boxY;
		framebuffer[pX + pY*winY] = 0x000000FF; 
		distance+=0.05;
	    }
	    printf("distance: %f\n", distance);
	}


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
