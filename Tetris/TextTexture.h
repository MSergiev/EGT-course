#ifndef TEXTTEXTURE_H_
#define TEXTTEXTURE_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <cstdio>

// Stores textures and it's dimensions
class TextTexture
{
public:
	// Empty constructor
	TextTexture();

	// Destroy texture
	~TextTexture();
public:
	// Returns texture width
	int getWidth();

	// Returns texture height
	int getHeight();

	// Render texture on given coordinates
	void render( SDL_Renderer*&, int, int );

	// Generate texture from text and font
	void remake( SDL_Renderer*&, const char*, TTF_Font*& );

private:
	// Texture
	SDL_Texture* pTexture;

	// Texture width
	int textureWidth;

	// Texture height
	int textureHeight;
};

#endif /* TEXTTEXTURE_H_ */
