#include "TextTexture.h"

TextTexture::TextTexture()
{
	pTexture = NULL;
	textureWidth = 0;
	textureHeight = 0;
}

TextTexture::~TextTexture()
{
	destroy();
}

int TextTexture::getWidth()
{
	return textureWidth;
}

int TextTexture::getHeight()
{
	return textureHeight;
}

void TextTexture::render( SDL_Renderer*& renderer, int x, int y )
{
	// Set up rectangle to print text within the block
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = textureWidth;
	rect.h = textureHeight;

	// Set color to white
	SDL_SetRenderDrawColor( renderer, 255,255,255,255 );

	// Render text
	SDL_RenderCopy(renderer, pTexture, NULL, &rect);
}

void TextTexture::remake( SDL_Renderer*& renderer, const char* text, TTF_Font*& font )
{
	// Destroy current texture
	destroy();

	// Make surfaces to get rendered text
	SDL_Surface* tempSurface = TTF_RenderText_Solid( font, text, SDL_Color{ 255,255,255,255 } );

	// Get dimensions of the generated text
	textureWidth = tempSurface->w;
	textureHeight = tempSurface->h;

	// Make texture from the surface
	pTexture = SDL_CreateTextureFromSurface( renderer, tempSurface );

	// If failed
	if( pTexture == NULL )
	{
		cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;

		textureWidth = 0;
		textureHeight = 0;
	}

	// Free all used surfaces
	SDL_FreeSurface( tempSurface );
	tempSurface = NULL;
}

void TextTexture::destroy()
{
	SDL_DestroyTexture( pTexture );
	pTexture = NULL;

	textureWidth = 0;
	textureHeight = 0;
}
