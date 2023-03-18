#ifndef SDL_UTILS
#define SDL_UTILS

// init screen and renderer using SDL.
// returns -1 in case of error, and 0 if everything went ok
int initSDL(const char *name, SDL_Window **win, SDL_Renderer **rend,
	     size_t screenWidth, size_t screenHeight);

// sets SDL color. It uses RGBA codification in a 32 bits long int
void setColor(SDL_Renderer *rend, uint32_t color);

#endif
