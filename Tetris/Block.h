#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
using std::cerr;
using std::endl;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Constants.h"

class Block {
public:
	Block(SDL_Renderer* renderer=NULL);
	void setRenderer(SDL_Renderer* renderer);
	bool loadTexture();
	void render(int x, int y, SDL_Color& color);
	~Block();
private:
	SDL_Renderer* renderer;
	int mWidth, mHeight;
	SDL_Texture* mBlockTexture;
};

#endif
