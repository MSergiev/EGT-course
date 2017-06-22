#ifndef CONSTANTS_H_
#define CONSTANTS_H_


// Screen resolution
const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 650;

// Font used
const char FONT[] = "font/PressStart2P.ttf";

// Font size ( consider block length and button padding )
const int FONT_SIZE = 20;

// Text for next shape
const char TEXT_NEXT[] = "Next:";

// Text for score
const char TEXT_SCORE[] = "Score:";

// Text for restart button
const char TEXT_RESTART[] = "New Game";

// Text for pause button
const char TEXT_PAUSE[] = "Pause";
const char TEXT_RESUME[] = "Resume";

// Text for exit button
const char TEXT_EXIT[] = "Exit";

// Button padding
const int BUTTON_PADDING = 20;

// Drop speed ( on a 60Hz monitor )
const int TETRIS_DROP_RATE = 45;

// Tetris field size
const int GAME_MATRIX_WIDTH = 10;
const int GAME_MATRIX_HEIGHT = 20;

// Tetris coordinates
const int GAME_MATRIX_UPPERLEFT_X = 20;
const int GAME_MATRIX_UPPERLEFT_Y = 20;

// Tetris block size ( consider font size and button padding )
const int BLOCK_LENGTH = 30;

// Tetris shape count
const int TOTAL_SHAPES = 7;

// Tetris shape matrix size
const int SHAPE_MATRIX_LENGTH = 4;

// Tetris shapes
const char SHAPES[ TOTAL_SHAPES ][ SHAPE_MATRIX_LENGTH ][ SHAPE_MATRIX_LENGTH ] =
{
	{// I shape
		{ '0', '0', '0', '0' },
		{ '1', '1', '1', '1' },
		{ '0', '0', '0', '0' },
		{ '0', '0', '0', '0' }
	},
	{// J shape
		{ '0', '0', '0', '0' },
		{ '1', '1', '1', '0' },
		{ '0', '0', '1', '0' },
		{ '0', '0', '0', '0' }
	},
	{// L shape
		{ '0', '0', '0', '0' },
		{ '0', '1', '1', '1' },
		{ '0', '1', '0', '0' },
		{ '0', '0', '0', '0' }
	},
	{// O shape
		{ '0', '0', '0', '0' },
		{ '0', '1', '1', '0' },
		{ '0', '1', '1', '0' },
		{ '0', '0', '0', '0' }
	},
	{// S shape
		{ '0', '0', '0', '0' },
		{ '0', '1', '1', '0' },
		{ '1', '1', '0', '0' },
		{ '0', '0', '0', '0' }
	},
	{// T shape
		{ '0', '0', '0', '0' },
		{ '1', '1', '1', '0' },
		{ '0', '1', '0', '0' },
		{ '0', '0', '0', '0' }
	},
	{// Z shape
		{ '0', '0', '0', '0' },
		{ '1', '1', '0', '0' },
		{ '0', '1', '1', '0' },
		{ '0', '0', '0', '0' }
	}
};

// Tetris shape rotation matrix
struct pair
{
	int x;
	int y;
};

const pair 	ROTATION[ 4 ][ SHAPE_MATRIX_LENGTH ][ SHAPE_MATRIX_LENGTH ] =
{
	{// default orientation
		{ {0, 0}, {0, 1}, {0, 2}, {0, 3} },
		{ {1, 0}, {1, 1}, {1, 2}, {1, 3} },
		{ {2, 0}, {2, 1}, {2, 2}, {2, 3} },
		{ {3, 0}, {3, 1}, {3, 2}, {3, 3} }
	},
	{// 90deg clockwise
		{ {3, 0}, {2, 0}, {1, 0}, {0, 0} },
		{ {3, 1}, {2, 1}, {1, 1}, {0, 1} },
		{ {3, 2}, {2, 2}, {1, 2}, {0, 2} },
		{ {3, 3}, {2, 3}, {1, 3}, {0, 3} }
	},
	{// 180deg clockwise
		{ {3, 3}, {3, 2}, {3, 1}, {3, 0} },
		{ {2, 3}, {2, 2}, {2, 1}, {2, 0} },
		{ {1, 3}, {1, 2}, {1, 1}, {1, 0} },
		{ {0, 3}, {0, 2}, {0, 1}, {0, 0} }
	},
	{// 270deg clockwise
		{ {0, 3}, {1, 3}, {2, 3}, {3, 3} },
		{ {0, 2}, {1, 2}, {2, 2}, {3, 2} },
		{ {0, 1}, {1, 1}, {2, 1}, {3, 1} },
		{ {0, 0}, {1, 0}, {2, 0}, {3, 0} }
	}
};

// Directional instructions
const char LEFT = 'l';
const char RIGHT = 'r';
const char DOWN = 'd';
const char UP = 'u';

#endif /* CONSTANTS_H_ */
