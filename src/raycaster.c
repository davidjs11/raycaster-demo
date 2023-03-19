#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "graphUtils.h"
#include "sdlUtils.h"
#include "gameUtils.h"

int main(void)
{
    // screen variables
    const size_t winX = 640;
    const size_t winY = 640;
    uint32_t framebuffer[winX * winY];

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
    SDL_Event event;
    uint8_t input[6] = {0};

    // game variables
    uint8_t viewMap = 0;
    struct entity player = {1, 1, 0, 0.1, 0.1};

    // rendering variables
    float viewAngle;
    float castX = 0, castY = 0;
    float fov = M_PI/3.0; // 60º

    // init the graphic engine
    initSDL("raycaster", &window, &rend, winX, winY);

    // game loop
    uint8_t running = 1;
    while (running)
    {
	// input
	processInput(&event, input);
	running = !(input[KEY_QUIT]);

	// controls
	moveEntity(&player, input[KEY_W], input[KEY_S]);
	rotateEntity(&player, input[KEY_A], input[KEY_D]);
	viewMap = input[KEY_M];					//map

	// render background
	clearBuffer(framebuffer, winX, winY, 0x00000000);

	viewAngle = player.angle;
	
	// render the map 
	if (viewMap)
	    renderMap(framebuffer, map, mapX, mapY, winX, winY, boxX, boxY);

	// cast rays and create the 3D view
	for (int i=0; i<winX; i++)
	{
	    // modify ray direction
	    viewAngle = player.angle-fov/2 + fov*i/winX;
	    for (float j=0; j<16; j+=0.025)
	    {
		// move the point to form the ray
		castX = player.posX + j*cos(viewAngle);
		castY = player.posY + j*sin(viewAngle);
		char wall = map[(int)castX + (int)castY*mapX];

		// set color
		if (wall == '1') color = 0x000000FF;
		else if (wall == '2') color = 0x0000FF00;
		else if (wall == '3') color = 0x00FF0000;

		// render map rays
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
