#ifndef BUTTON_H_
#define BUTTON_H_

#include <SDL2/SDL.h>
#include "TextTexture.h"
#include "Constants.h"

// Class for text-based buttons
class Button: public TextTexture
{
public:
	Button();
	~Button();
public:
	// Returns button width
	int getWidth();

	// Returns button height
	int getHeight();

	// Render texture on given coordinates
	void render( SDL_Renderer*&, int, int );

	// Generate texture from text and font and wrap button around it
	void remake( SDL_Renderer*&, const char*, TTF_Font*& );

	// Are the coordinates in the button
	bool isIn( int, int );

	// Press the button
	void press();

	// Release the button
	void release();

	// Return true if button's pressed
	bool isPressed();
private:
	// Button border
	SDL_Rect button;

	// Is it pressed
	bool pressed;
};

#endif /* BUTTON_H_ */
