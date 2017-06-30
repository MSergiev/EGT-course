#include "Shape.h"

Shape::Shape( SDL_Renderer* renderer, Type type ) : mRenderer(renderer), mBlockDraw(Block(renderer))
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

void Shape::setRotation(Uint8 rotation){
	muiRotation = rotation%4;
}

Uint8 Shape::getRotation() const {
	return muiRotation;
}

void Shape::setRenderer(SDL_Renderer* renderer){
	mRenderer = renderer;
	mBlockDraw.setRenderer(renderer);
}

pair Shape::getCoords(int rawX, int rawY){
	pair coords;
	switch(muiRotation){
		// 0 deg
		case 0:
			coords.x = x+rawX*BLOCK_LENGTH+1;
			coords.y = y+rawY*BLOCK_LENGTH+1;
			break;
		// 90 deg
		case 1:
			coords.x = x+(SHAPE_MATRIX_LENGTH-rawY-1)*(BLOCK_LENGTH)+1;
			coords.y = y+rawX*BLOCK_LENGTH+1;
			break;
		// 180 deg
		case 2:
			coords.x = x+(SHAPE_MATRIX_LENGTH-rawX-1)*BLOCK_LENGTH+1;
			coords.y = y+(SHAPE_MATRIX_LENGTH-rawY-1)*BLOCK_LENGTH+1;
			break;
		// 270 deg
		default:
			coords.x = x+rawY*BLOCK_LENGTH+1;
			coords.y = y+(SHAPE_MATRIX_LENGTH-rawX-1)*BLOCK_LENGTH+1;
	}
	return coords;
}

void Shape::render( bool drop )
{
	// Don't render if shape is NONE
	if( type == NONE ) return;

	// If we want the shape to drop
	if( drop )
		// Drop shape by one block
		y += BLOCK_LENGTH;

	// Decide on color to draw with
	SDL_Color color = decideColor();

	// Drawing coordinates
	pair rotated;

	// Cycle through shape array
	for( int rY = 0; rY < SHAPE_MATRIX_LENGTH; ++rY ) {
		for( int rX = 0; rX < SHAPE_MATRIX_LENGTH; ++rX ) {
			// Check for block existance
			if(SHAPES[type][rY][rX]){
				// Calculate coordinates
				rotated = getCoords(rX, rY);
				// Draw block
				mBlockDraw.render(rotated.x, rotated.y, color);
			}
		}
	}

/*   DEPRECATED
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
				//SDL_RenderDrawRect( renderer, &rect );
				mBlockDraw.render(x+rX*BLOCK_LENGTH+1, y+rY*BLOCK_LENGTH+1, color);
			}
		}
		*/
}

void Shape::renderShadow()
{
	// Don't render if shape is NONE
	if( type == NONE )
		return;

	// Decide on color to draw with
	SDL_Color color = decideColor();
	color.a = 64;
	//SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, 64);

	// Drawing coordinates
	pair rotated;

	// Cycle through shape array
	for( int rY = 0; rY < SHAPE_MATRIX_LENGTH; ++rY ) {
		for( int rX = 0; rX < SHAPE_MATRIX_LENGTH; ++rX ) {
			// Check for block existance
			if(SHAPES[type][rY][rX]){
				// Calculate coordinates
				rotated = getCoords(rX, rY);
				// Draw block
				mBlockDraw.render(rotated.x, rotated.y, color);
			}
		}
	}	
	
/* DEPRECATED
	// Go over the 4x4 rotation map and through it, read the coordinates of the shape in proper order to simulate the rotation
	for( int rY = 0; rY < SHAPE_MATRIX_LENGTH; rY++ )
		for( int rX = 0; rX < SHAPE_MATRIX_LENGTH; rX++ )
		{
			// Get info on current element of the shape matrix
			bool temp = SHAPES[ type ][ ROTATION[ rRotation ][ rY ][ rX ].x ][ ROTATION[ rRotation ][ rY ][ rX ].y ];

			// If it's part of the shape
			if( temp )
			{
				// Make a rectangle on it's position in a way that it'll fit 1px within the block
				SDL_Rect rect;
				rect.x = x + rX * BLOCK_LENGTH + 1;
				rect.y = y + rY * BLOCK_LENGTH + 1;
				rect.w = BLOCK_LENGTH - 2;
				rect.h = BLOCK_LENGTH - 2;

				// Draw rectangle outline
				//mBlockDraw.render(x+rX*BLOCK_LENGTH+1, y+rY*BLOCK_LENGTH+1, color);
				SDL_RenderFillRect( mRenderer, &rect );
			}
		}
		*/
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
	if(  newX != -999 && newY != -999 )
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
//	if( SHAPES[ type ][ ROTATION[ rRotation ][ y ][ x ].x ][ ROTATION[ rRotation ][ y ][ x ].y ] )
	pair coords = getCoords(x,y);
	if( SHAPES[type][coords.y][coords.x])	return true;
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
	muiRotation = 0;

	//iRotation = 0;
	//rRotation = static_cast<Shape::Rotation> ( iRotation );
}

SDL_Color Shape::decideColor()
{
	SDL_Color color;
	switch( type )
	{
	case I:
		// Teal
		color = {0,255,255,255};
		//SDL_SetRenderDrawColor( mRenderer, 0x00, 0xFF, 0xFF, 0xFF );
		break;
	case J:
		// Blue
		color = {0,0,255,255};
		//SDL_SetRenderDrawColor( mRenderer, 0x00, 0x00, 0xFF, 0xFF );
		break;
	case L:
		// Orange
		color = {255,128,0,255};
		//SDL_SetRenderDrawColor( mRenderer, 0xFF, 0x8C, 0x00, 0xFF );
		break;
	case O:
		// Yellow
		color = {255,255,0,255};
		//SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0x00, 0xFF );
		break;
	case S:
		// Green
		color = {0,255,0,255};
		//SDL_SetRenderDrawColor( mRenderer, 0x00, 0xFF, 0x00, 0xFF );
		break;
	case T:
		// Purple
		color = {128,0,128,255};
		//SDL_SetRenderDrawColor( mRenderer, 0x8B, 0x00, 0x8B, 0xFF );
		break;
	case Z:
		// Red
		color = {255,0,0,255};
		//SDL_SetRenderDrawColor( mRenderer, 0xFF, 0x00, 0x00, 0xFF );
		break;
	case NONE:
		color = {0,0,0,255};
		break;
	}
	return color;
}
