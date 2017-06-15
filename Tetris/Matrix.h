#ifndef MATRIX_H_
#define MATRIX_H_

#include <SDL2/SDL.h>
#include "Constants.h"
#include "Shape.h"

// Class for game matrix
class Matrix
{
public:
	// Initialize matrix as empty
	Matrix();
	// Empty destructor
	~Matrix();
public:
	// Render the game matrix on screen
	void render( SDL_Renderer*& );

	// Check if a shape has a neighbor or border on the LEFT, DOWN or RIGHT
	bool isOn( Shape&, char );

	// Check if a shape is glitching through a wall LEFT RIGHT or DOWN
	bool isGlitchWall( Shape&, char );

	// Check if shape is glitching through another shape
	bool isGlitch( Shape& );

	// Add a shape to the game matrix
	void assimilate( Shape& );

	// Check for full lines, remove them and returns how many were removed
	int pop();

	// Check for full lines and white them out
	void blink();

	// Check if the matrix has reached the top (if you lost)
	bool lose();
private:
	// Returns a char responding to a shape type for color recognition by the game matrix renderer
	char color( Shape::Type );
private:
	// Game matrix
	char data[ GAME_MATRIX_WIDTH ][ GAME_MATRIX_HEIGHT ];
};

#endif /* MATRIX_H_ */
