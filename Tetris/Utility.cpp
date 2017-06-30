#include "Utility.h"

bool init( SDL_Window*& window, SDL_Renderer*& renderer )
{
	// End result
	bool result = true;

	// Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cerr << "Couldn't initialize SDL. Error: " << SDL_GetError() << endl;
		result = false;
	}
	else
	{
		// Set scaling technique
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
			cerr << "Warning: Linear texture filtering not enabled!" << endl;

		// Create window
		window = SDL_CreateWindow( "Tetris by Mitko", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			cerr << "Couldn't create window. Error: " << SDL_GetError() << endl;
			result = false;
		}
		else
		{
			// Create renderer
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer == NULL )
			{
				cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				result = false;
			}
			// Initialize TTF
			else if( TTF_Init() == -1 )
			{
				cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
				result = false;
			// Initialize SDL_Image
			} else if(!IMG_Init(IMG_INIT_PNG)){
				cerr << "SDL_image error: " << IMG_GetError() << endl;
				result = false;
			}
		}
	}

	return result;
}

bool loadFont( TTF_Font*& font )
{
	// End result
	bool result = true;

	// Load font
	font = TTF_OpenFont( FONT, FONT_SIZE );
	if( font == NULL )
	{
		cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
		result = false;
	}

	return result;
}

void close( SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font*& font )
{
	// Destroy all the things
	TTF_CloseFont( font );
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );

	// Null them
	window = NULL;
	renderer = NULL;
	font = NULL;

	// Quit out of all SDL subsystems
	TTF_Quit();
	SDL_Quit();
}
