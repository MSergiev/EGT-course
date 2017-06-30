#include "Game.h"

Game::Game() 
{
	// Initialize SDL and quit if it fails
	window = NULL;
	renderer = NULL;
	if( !init( window, renderer ) )
		quit = true;
	// Load media and quit if it fails
	else if ( !loadFont( font ) )
		quit = true;
	else
		quit = false;

	// Initialize shape objects
	shape.setRenderer(renderer);
	nextShape.setRenderer(renderer);
	shadowShape.setRenderer(renderer);
	heldShape.setRenderer(renderer);


	// Set up random for shapes generation
	srand( time( NULL ) );

	// Select initial shape
	shape.reset( static_cast<Shape::Type>( rand() % TOTAL_SHAPES ) );

	// Copy shape into shadow
	shadowShape = shape;

	// Generate next shape
	genNextShape();

	// Held shape is NONE and in hold block
	heldShape.reset( Shape::NONE,
					 GAME_MATRIX_UPPERLEFT_X + ( GAME_MATRIX_WIDTH + 1 ) * BLOCK_LENGTH,
					 GAME_MATRIX_UPPERLEFT_Y + (SHAPE_MATRIX_LENGTH + 1 ) * BLOCK_LENGTH );

	
	// Pause is off
	isPaused = false;

	// Set score to 0
	score = 0;

	// Make textures from the font
	genText();

	// Set frequency/speed of shapes to drop
	delay = TETRIS_DROP_RATE;
}

Game::~Game()
{
	// Destroy textures
	headerNext.destroy();
	headerScore.destroy();
	headerHeld.destroy();
	textureScore.destroy();
	buttonRestart.destroy();
	buttonPause.destroy();
	buttonExit.destroy();

	// Destroy window, renderer and font and quit SDL
	close( window, renderer, font );
}

void Game::eventHandler( SDL_Event& e )
{
	// If player quits
	if( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE )
		// Quit the game
		quit = true;
	// If a key is pressed and the game is not paused
	else if( e.type == SDL_KEYDOWN && !isPaused )
		// Handle the key event
		keyEvent( e );
	// If the mouse is clicked or released
	else if( e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
		// Handle the mouse event
		mouseEvent( e );
}

bool Game::getQuit() const
{
	return quit;
}

void Game::render()
{
	// Set color to black
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

	// Clear the screen
	SDL_RenderClear( renderer );

	// Process the frame ( is a shape dropped fully yet, should it drop this frame, generate new shapes, score, etc )
	bool drop = processFrame();

	// Render the shape
	shape.render( drop );

	// Render the shadow
	renderShadow();

	// Render the matrix
	matrix.render( renderer );

	// Render the next shape
	renderNextShape();

	// Render the held shape
	renderHeldShape();

	// Render score
	renderScore();

	// Render new game button
	renderButtonRestart();

	// Render pause button
	renderButtonPause();

	// Render exit button
	renderButtonExit();

	// Present the newly drawn frame on screen
	SDL_RenderPresent( renderer );
}

void Game::genText()
{
	// Set up all text textures
	headerNext.remake( renderer, TEXT_NEXT, font );
	headerScore.remake( renderer, TEXT_SCORE, font );
	headerHeld.remake( renderer, TEXT_HOLD, font );
	textureScore.remake( renderer, "0", font );
	buttonRestart.remake( renderer, TEXT_RESTART, font );
	buttonPause.remake( renderer, TEXT_PAUSE, font );
	buttonExit.remake( renderer, TEXT_EXIT, font );
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
	nextShape.render( false );

	// Set rectangle to match the whole next shape block
	SDL_Rect rect;
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

void Game::renderHeldShape()
{
	// Render next shape without dropping it
	heldShape.render( false );

	// Set rectangle to match the whole held shape block
	SDL_Rect rect;
	rect.x = heldShape.getX();
	rect.y = heldShape.getY();
	rect.w = SHAPE_MATRIX_LENGTH * BLOCK_LENGTH;
	rect.h = SHAPE_MATRIX_LENGTH * BLOCK_LENGTH;

	// Set color to gray and draw it's outline
	SDL_SetRenderDrawColor( renderer, 0x69, 0x69, 0x69, 0xFF );
	SDL_RenderDrawRect( renderer, &rect );

	// Render header inside block
	headerHeld.render( renderer, rect.x + 3, rect.y + 3 );
}

void Game::renderShadow()
{
	// Copy current shape into shadow
	shadowShape = shape;

	// Move shadow down the matrix till it clashes with something in the game matrix
	while( !matrix.isOn( shadowShape, DOWN ) )
		shadowShape.move( DOWN );

	// Render the shape as a shadow
	shadowShape.renderShadow();
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

void Game::renderButtonRestart()
{
	// Calculate button position
	int x = GAME_MATRIX_UPPERLEFT_X + ( GAME_MATRIX_WIDTH + SHAPE_MATRIX_LENGTH + 2 ) * BLOCK_LENGTH;
	int y = GAME_MATRIX_UPPERLEFT_Y + 5 * BLOCK_LENGTH;

	// Draw button
	buttonRestart.render( renderer, x, y );
}

void Game::renderButtonPause()
{
	// Calculate button position
	int x = GAME_MATRIX_UPPERLEFT_X + ( GAME_MATRIX_WIDTH + SHAPE_MATRIX_LENGTH + 2 ) * BLOCK_LENGTH;
	int y = GAME_MATRIX_UPPERLEFT_Y + 6 * BLOCK_LENGTH + buttonRestart.getHeight();

	// Draw button
	buttonPause.render( renderer, x, y );
}

void Game::renderButtonExit()
{
	// Calculate button position
	int x = GAME_MATRIX_UPPERLEFT_X + ( GAME_MATRIX_WIDTH + SHAPE_MATRIX_LENGTH + 2 ) * BLOCK_LENGTH;
	int y = GAME_MATRIX_UPPERLEFT_Y + 7 * BLOCK_LENGTH + buttonRestart.getHeight() + buttonPause.getHeight();

	// Draw button
	buttonExit.render( renderer, x, y );
}

void Game::releaseButtons()
{
	buttonRestart.release();
	buttonPause.release();
	buttonExit.release();
}

void Game::restart()
{
	// Reset score
	score = 0;

	// Empty field
	matrix.clear();

	// Resume game
	isPaused = false;

	// don't quit
	quit = false;

	// Reset delay
	delay = TETRIS_DROP_RATE;

	// Reset shape and shadow
	shape.reset( static_cast<Shape::Type>( rand() % TOTAL_SHAPES ) );
	shadowShape = shape;

	// Generate next shape
	genNextShape();
}

bool Game::shouldDrop()
{
	// If game is paused, don't drop or advance the delay
	if( isPaused )
		return false;

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
		shadowShape = shape;

		// Generates next shape
		genNextShape();
	}

	// Returns should the shape be lowered
	return drop;
}

void Game::keyEvent( SDL_Event& e )
{
	// Take the pressed key
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
	case SDLK_z:
		// Hold/Release shape
		hold();
	}

	// Render whatever was changed from a key press
	render();
}

void Game::mouseEvent( SDL_Event& e )
{
	if( e.type == SDL_MOUSEBUTTONDOWN )
	{
		// Get current mouse coordinates
		int x, y;
		SDL_GetMouseState( &x, &y );

		// If the mouse is on the restart button
		if( buttonRestart.isIn( x, y ) )
			// Press it
			buttonRestart.press();
		// If the mouse is on the pause button
		else if( buttonPause.isIn( x, y ) )
			// Press it
			buttonPause.press();
		// If the mouse is on the exit button
		else if( buttonExit.isIn( x, y ) )
			// Press it
			buttonExit.press();

		// Render whatever was changed from a mouse click
		render();
	}
	else if( e.type == SDL_MOUSEBUTTONUP )
	{
		// Get current mouse coordinates
		int x, y;
		SDL_GetMouseState( &x, &y );

		// If the mouse is on the restart button and it was pressed
		if( buttonRestart.isIn( x, y ) && buttonRestart.isPressed() )
		{
			// Release it
			buttonRestart.release();

			// Restart game
			restart();
		}
		// If the mouse is on the pause button and it was pressed
		else if( buttonPause.isIn( x, y ) && buttonPause.isPressed() )
		{
			// Release it
			buttonPause.release();

			// If it's paused
			if( isPaused )
			{
				// Make the button "pause" then resume the game
				buttonPause.remake( renderer, TEXT_PAUSE, font );
				isPaused = false;
			}
			else
			{
				// Make the button "resume" then pause the game
				buttonPause.remake( renderer, TEXT_RESUME, font );
				isPaused = true;
			}
		}
		// If the mouse is on the exit button and it was pressed
		else if( buttonExit.isIn( x, y ) && buttonExit.isPressed() )
		{
			// Release it
			buttonExit.release();

			// Quit the game
			quit = true;
		}

		// Release all buttons
		releaseButtons();

		// Render whatever was changed from a mouse click
		render();
	}
}

void Game::spin()
{
	shape.setRotation(shape.getRotation()+1);
	/*
	// Make a temporary shape
	Shape tempShape( renderer );

	// Copy into it the current one and rotate it
	tempShape = shape;
	//tempShape.turn();

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
		*/
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
	shape = shadowShape;

	// Set delay to it's max so next frame will try dropping it and will assimilate it into the game matrix
	delay = TETRIS_DROP_RATE;
}

void Game::hold()
{
	// If we're not holding a shape
	if( heldShape.getType() == Shape::NONE )
	{
		// Grab current shape
		heldShape.reset( shape.getType(),
						 GAME_MATRIX_UPPERLEFT_X + ( GAME_MATRIX_WIDTH + 1 ) * BLOCK_LENGTH,
						 GAME_MATRIX_UPPERLEFT_Y + (SHAPE_MATRIX_LENGTH + 1 ) * BLOCK_LENGTH );

		// Move on to the next one
		shape.reset( nextShape.getType() );
		//shadowShape = shape;

		// Generate next shape
		genNextShape();
	}
	// If we're holding a shape
	else
	{
		// Give currently held shape
		shape.reset( heldShape.getType() );

		// Empty held shape
		heldShape.reset( Shape::NONE,
						 GAME_MATRIX_UPPERLEFT_X + ( GAME_MATRIX_WIDTH + 1 ) * BLOCK_LENGTH,
						 GAME_MATRIX_UPPERLEFT_Y + (SHAPE_MATRIX_LENGTH + 1 ) * BLOCK_LENGTH );
	}
}
