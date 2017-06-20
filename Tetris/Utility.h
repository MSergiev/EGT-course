#ifndef UTILITY_H_
#define UTILITY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include "Constants.h"

bool init( SDL_Window*&, SDL_Renderer*&, const int, const int );
bool loadMedia( TTF_Font*& );
void close( SDL_Window*, SDL_Renderer*, TTF_Font* );

#endif /* UTILITY_H_ */
