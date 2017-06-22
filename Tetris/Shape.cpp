#include "Shape.h"

Shape::Shape()
{
}

Shape::Shape( Type type )
{
	// Initialize shape with type at top of the game matrix
	init( type );
}

Shape::~Shape()
{
}

Shape::Type Shape::getType()
{
	return type;
}

void Shape::render( SDL_Renderer*& renderer, bool drop )
{
	// Don't render if shape is NONE
	if( type == NONE )
		return;

	// If we want the shape to drop
	if( drop )
		// Drop shape by one block
		y += BLOCK_LENGTH;

	// Decide on color to draw with
	decideColor( renderer );

	// Go over the 4x4 rotation map and through it, read the coordinates of the shape in proper order to simulate the rotation
	for( int rY = 0; rY < SHAPE_MATRIX_LENGTH; rY++ )
		for( int rX = 0; rX < SHAPE_MATRIX_LENGTH; rX++ )
		{
			// Get info on current element of the shape matrix
			char temp = SHAPES[ type ][ ROTATION[ rRotation ][ rY ][ rX ].x ][ ROTATION[ rRotation ][ rY ][ rX ].y ];

			// If it's part of the shape
			if( temp != '0' )
			{
				// Make a rectangle on it's position in a way that it'll fit 1px within the block
				SDL_Rect rect;
				rect.x = x + rX * BLOCK_LENGTH + 1;
				rect.y = y + rY * BLOCK_LENGTH + 1;
				rect.w = BLOCK_LENGTH - 2;
				rect.h = BLOCK_LENGTH - 2;

				// Fill the rectangle
				SDL_RenderFillRect( renderer, &rect );
			}
		}
}

void Shape::renderShadow( SDL_Renderer*& renderer )
{
	// Don't render if shape is NONE
	if( type == NONE )
		return;

	// Decide on color to draw with
	decideColor( renderer );

	// Go over the 4x4 rotation map and through it, read the coordinates of the shape in proper order to simulate the rotation
	for( int rY = 0; rY < SHAPE_MATRIX_LENGTH; rY++ )
		for( int rX = 0; rX < SHAPE_MATRIX_LENGTH; rX++ )
		{
			// Get info on current element of the shape matrix
			char temp = SHAPES[ type ][ ROTATION[ rRotation ][ rY ][ rX ].x ][ ROTATION[ rRotation ][ rY ][ rX ].y ];

			// If it's part of the shape
			if( temp != '0' )
			{
				// Make a rectangle on it's position in a way that it'll fit 1px within the block
				SDL_Rect rect;
				rect.x = x + rX * BLOCK_LENGTH + 1;
				rect.y = y + rY * BLOCK_LENGTH + 1;
				rect.w = BLOCK_LENGTH - 2;
				rect.h = BLOCK_LENGTH - 2;

				// Draw rectangle outline
				SDL_RenderDrawRect( renderer, &rect );
			}
		}
}

void Shape::move( char direction )
{
	// If we want to move left
	if( direction == LEFT )
		// Move one block left
		x -= BLOCK_LENGTH;

	// If you want to move right
	else if( direction == RIGHT )
		// Move one block right
		x += BLOCK_LENGTH;

	// If you want to move down
	else if( direction == DOWN )
		// Move one block down
		y += BLOCK_LENGTH;

	// If you want to move up
	else if( direction == UP )
		// Move one block up
		y -= BLOCK_LENGTH;
}

void Shape::reset( Shape::Type newType, int newX, int newY )
{
	// Initialize shape with type at top of the game matrix
	init( newType );

	// If we've given both coordinates
	if( !( newX == -999 ) || !( newY == -999 ) )
	{
		// Set them as position of the shape
		this->x = newX;
		this->y = newY;
	}
}

int Shape::getX()
{
	return x;
}

int Shape::getY()
{
	return y;
}

bool Shape::isBlock( int x, int y )
{
	// In the 4x4 shape matrix, if, in accordance with the current rotation, the block is part of the shape
	if( SHAPES[ type ][ ROTATION[ rRotation ][ y ][ x ].x ][ ROTATION[ rRotation ][ y ][ x ].y ] == '1' )
		return true;

	return false;
}

void Shape::turn()
{
	// Move to next rotation
	iRotation++;

	// Handle looping back to the original rotation
	iRotation %= 4;

	// Save new chosen rotation
	rRotation = static_cast<Shape::Rotation> ( iRotation );
}

void Shape::init( Shape::Type newType )
{
	// Set new type
	type = newType;

	// Set starting location on top of the game matrix
	x = GAME_MATRIX_UPPERLEFT_X + ( GAME_MATRIX_WIDTH / 2 - 2 ) * BLOCK_LENGTH;
	y = GAME_MATRIX_UPPERLEFT_Y - 2 * BLOCK_LENGTH;

	// Set default rotation
	iRotation = 0;
	rRotation = static_cast<Shape::Rotation> ( iRotation );
}

void Shape::decideColor( SDL_Renderer*& renderer )
{
	switch( type )
	{
	case I:
		// Teal
		SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0xFF, 0xFF );
		break;
	case J:
		// Blue
		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
		break;
	case L:
		// Orange
		SDL_SetRenderDrawColor( renderer, 0xFF, 0x8C, 0x00, 0xFF );
		break;
	case O:
		// Yellow
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );
		break;
	case S:
		// Green
		SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
		break;
	case T:
		// Purple
		SDL_SetRenderDrawColor( renderer, 0x8B, 0x00, 0x8B, 0xFF );
		break;
	case Z:
		// Red
		SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
		break;
	}
}







