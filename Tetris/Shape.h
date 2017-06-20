#ifndef SHAPE_H_
#define SHAPE_H_

#include <SDL2/SDL.h>

#include "Constants.h"

// Class for the shapes in the game
// 4x4 array with information on it's top-left coordinates and which of the blocks in the array are part of the shape
class Shape
{
public:
	// Enum for types of shapes
	enum Type { I, J, L, O, S, T, Z };

	// Enum for shape rotation
	enum Rotation { ROTATION_0, ROTATION_90, ROTATION_180, ROTATION_270 };
public:
	// Unused empty constructor
	Shape();

	// Initialize the shape at the top of the game matrix with type
	Shape( Type );

	// Empty destructor
	~Shape();
public:
	// Returns type of shape
	Shape::Type getType();

	// Renders shape with given SDL_Rederer and asks should it drop lower
	void render( SDL_Renderer*&, bool );

	// Renders shape as a shadow
	void renderShadow( SDL_Renderer*& );

	// Moves shape UP, DOWN, LEFT or RIGHT by one block
	void move( char );

	// Resets shape back on top of the game matrix with given type
	// Can take two additional arguments for a different reset position
	// ( if one is left at -999, it'll put shape on top of the game matrix )
	void reset( Shape::Type, int = -999, int = -999 );

	// Returns X coordinate of the shape
	int getX();

	// Returns Y coordinate of the shape
	int getY();

	// Returns true of the asked block in the 4x4 array is block from the shape
	bool isBlock( int, int );

	// Rotates the 4x4 array clockwise ( rotates shape 90 degrees clockwise )
	void turn();
private:
	// Sets type and starting position at top of the game matrix
	void init( Shape::Type );
private:
	// Type of the shape
	Type type;

	// X coordinate of the shape
	int x;

	// Y coordinate of the shape
	int y;

	// Integer form of rotation for iteration
	int iRotation;

	// Rotation of the shape
	Rotation rRotation;
};

#endif /* SHAPE_H_ */
