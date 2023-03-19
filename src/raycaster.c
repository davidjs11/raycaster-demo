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
    uint32_t color = 0x00000000;

    // sdl variables
    SDL_Window *window;
    SDL_Renderer *rend;
    initSDL("raycaster", &window, &rend, winX, winY);
    SDL_Event event;
    uint8_t input[6] = {0};

    // game variables
    uint8_t viewMap = 0;
    float playerX = 1;
    float playerY = 1;
    float playerAngle = 0;
    float viewAngle = 0;
    float castX = 0, castY = 0;
    float fov = M_PI/3.0; // 60º

    // game loop
    uint8_t running = 1;
    while (running)
    {
	// input
	processInput(&event, input);
	running = !(input[KEY_QUIT]);

	// controls
	playerX += 0.1*(cos(playerAngle)*input[KEY_W]		//position
			+ cos(M_PI+playerAngle)*input[KEY_S]);
	playerY += 0.1*(sin(playerAngle)*input[KEY_W]
			+ sin(M_PI+playerAngle)*input[KEY_S]);
	playerAngle += 0.1 * (input[KEY_D] - input[KEY_A]);	//angle
	viewMap = input[KEY_M];					//map

	// render background
	clearBuffer(framebuffer, winX, winY, 0x00000000);

	viewAngle = playerAngle;
	
	// render the map 
	if (viewMap)
	{
	    renderMap(framebuffer, map, mapX, mapY, winX, winY, boxX, boxY);

	    // render player
	    renderRect(framebuffer, winX, winY, playerX*boxX, playerY*boxY,
			    1, 1, 0x00FFFFFF);
	}

	// cast rays and create the 3D view
	for (int i=0; i<winX; i++)
	{
	    viewAngle = playerAngle-fov/2 + fov*i/winX;
	    for (float j=0; j<16; j+=0.01)
	    {
		castX = playerX + j*cos(viewAngle);
		castY = playerY + j*sin(viewAngle);
		char wall = map[(int)castX + (int)castY*mapX];

		// set color
		if (wall == '1') color = 0x000000FF;
		else if (wall == '2') color = 0x0000FF00;
		else if (wall == '3') color = 0x00FF0000;

		// render lines
		if (viewMap)
		{
		    int pX = castX * boxX;
		    int pY = castY * boxY;
		    if (wall != ' ') break;
		    framebuffer[pX + pY*winY] = 0x00FFFFFF; 
		}

		// render the line whose length will depend on how far the next
		// object is
		if (!viewMap && wall != ' ')
		{
		    size_t columnHeight = winY/j;

		    renderRect(framebuffer, winX, winY, i, winY/2-columnHeight/2,
			       1, columnHeight, color);
		    break;
		}
	    }
	}

	// render the buffer
	renderBuffer(rend, framebuffer, winX, winY);
    }

}
