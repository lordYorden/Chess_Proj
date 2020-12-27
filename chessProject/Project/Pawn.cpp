#include "Pawn.h"
#define BLACK 'p'
#define WHITE 'P'
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
#define MOVE_ONE 1
#define MOVE_TWO 2
//opCode
#define OUT_OF_RANGE 5
#define SAME_COLOR 3
#define SAME_SQUARE 7
#define ILIGAL_MOVE 6
#define LIGAL_MOVE 0

/*
* the constructor of class pawn
* input: the place in the board (x,y), is the piece white
* output: none
*/
Pawn::Pawn(int x,int y, bool isWhite):
	Piece(x,y, isWhite), _isFirstMove(true)
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

Pawn::~Pawn()
{
}

/*
* the is legal function checks every single valid move for a piece and checks if the
* curr move with pawn fits one of the posible moves also checks for end result such as
* same place or same color
* input: the board, the place in the board to move the pawn to
* output: opCode - the protocol code that fits the move
*/
int Pawn::isLegal(Piece* board[BOARD_SIZE][BOARD_SIZE], std::string& dst)
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
		//checks for bakward movement
		if (this->_isWhite)
		{
			if (otherY < this->_position[Y_POSITION])
			{
				opCode = ILIGAL_MOVE;
				return opCode;
			}
		}
		else
		{
			if (otherY > this->_position[Y_POSITION])
			{
				opCode = ILIGAL_MOVE;
				return opCode;
			}
		}

		opCode = ILIGAL_MOVE; //default case
		//check ligal dobble first move in pawn
		if (otherX == _position[X_POSITION] && board[otherY][otherX]->getValue() == NULL_PIECE)
		{
			if (this->_isFirstMove)
			{
				if (this->_isWhite)
				{
					if (this->_position[X_POSITION] == otherX && this->_position[Y_POSITION] + MOVE_TWO == otherY)
					{
							if (board[otherY - MOVE_ONE][otherX]->getValue() == NULL_PIECE)
							{
								opCode = LIGAL_MOVE;
								this->_isFirstMove = false;
								return opCode;
							}
							else
							{
								opCode = ILIGAL_MOVE;
								this->_isFirstMove = false;
								return opCode;
							}
					}
					else
					{
						this->_isFirstMove = false;
					}

				}
				else
				{
					if (this->_position[X_POSITION] == otherX && this->_position[Y_POSITION] - MOVE_TWO == otherY)
					{
						if (board[otherY + MOVE_ONE][otherX]->getValue() == NULL_PIECE)
						{
							opCode = LIGAL_MOVE;
							this->_isFirstMove = false;
							return opCode;
						}
						else
						{
							opCode = ILIGAL_MOVE;
							this->_isFirstMove = false;
							return opCode;
						}
					}
					else
					{
						this->_isFirstMove = false;
					}
				}
			}

			if (otherY == _position[Y_POSITION] + MOVE_ONE || otherY == _position[Y_POSITION] - MOVE_ONE)
			{
				opCode = LIGAL_MOVE;
				return opCode;
			}
		}

		//checks for eat
		if (board[otherY][otherX]->getValue() != NULL_PIECE)
		{
			if (this->_isWhite)
			{
				if ((otherX == _position[X_POSITION] + MOVE_ONE) && (otherY == _position[Y_POSITION] + MOVE_ONE))
				{
					opCode = LIGAL_MOVE;
					return opCode;
				}
				else if ((otherX == _position[X_POSITION] - MOVE_ONE) && (otherY == _position[Y_POSITION] + MOVE_ONE))
				{
					opCode = LIGAL_MOVE;
					return opCode;
				}
			}
			else
			{
				if ((otherX == _position[X_POSITION] - MOVE_ONE) && (otherY == _position[Y_POSITION] - MOVE_ONE))
				{
					opCode = LIGAL_MOVE;
					return opCode;
				}
				else if ((otherX == _position[X_POSITION] + MOVE_ONE) && (otherY == _position[Y_POSITION] - MOVE_ONE))
				{
					opCode = LIGAL_MOVE;
					return opCode;
				}
			}
		}
	}
	return opCode;
}
