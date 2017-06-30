#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "Utility.h"
#include "Constants.h"
#include "Shape.h"
#include "Matrix.h"
#include "TextTexture.h"
#include "Button.h"

//SDL_Renderer* renderer = NULL;

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
	void eventHandler( SDL_Event& );

	// Returns if the game's over
	bool getQuit() const;

	// Renders on everything on screen
	void render();
private:
	// Generate text textures
	void genText();

	// Generate score texture
	void updateScore();

	// Generates the next shape
	void genNextShape();

	// Renders the next shape
	void renderNextShape();

	// Renders held shape
	void renderHeldShape();

	// Renders the shadow
	void renderShadow();

	// Renders score
	void renderScore();

	// Render new game button
	void renderButtonRestart();

	// Render pause button
	void renderButtonPause();

	// Render exit button
	void renderButtonExit();

	// Release all buttons
	void releaseButtons();

	// Restart the game
	void restart();

	// Calculates should the shape drop this frame
	bool shouldDrop();

	// Calculates data about the frame
	bool processFrame();

	// Keyboard event handle
	void keyEvent( SDL_Event& );

	// Mouse click event handle
	void mouseEvent( SDL_Event& );

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

	// Action if Z is pressed
	void hold();


private:
	// Window and its renderer for the game
	SDL_Window* window;
	SDL_Renderer* renderer;

	// Text font
	TTF_Font* font;

	// Text
	TextTexture headerNext;
	TextTexture headerScore;
	TextTexture headerHeld;

	// Quit flag
	bool quit;

	// Pause flag
	bool isPaused;

	// Game matrix
	Matrix matrix;

	// Current shape, it's shadow, next shape and the held shape
	Shape shape;
	Shape shadowShape;
	Shape nextShape;
	Shape heldShape;

	// Delay counter to calculate on which frame should the shape drop
	int delay;

	// Score tracker
	int score;

	// Score texture
	TextTexture textureScore;

	// Buttons
	Button buttonRestart;
	Button buttonPause;
	Button buttonExit;
};

#endif /* GAME_H_ */
