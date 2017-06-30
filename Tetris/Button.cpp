#include "Button.h"

Button::Button() : TextTexture()
{
	button.x = 0;
	button.y = 0;
	button.w = 0;
	button.h = 0;

	pressed = false;
}

Button::~Button()
{
}

int Button::getWidth()
{
	return button.w;
}

int Button::getHeight()
{
	return button.h;
}

void Button::render( SDL_Renderer*& renderer, int x, int y )
{
	// Set draw color to gray
	SDL_SetRenderDrawColor( renderer, 0x69, 0x69, 0x69, 0xFF );

	// Set render coordinates
	button.x = x;
	button.y = y;

	// Draw button outline
	SDL_RenderDrawRect( renderer, &button );

	// Render button text
	if( pressed )
		TextTexture::render( renderer, x + ( BUTTON_PADDING / 2 ) + ( BUTTON_PADDING / 4 ),
									   y + ( BUTTON_PADDING / 2 ) + ( BUTTON_PADDING / 4 ) );
	else
		TextTexture::render( renderer, x + ( BUTTON_PADDING / 2 ),
									   y + ( BUTTON_PADDING / 2 ) );
}

void Button::remake( SDL_Renderer*& renderer, const char* text, TTF_Font*& font )
{
	// Remake the texture
	TextTexture::remake( renderer, text, font );

	// Set button to be 10px bigger
	button.w = TextTexture::getWidth() + BUTTON_PADDING;
	button.h = TextTexture::getHeight() + BUTTON_PADDING;
}

bool Button::isIn( int x, int y )
{
	if( x < button.x || x > ( button.x + button.w ) )
		return false;
	else if( y < button.y || y > ( button.y + button.h ) )
		return false;

	return true;
}

void Button::press()
{
	pressed = true;
}

void Button::release()
{
	pressed = false;
}

bool Button::isPressed()
{
	return pressed;
}
