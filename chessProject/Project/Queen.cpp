#include "Queen.h"
#define BLACK 'q'
#define WHITE 'Q'
#define LESS_THEN_PLACE 2
#define X_MAX_RANGE 'h'
#define X_MIN_RANGE 'a'
#define Y_MIN_RANGE '1'
#define Y_MAX_RANGE '8'
#define Y_POSITION 0
#define X_POSITION 1
#define NULL_PIECE '#'
#define X_PLACE 0
#define Y_PLACE 1
#define BOARD_SIZE 8
#define MIN_X 0
#define NOT_THE_CURR_PIECE 1
//opCode
#define OUT_OF_RANGE 5
#define SAME_COLOR 3
#define SAME_SQUARE 7
#define ILIGAL_MOVE 6
#define LIGAL_MOVE 0


/*
* the constructor of class queen
* input: the place in the board (x,y), is the piece white
* output: none
*/
Queen::Queen(int x,int y, bool isWhite):
    Piece(x,y, isWhite)
{
	if (this->_isWhite)
	{
		setValue(WHITE);
	}
	else
	{
		setValue(BLACK);
	}
}

/*
* the is legal function checks every single valid move for a piece and checks if the 
* curr move with queen fits one of the posible moves also checks for end result such as
* same place or same color
* input: the board, the place in the board to move the queen to
* output: opCode - the protocol code that fits the move  
*/
int Queen::isLegal(Piece* board[BOARD_SIZE][BOARD_SIZE], std::string& dst)
{
	int opCode = 0;
	int otherX = 0;
	int otherY = 0;

	if (dst.length() > LESS_THEN_PLACE)
	{
		//throw inputExption *why and how*
	}
	else if ((dst[X_PLACE] > X_MAX_RANGE || dst[X_PLACE] < X_MIN_RANGE) || (dst[Y_PLACE] > Y_MAX_RANGE || dst[Y_PLACE] < Y_MIN_RANGE))
	{
		opCode = OUT_OF_RANGE;
	}
	else
	{
		otherX = dst[X_PLACE] - X_MIN_RANGE;
		otherY = dst[Y_PLACE] - Y_MIN_RANGE;
	}


	if (board[otherY][otherX]->getValue() != NULL_PIECE)
	{

		if ((otherX == this->_position[X_POSITION]) && (otherY == this->_position[Y_POSITION]))
		{
			opCode = SAME_SQUARE;
		}
		else if (this->_isWhite == board[otherY][otherX]->isPieceWhite())
		{
			opCode = SAME_COLOR;
		}
	}

	if (!opCode)
	{
		opCode = ILIGAL_MOVE; // default case

		//checking vertical lines
		if (otherX == this->_position[X_POSITION])
		{
			if (otherY < this->_position[Y_POSITION])
			{
				for (int y = this->_position[Y_POSITION] - NOT_THE_CURR_PIECE; y >= MIN_X; y--)
				{
					if (y == otherY)
					{
						opCode = LIGAL_MOVE;
						return opCode;
					}
					else if (board[y][otherX]->getValue() != NULL_PIECE)
					{
						opCode = ILIGAL_MOVE;
						return opCode;
					}
				}
			}
			else if (otherY > this->_position[Y_POSITION])
			{
				for (int y = this->_position[Y_POSITION] + NOT_THE_CURR_PIECE; y < BOARD_SIZE; y++)
				{
					if (y == otherY)
					{
						opCode = LIGAL_MOVE;
						return opCode;
					}
					else if (board[y][otherX]->getValue() != NULL_PIECE)
					{
						opCode = ILIGAL_MOVE;
						return opCode;
					}
				}
			}
		}
		//checking horizontal lines
		else if(otherY == this->_position[Y_POSITION])
		{
			if (otherX < this->_position[X_POSITION])
			{
				for (int x = this->_position[X_POSITION] - NOT_THE_CURR_PIECE; x >= MIN_X; x--)
				{
					if (x == otherX)
					{
						opCode = LIGAL_MOVE;
						return opCode;
					}
					else if (board[otherY][x]->getValue() != NULL_PIECE)
					{
						opCode = ILIGAL_MOVE;
						return opCode;
					}
				}
			}
			else if (otherX > this->_position[X_POSITION])
			{
				for (int x = this->_position[X_POSITION] + NOT_THE_CURR_PIECE; x < BOARD_SIZE; x++)
				{
					if (x == otherX)
					{
						opCode = LIGAL_MOVE;
						return opCode;
					}
					else if (board[otherY][x]->getValue() != NULL_PIECE)
					{
						opCode = ILIGAL_MOVE;
						return opCode;
					}
				}
			}
		}
		//checking upper right diagonal
		else if (this->_position[X_POSITION] < otherX && this->_position[Y_POSITION] < otherY)
		{
			for (int x = this->_position[X_POSITION]+NOT_THE_CURR_PIECE, y = this->_position[Y_POSITION]+NOT_THE_CURR_PIECE; x < BOARD_SIZE && y < BOARD_SIZE; x++, y++)
			{
				if (x == otherX && y == otherY)
				{
					opCode = LIGAL_MOVE;
					return opCode;
				}
				else if (board[y][x]->getValue() != NULL_PIECE)
				{
					opCode = ILIGAL_MOVE;
					return opCode;
				}
			}
		}
		//checking bottom left diagonal
		else if (this->_position[X_POSITION] > otherX && this->_position[Y_POSITION] > otherY)
		{
			for (int x = this->_position[X_POSITION]-NOT_THE_CURR_PIECE, y = this->_position[Y_POSITION]-NOT_THE_CURR_PIECE; x >= MIN_X && y >= MIN_X; x--, y--)
			{
				if (x == otherX && y == otherY)
				{
					opCode = LIGAL_MOVE;
					return opCode;
				}
				else if (board[y][x]->getValue() != NULL_PIECE)
				{
					opCode = ILIGAL_MOVE;
					return opCode;
				}
			}
		}
		//checking upper right diagonal
		else if (this->_position[X_POSITION] > otherX && this->_position[Y_POSITION] < otherY)
		{
			for (int x = this->_position[X_POSITION]-NOT_THE_CURR_PIECE, y = this->_position[Y_POSITION]+NOT_THE_CURR_PIECE; x >= MIN_X && y < BOARD_SIZE; x--, y++)
			{
				if (x == otherX && y == otherY)
				{
					opCode = LIGAL_MOVE;
					return opCode;
				}
				else if (board[y][x]->getValue() != NULL_PIECE)
				{
					opCode = ILIGAL_MOVE;
					return opCode;
				}
			}
		}
		//checking bottom right diagonal
		else if (this->_position[X_POSITION] < otherX && this->_position[Y_POSITION] > otherY)
		{
			for (int x = this->_position[X_POSITION]+NOT_THE_CURR_PIECE, y = this->_position[Y_POSITION]-NOT_THE_CURR_PIECE; x < BOARD_SIZE && y >= MIN_X; x++, y--)
			{
				if (x == otherX && y == otherY)
				{
					opCode = LIGAL_MOVE;
					return opCode;
				}
				else if (board[y][x]->getValue() != NULL_PIECE)
				{
					opCode = ILIGAL_MOVE;
					return opCode;
				}
			}
		}
	}
	return opCode;
}