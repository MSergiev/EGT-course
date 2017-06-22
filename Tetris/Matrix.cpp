#include "Matrix.h"

Matrix::Matrix()
{
	// Each element in the game matrix
	for( int x = 0; x < GAME_MATRIX_WIDTH; x++ )
		for( int y = 0; y < GAME_MATRIX_HEIGHT; y++ )
			// Set it to empty
			data[ x ][ y ] = '0';
}

Matrix::~Matrix()
{
}

void Matrix::render( SDL_Renderer*& pRenderer )
{
	// Make a rectangle with a size of a block
	SDL_Rect rect;
	rect.w = BLOCK_LENGTH;
	rect.h = BLOCK_LENGTH;

	// For each element in the game matrix
	for( int curX = 0; curX < GAME_MATRIX_WIDTH; curX++ )
		for( int curY = 0; curY < GAME_MATRIX_HEIGHT; curY++ )
		{
			// Set rectangle position to according position of the current element of the game matrix
			rect.x = GAME_MATRIX_UPPERLEFT_X + curX * BLOCK_LENGTH;
			rect.y = GAME_MATRIX_UPPERLEFT_Y + curY * BLOCK_LENGTH;

			// Fill a rectangle of an appropriate color based on the game matrix
			switch( data[ curX ][ curY ] )
			{
			case '1':
				// White
				SDL_SetRenderDrawColor( pRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderFillRect( pRenderer, &rect );
				break;
			case 'I':
				// Teal
				SDL_SetRenderDrawColor( pRenderer, 0x00, 0xFF, 0xFF, 0xFF );
				SDL_RenderFillRect( pRenderer, &rect );
				break;
			case 'J':
				// Blue
				SDL_SetRenderDrawColor( pRenderer, 0x00, 0x00, 0xFF, 0xFF );
				SDL_RenderFillRect( pRenderer, &rect );
				break;
			case 'L':
				// Orange
				SDL_SetRenderDrawColor( pRenderer, 0xFF, 0x8C, 0x00, 0xFF );
				SDL_RenderFillRect( pRenderer, &rect );
				break;
			case 'O':
				// Yellow
				SDL_SetRenderDrawColor( pRenderer, 0xFF, 0xFF, 0x00, 0xFF );
				SDL_RenderFillRect( pRenderer, &rect );
				break;
			case 'S':
				// Green
				SDL_SetRenderDrawColor( pRenderer, 0x00, 0xFF, 0x00, 0xFF );
				SDL_RenderFillRect( pRenderer, &rect );
				break;
			case 'T':
				// Purple
				SDL_SetRenderDrawColor( pRenderer, 0x8B, 0x00, 0x8B, 0xFF );
				SDL_RenderFillRect( pRenderer, &rect );
				break;
			case 'Z':
				// Red
				SDL_SetRenderDrawColor( pRenderer, 0xFF, 0x00, 0x00, 0xFF );
				SDL_RenderFillRect( pRenderer, &rect );
				break;
			}

			// Draw a black outline
			SDL_SetRenderDrawColor( pRenderer, 0x00, 0x00, 0x00, 0xFF );
			SDL_RenderDrawRect( pRenderer, &rect );
		}

	// Set rectangle to cover the whole game matrix
	rect.x = GAME_MATRIX_UPPERLEFT_X;
	rect.y = GAME_MATRIX_UPPERLEFT_Y;
	rect.w = GAME_MATRIX_WIDTH * BLOCK_LENGTH;
	rect.h = GAME_MATRIX_HEIGHT * BLOCK_LENGTH;

	// Draw a gray outline
	SDL_SetRenderDrawColor( pRenderer, 0x69, 0x69, 0x69, 0xFF );
	SDL_RenderDrawRect( pRenderer, &rect );
}

bool Matrix::isOn( Shape& shape, char direction )
{
	// For each block of the shape matrix
	for( int y = 0; y < SHAPE_MATRIX_LENGTH; y++ )
		for( int x = 0; x < SHAPE_MATRIX_LENGTH; x++ )
			// If the block is part of the shape
			if( shape.isBlock( x, y ) )
			{
				// Calculate current block's location in the game matrix
				int tempX = ( shape.getX() - GAME_MATRIX_UPPERLEFT_X ) / BLOCK_LENGTH + x;
				int tempY = ( shape.getY() - GAME_MATRIX_UPPERLEFT_Y ) / BLOCK_LENGTH + y;

				// If we're checking for something under the shape
				if( direction == DOWN )
				{
					// If block is on the bottom of the game matrix or the block under is not empty
					if( tempY == GAME_MATRIX_HEIGHT - 1 || data[ tempX ][ tempY + 1 ] != '0' )
						return true;
				}

				// If we're checking for something on the left of the shape
				else if( direction == LEFT )
				{
					// If the block is leftmost on the game matrix or the block on the left is not empty
					if( tempX == 0 || data[ tempX - 1 ][ tempY ] != '0' )
						return true;
				}

				// If we're checking for something on the right of the shape
				else if( direction == RIGHT )
				{
					// If the block is rightmost on the game matrix or the block on the right is not empty
					if( tempX == GAME_MATRIX_WIDTH - 1 || data[ tempX + 1 ][ tempY ]  != '0' )
						return true;
				}
			}

	return false;
}

bool Matrix::isGlitchWall( Shape& shape, char direction )
{
	// For each block of the shape matrix
	for( int y = 0; y < SHAPE_MATRIX_LENGTH; y++ )
		for( int x = 0; x < SHAPE_MATRIX_LENGTH; x++ )
			// If the block is part of the shape
			if( shape.isBlock( x, y ) )
			{
				// If we want to check for glitching through the left wall
				if( direction == LEFT )
				{
					// If the block is outside the game matrix
					if( shape.getX() + x * BLOCK_LENGTH - GAME_MATRIX_UPPERLEFT_X < 0 )
						return true;
				}

				// If we want to check for glitching through the right wall
				else if( direction == RIGHT )
				{
					// If the block is outside the game matrix
					if( shape.getX() + x * BLOCK_LENGTH - GAME_MATRIX_UPPERLEFT_X - GAME_MATRIX_WIDTH * BLOCK_LENGTH >= 0 )
						return true;
				}

				// If we want to check for glitching through the bottom
				else if( direction ==  DOWN )
				{
					// If the block is outside the game matrix
					if( shape.getY() + y * BLOCK_LENGTH - GAME_MATRIX_UPPERLEFT_Y - GAME_MATRIX_HEIGHT * BLOCK_LENGTH >= 0 )
						return true;
				}
			}

	return false;
}

bool Matrix::isGlitch( Shape& shape )
{
	// For each block of the shape matrix
	for( int y = 0; y < SHAPE_MATRIX_LENGTH; y++ )
		for( int x = 0; x < SHAPE_MATRIX_LENGTH; x++ )
			// If the block is part of the shape
			if( shape.isBlock( x, y ) )
			{
				// Calculate it's place on the game matrix
				int tempX = ( shape.getX() - GAME_MATRIX_UPPERLEFT_X ) / BLOCK_LENGTH + x;
				int tempY = ( shape.getY() - GAME_MATRIX_UPPERLEFT_Y ) / BLOCK_LENGTH + y;
				// If the block is not empty
				if( data[ tempX ][ tempY ]  != '0' )
					return true;
			}

	return false;
}

void Matrix::assimilate( Shape& shape )
{
	// Get proper char to save in the game matrix so it recognizes the color of the shape when rendering
	char type = color( shape.getType() );

	// For each element in the game matrix
	for( int y = 0; y < SHAPE_MATRIX_LENGTH; y++ )
		for( int x = 0; x < SHAPE_MATRIX_LENGTH; x++ )
			// If the block is part of the shape
			if( shape.isBlock( x, y ) )
			{
				// Calculate it's position in the game matrix
				int tempX = ( shape.getX() - GAME_MATRIX_UPPERLEFT_X ) / BLOCK_LENGTH + x;
				int tempY = ( shape.getY() - GAME_MATRIX_UPPERLEFT_Y ) / BLOCK_LENGTH + y;

				// Set it's block in the game matrix to it's type
				data[ tempX ][ tempY ] = type;
			}
}

void Matrix::clear()
{
	// Each element in the game matrix
	for( int x = 0; x < GAME_MATRIX_WIDTH; x++ )
		for( int y = 0; y < GAME_MATRIX_HEIGHT; y++ )
			// Set it to empty
			data[ x ][ y ] = '0';
}

int Matrix::pop()
{
	int removed = 0;

	// For each line in the game matrix
	for( int y = GAME_MATRIX_HEIGHT - 1; y >= 0; y-- )
	{
		// Set a flag to indicate if the line is full
		bool fullLine = true;

		// For each block on the line
		for( int x = 0; x < GAME_MATRIX_WIDTH; x++ )
			// If the block is empty
			if( data[ x ][ y ] == '0' )
			{
				// Set flag to false cause line isn't full
				fullLine = false;
				break;
			}

		// If line is full
		if( fullLine )
		{
			// Increase removed counter
			removed++;

			// Replace each block with the value of the block above it ( squishing it )
			for( int tempX = 0; tempX < GAME_MATRIX_WIDTH; tempX++ )
				for( int tempY = y; tempY > 0; tempY-- )
					data[ tempX ][ tempY ] = data[ tempX ][ tempY - 1 ];

			// Add an empty line on top of the game matrix
			for( int tempX = 0; tempX < GAME_MATRIX_WIDTH; tempX++ )
				data[ tempX ][ 0 ] = '0';

			// Push the line iterator down in case the following line is also full ( it'll skip it otherwise )
			y++;
		}
	}

	return removed;
}

void Matrix::blink()
{
	// For each line in the game matrix
	for( int y = GAME_MATRIX_HEIGHT - 1; y >= 0; y-- )
	{
		// Set a flag to indicate if the line is full
		bool fullLine = true;

		// For each block on the line
		for( int x = 0; x < GAME_MATRIX_WIDTH; x++ )
			// If the block is empty
			if( data[ x ][ y ] == '0' )
			{
				// Set flag to false cause line isn't full
				fullLine = false;
				break;
			}

		// If line is full
		if( fullLine )
		{
			// Set all blocks in the line to be colored white
			for( int x = 0; x < GAME_MATRIX_WIDTH; x++ )
				data[ x ][ y ] = '1';
		}
	}
}

bool Matrix::lose()
{
	// For every block on the top line of the game matrix
	for( int x = 0; x < GAME_MATRIX_WIDTH; x++ )
		// If the block isn't empty
		if( data[ x ][ 0 ] != '0' )
			return true;

	return false;
}

char Matrix::color( Shape::Type type )
{
	// Return a char based on the type of shape given so game matrix can render in corresponding color
	switch( type )
	{
	case Shape::I:
		return 'I';
		break;
	case Shape::J:
		return 'J';
		break;
	case Shape::L:
		return 'L';
		break;
	case Shape::O:
		return 'O';
		break;
	case Shape::S:
		return 'S';
		break;
	case Shape::T:
		return 'T';
		break;
	case Shape::Z:
		return 'Z';
		break;
	}

	return '0';
}















