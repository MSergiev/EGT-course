#include "Game.h"

Game::Game()
{
	// Set up random for shapes generation
	srand( time( NULL ) );

	// Select initial shape
	shape.reset( static_cast<Shape::Type>( rand() % TOTAL_SHAPES ) );

	// Copy shape into shadow
	shadow = shape;

	// Generate next shape
	genNextShape();

	window = NULL;
	renderer = NULL;

	// Initialize SDL and quit if it fails
	if( !init( window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT ) )
		quit = true;
	// Load media and quit if it fails
	else if ( !loadMedia( font ) )
		quit = true;
	else
		quit = false;

	// Set score to 0
	score = 0;

	// Make textures from the font
	genText();

	// Set frequency/speed of shapes to drop
	delay = TETRIS_DROP_RATE;
}

Game::~Game()
{
	// Quit SDL
	close( window, renderer, font );
}

void Game::eventHandler( SDL_Event e )
{
	// If player quits
	if( e.type == SDL_QUIT )
		// Quit the game
		quit = true;
	// If a key is pressed
	else if( e.type == SDL_KEYDOWN )
	{
		switch( e.key.keysym.sym )
		{
		case SDLK_LEFT:
			// Move shape one block left
			moveLeft();
			break;
		case SDLK_RIGHT:
			// Move shape one block right
			moveRight();
			break;
		case SDLK_UP:
			// Spin shape 90 degrees clockwise
			spin();
			break;
		case SDLK_DOWN:
			// Lower the shape one block
			speedUp();
			break;
		case SDLK_SPACE:
			// Slam the shape down
			slam();
			break;
		}

		// Render whatever was changed from a key press
		render();
	}
}

bool Game::getQuit() const
{
	return quit;
}

void Game::render()
{
	// Set color to black
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );

	// Clear the screen
	SDL_RenderClear( renderer );

	// Process the frame ( is a shape dropped fully yet, should it drop this frame, generate new shapes, score, etc )
	bool drop = processFrame();

	// Render the shape
	shape.render( renderer, drop );

	// Render the shadow
	renderShadow();

	// Render the matrix
	matrix.render( renderer );

	// Render the next shape
	renderNextShape();

	// Render score
	renderScore();

	// Present the newly drawn frame on screen
	SDL_RenderPresent( renderer );
}

void Game::genText()
{
	// Set up all textures
	headerNext.remake( renderer, TEXT_NEXT, font );
	headerScore.remake( renderer, TEXT_SCORE, font );
	textureScore.remake( renderer, "0", font );
}

void Game::updateScore()
{
	// Transform score to string using stringstream
	std::stringstream ss;
	ss << score;
	std::string scoreStr = ss.str();

	// Remake the score texture
	textureScore.remake( renderer, scoreStr.c_str(), font );
}

void Game::genNextShape()
{
	// Reset the next shape by generating it a new type and setting it's position to the next shape box
	nextShape.reset( static_cast<Shape::Type>( rand() % TOTAL_SHAPES ),
					 GAME_MATRIX_UPPERLEFT_X + ( GAME_MATRIX_WIDTH + 1 ) * BLOCK_LENGTH,
					 GAME_MATRIX_UPPERLEFT_Y );
}

void Game::renderNextShape()
{
	// Render next shape without dropping it
	nextShape.render( renderer, false );

	// Set up a rectangle with block size
	SDL_Rect rect;
	rect.w = BLOCK_LENGTH;
	rect.h = BLOCK_LENGTH;

	// Set draw color to black
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );

	// For each block in the shape matrix
	for( int curX = 0; curX < SHAPE_MATRIX_LENGTH; curX++ )
		for( int curY = 0; curY < SHAPE_MATRIX_LENGTH; curY++ )
		{
			// Set up rectangle at appropriate location
			rect.x = nextShape.getX() + curX * BLOCK_LENGTH;
			rect.y = nextShape.getY() + curY * BLOCK_LENGTH;

			// Render the rectangle outline
			SDL_RenderDrawRect( renderer, &rect );
		}

	// Set rectangle to match the whole next shape block
	rect.x = nextShape.getX();
	rect.y = nextShape.getY();
	rect.w = SHAPE_MATRIX_LENGTH * BLOCK_LENGTH;
	rect.h = SHAPE_MATRIX_LENGTH * BLOCK_LENGTH;

	// Set color to gray and draw it's outline
	SDL_SetRenderDrawColor( renderer, 0x69, 0x69, 0x69, 0xFF );
	SDL_RenderDrawRect( renderer, &rect );

	// Render header inside block
	headerNext.render( renderer, rect.x + 3, rect.y + 3 );
}

void Game::renderShadow()
{
	// Copy current shape into shadow
	shadow = shape;

	// Move shadow down the matrix till it clashes with something in the game matrix
	while( !matrix.isOn( shadow, DOWN ) )
		shadow.move( DOWN );

	// Render the shape as a shadow
	shadow.renderShadow( renderer );
}

void Game::renderScore()
{
	// Make a rectangle
	SDL_Rect rect;

	// Set it's position and size to the scoring box
	rect.x = GAME_MATRIX_UPPERLEFT_X + ( GAME_MATRIX_WIDTH + SHAPE_MATRIX_LENGTH + 2 ) * BLOCK_LENGTH;
	rect.y = GAME_MATRIX_UPPERLEFT_Y;
	rect.h = SHAPE_MATRIX_LENGTH * BLOCK_LENGTH;
	rect.w = 2 * SHAPE_MATRIX_LENGTH * BLOCK_LENGTH;

	// Draw score box outline in gray
	SDL_SetRenderDrawColor( renderer, 0x69, 0x69, 0x69, 0xFF );
	SDL_RenderDrawRect(renderer, &rect);

	// Render header for score inside the block
	headerScore.render( renderer, rect.x + 3, rect.y + 3 );

	// Set up rectangle to print score
	// Move y under the text
	rect.y += headerScore.getHeight();
	// Calculate middle of the remainder of the box
	rect.y = ( rect.y + ( GAME_MATRIX_UPPERLEFT_Y + SHAPE_MATRIX_LENGTH * BLOCK_LENGTH ) - textureScore.getHeight() ) / 2;
	// Return to the start of the box;
	rect.x -= 3;
	// Calculate middle of the box
	rect.x = ( rect.x + rect.x + 2 * SHAPE_MATRIX_LENGTH * BLOCK_LENGTH - textureScore.getWidth() ) / 2;

	// Render score
	textureScore.render( renderer, rect.x, rect.y );
}

bool Game::shouldDrop()
{
	// Reset delay if it's time to drop ( if delay is at it's max )
	if( delay == TETRIS_DROP_RATE )
	{
		delay = 0;
		return true;
	}
	else
	{
		// If not, keep counting
		delay++;
		return false;
	}
}

bool Game::processFrame()
{
	// Is this frame going to lower the shape?
	bool drop = shouldDrop();

	// Check for filled lines and white them out
	matrix.blink();

	// If it's time to drop
	if( drop )
	{
		// Remove filled lines and return how many there were
		int removed = matrix.pop();

		switch( removed )
		{
		case 1:
			// Add 50pts per line
			score += 50;
			break;
		case 2:
			// Add 75pts per line
			score += 150;
			break;
		case 3:
			// Add 100pts per line
			score += 300;
			break;
		case 4:
			// Add 300pts per line
			score += 1200;
			break;
		}

		updateScore();
	}

	// If it's time to drop and the shape is lowered fully
	if( drop && matrix.isOn( shape, DOWN ) )
	{
		// Game matrix absorbs the shape
		matrix.assimilate( shape );

		// Checks if you lost the game
		if( matrix.lose() )
			quit = true;

		// Resets shape
		shape.reset( nextShape.getType() );

		// Copies it to shadow
		shadow = shape;

		// Generates next shape
		genNextShape();
	}

	// Returns should the shape be lowered
	return drop;
}

void Game::spin()
{
	// Make a temporary shape
	Shape tempShape( Shape::I );

	// Copy into it the current one and rotate it
	tempShape = shape;
	tempShape.turn();

	while( true )
		// Move it as much as needed if it glitches through the walls on LEFT, RIGHT or DOWN
		if( matrix.isGlitchWall( tempShape, LEFT ) )
			tempShape.move( RIGHT );
		else if( matrix.isGlitchWall( tempShape, RIGHT ) )
			tempShape.move( LEFT );
		else if( matrix.isGlitchWall( tempShape, DOWN ) )
			tempShape.move( UP );
		else
			break;

	// If it doesn't glitch through something in the game matrix
	if( !matrix.isGlitch( tempShape ) )
		// We'll apply the changes to our current shape
		shape = tempShape;
}

void Game::speedUp()
{
	// Set delay to it's max so next frame will drop the shape
	delay = TETRIS_DROP_RATE;
}

void Game::moveLeft()
{
	// If shape isn't on the left wall
	if( !matrix.isOn( shape, LEFT ) )
		// Move it one block left
		shape.move( LEFT );
}

void Game::moveRight()
{
	// If shape isn't on the right wall
	if( !matrix.isOn( shape, RIGHT ) )
		// Move one block right
		shape.move( RIGHT );
}

void Game::slam()
{
	// Put current shape down to it's shadow's position
	shape = shadow;

	// Set delay to it's max so next frame will try dropping it and will assimilate it into the game matrix
	delay = TETRIS_DROP_RATE;
}











