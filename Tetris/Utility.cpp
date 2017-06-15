#include "Utility.h"

bool init( SDL_Window*& pWindow, SDL_Renderer*& pRenderer, const int ciScreenWidth, const int ciScreenHeight )
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "Couldn't initialize SDL. Error:\n%s", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		pWindow = SDL_CreateWindow( "Tetris by Mitko", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ciScreenWidth, ciScreenHeight, SDL_WINDOW_SHOWN );
		if( pWindow == NULL )
		{
			printf( "Couldn't create window. Error:\n%s", SDL_GetError() );
			success = false;
		}
		else
		{
			pRenderer = SDL_CreateRenderer( pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( pRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else if( TTF_Init() == -1 )
			{
				printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
				success = false;
			}
		}
	}

	return success;
}

bool loadMedia( TTF_Font*& font )
{
	bool success = true;

	font = TTF_OpenFont( FONT, FONT_SIZE );
	if( font == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	return success;
}

void close( SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* text1, SDL_Texture* text2 )
{
	TTF_CloseFont( font );
	SDL_DestroyTexture( text1 );
	SDL_DestroyTexture( text2 );
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;
	font = NULL;
	text1 = NULL;
	text2 = NULL;

	TTF_Quit();
	SDL_Quit();
}
