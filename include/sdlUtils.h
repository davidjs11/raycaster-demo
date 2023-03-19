#ifndef SDL_UTILS
#define SDL_UTILS

#define KEY_QUIT 0
#define KEY_W 1
#define KEY_S 2
#define KEY_A 3
#define KEY_D 4
#define KEY_M 5

// init screen and renderer using SDL.
// returns -1 in case of error, and 0 if everything went ok
int initSDL(const char *name, SDL_Window **win, SDL_Renderer **rend,
	     size_t screenWidth, size_t screenHeight);

// sets SDL color. It uses RGBA codification in a 32 bits long int
void setColor(SDL_Renderer *rend, uint32_t color);

// process an input array
void processInput(SDL_Event *event, uint8_t *input);

// render the frame buffer
void renderBuffer(SDL_Renderer *rend, uint32_t *buffer,
	    size_t winX, size_t winY);

#endif
