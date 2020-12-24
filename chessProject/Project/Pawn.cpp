#include "Pawn.h"
#define BLACK 'p'
#define WHITE 'P'

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

int Pawn::isLegal(Piece* board[8][8], std::string& dst)
{
	int opCode = 0;
	int otherX = 0;
	int otherY = 0;

	if (dst.length() > 2)
	{
		//throw inputExption *why and how*
	}
	else if ((dst[0] > 'h' || dst[0] < 'a') || (dst[1] > '8' || dst[1] < '1'))
	{
		opCode = 5;
	}
	else
	{
		otherX = dst[0] - 'a';
		otherY = dst[1] - '1';
	}


	if (board[otherY][otherX]->getValue() != '#')
	{

		if ((otherX == this->_position[1]) && (otherY == this->_position[0]))
		{
			opCode = 7;
		}
		else if (this->_isWhite == board[otherY][otherX]->isPieceWhite())
		{
			opCode = 3;
		}
	}

	if (!opCode)
	{
		if(this->_isFirstMove)
		{
			if (this->_isWhite)
			{
				if (this->_position[1] == otherX && this->_position[0] + 2 == otherY)
				{
					opCode = 0;
					this->_isFirstMove = false;
					return opCode;
				}
			}
			else
			{
				if (this->_position[1] == otherX && this->_position[0] - 2 == otherY)
				{
					opCode = 0;
					this->_isFirstMove = false;
					return opCode;
				}
			}
		}

		if (this->_isWhite)
		{
			if (otherY < this->_position[0])
			{
				opCode = 6;
				return opCode;
			}
		}
		else
		{
			if (otherY > this->_position[0])
			{
				opCode = 6;
				return opCode;
			}
		}

		opCode = 6;
		if (otherX == _position[1])
		{
			if (otherY == _position[0] + 1 || otherY == _position[0] - 1)
			{
				opCode = 0;
				return opCode;
			}
		}

		if (board[otherY][otherX]->getValue() != '#')//if eat
		{
			if (this->_isWhite)
			{
				if ((otherX == _position[1] + 1) && (otherY == _position[0] + 1))
				{
					opCode = 0;
					return opCode;
				}
				else if ((otherX == _position[1] - 1) && (otherY == _position[0] + 1))
				{
					opCode = 0;
					return opCode;
				}
			}
			else
			{
				if ((otherX == _position[1] - 1) && (otherY == _position[0] - 1))
				{
					opCode = 0;
					return opCode;
				}
				else if ((otherX == _position[1] + 1) && (otherY == _position[0] - 1))
				{
					opCode = 0;
					return opCode;
				}
			}
		}
	}
	return opCode;
}
