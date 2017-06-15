#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Utility.h"
#include "Constants.h"
#include "Matrix.h"
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>
#include "Shape.h"

// Class for the game Tetris
class Game
{
public:
	// Initializes SDL and game elements
	Game();

	// Quits SDL
	~Game();
public:
	// Handles events
	void eventHandler( SDL_Event );

	// Returns if the game's over
	bool getQuit() const;

	// Renders on everything on screen
	void render();
private:
	// Private copy constructor and operator = cause we don't want them to exist
	Game( const Game& );
	Game& operator=( const Game& );
private:
	// Generate text textures
	void genText( SDL_Texture*&, const char* );

	// Generate score texture
	void genScoreTexture();

	// Generates the next shape
	void genNextShape();

	// Renders the next shape
	void renderNextShape();

	// Renders the shadow
	void renderShadow();

	// Renders score
	void renderScore();

	// Calculates should the shape drop this frame
	bool shouldDrop();

	// Calculates data about the frame
	bool processFrame();

	// Action if UP is pressed
	void spin();

	// Action if DOWN is pressed
	void speedUp();

	// Action if LEFT is pressed
	void moveLeft();

	// Action if RIGHT is pressed
	void moveRight();

	// Action if SPACE is pressed
	void slam();


private:
	// Window and it's renderer for the game
	SDL_Window* window;
	SDL_Renderer* renderer;

	// Text font
	TTF_Font* font;

	// Text
	SDL_Texture* textNext;
	SDL_Texture* textScore;

	// Text dimensions ( to avoid stretching )
	int textNextWidth;
	int textNextHeight;

	int textScoreWidth;
	int textScoreHeight;

	// Quit flag
	bool quit;

	// Game matrix
	Matrix matrix;

	// Current shape, it's shadow and the next shape
	Shape shape;
	Shape nextShape;
	Shape shadow;

	// Delay counter to calculate on which frame should the shape drop
	int delay;

	// Score tracker
	int score;

	// Score texture
	SDL_Texture* scoreTexture;

	// Score texture dimensions
	int scoreTextureWidth;
	int scoreTextureHeight;
};

#endif /* GAME_H_ */
