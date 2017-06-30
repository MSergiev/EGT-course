#ifndef UTILITY_H_
#define UTILITY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using std::cerr;
using std::endl;

#include "Constants.h"

// Initialize SDL and it's subsystems and make window and it's renderer
bool init( SDL_Window*&, SDL_Renderer*& );

// Load media associated with the application
bool loadFont( TTF_Font*& );

// Destroy window, renderer and font and quit SDL and it's subsystems
void close( SDL_Window*&, SDL_Renderer*&, TTF_Font*& );

#endif /* UTILITY_H_ */
