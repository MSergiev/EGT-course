#ifndef TEXTTEXTURE_H_
#define TEXTTEXTURE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>

// Stores textures and it's dimensions
class TextTexture
{
public:
	// Empty constructor
	TextTexture();

	// Destroy texture
	virtual ~TextTexture();
public:
	// Returns texture width
	virtual int getWidth();

	// Returns texture height
	virtual int getHeight();

	// Render texture on given coordinates
	virtual void render( SDL_Renderer*&, int, int );

	// Generate texture from text and font
	virtual void remake( SDL_Renderer*&, const char*, TTF_Font*& );

	// Destroy texture
	void destroy();

private:
	// Texture
	SDL_Texture* pTexture;

	// Texture width
	int textureWidth;

	// Texture height
	int textureHeight;
};

#endif /* TEXTTEXTURE_H_ */
