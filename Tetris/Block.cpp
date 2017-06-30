#include "Block.h"

Block::Block(SDL_Renderer* renderer){
	this->renderer=renderer;
}

// Render a block
// renderer = SDL renderer
// x = x top left coordinate
// y = y top left coordinate
void Block::render(int x, int y, SDL_Color& color){
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 255,255,255,255);
	SDL_Rect renderQuad = {x,y,BLOCK_LENGTH-2,BLOCK_LENGTH-2};
	SDL_SetTextureColorMod(mBlockTexture, color.r, color.g, color.b);
	//SDL_RenderFillRect(renderer, &renderQuad);
	SDL_RenderCopy(renderer, mBlockTexture, NULL, &renderQuad);
}

// Free resources
Block::~Block(){
	SDL_DestroyTexture(mBlockTexture);
}

// Renderer setter
void Block::setRenderer(SDL_Renderer* renderer){
	this->renderer=renderer;
	loadTexture();
}

// Load block texture from file
bool Block::loadTexture(){
	bool success = 1;
	SDL_Texture* tex = NULL;
	SDL_Surface* loaded = IMG_Load("block.png");
	if(loaded==NULL){
		cerr << "Image error" << endl;
		success =  0;
	} else {
		tex = SDL_CreateTextureFromSurface(renderer, loaded);
		mWidth = loaded->w;
		mHeight = loaded->h;
	}
	SDL_FreeSurface(loaded);
	mBlockTexture = tex;
	success = (mBlockTexture!=NULL);
	return success;
}
