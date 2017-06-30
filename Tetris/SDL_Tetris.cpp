#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "Game.h"

extern SDL_Renderer* renderer;

int main(int argc, char* args[] )
{
	// game initializing
	Game game;

	// event holder
	SDL_Event e;

	// main loop
	while( !game.getQuit() )
	{
		// event loop
		while( SDL_PollEvent( &e ) != 0 )
		{
			game.eventHandler( e );
		}// end of event loop

		// render screen
		game.render();
	}// end of main loop

	return 0;
}
