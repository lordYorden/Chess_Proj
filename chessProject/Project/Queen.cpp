#include "Queen.h"
#define BLACK 'q'
#define WHITE 'Q'

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

int Queen::isLegal(Piece* board[8][8], std::string& dst)
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
		opCode = 6; // defult case
		if (otherX == this->_position[1])
		{
			if (otherY < this->_position[0])
			{
				for (int y = this->_position[0] - 1; y >= 0; y--)
				{
					if (y == otherY)
					{
						opCode = 0;
						return opCode;
					}
					else if (board[y][otherX]->getValue() != '#')
					{
						opCode = 6;
						return opCode;
					}
				}
			}
			else if (otherY > this->_position[0])
			{
				for (int y = this->_position[0] + 1; y < 8; y++)
				{
					if (y == otherY)
					{
						opCode = 0;
						return opCode;
					}
					else if (board[y][otherX]->getValue() != '#')
					{
						opCode = 6;
						return opCode;
					}
				}
			}
		}
		else if(otherY == this->_position[0])
		{
			if (otherX < this->_position[1])
			{
				for (int x = this->_position[1] - 1; x >= 0; x--)
				{
					if (x == otherX)
					{
						opCode = 0;
						return opCode;
					}
					else if (board[otherY][x]->getValue() != '#')
					{
						opCode = 6;
						return opCode;
					}
				}
			}
			else if (otherX > this->_position[1])
			{
				for (int x = this->_position[1] + 1; x < 8; x++)
				{
					if (x == otherX)
					{
						opCode = 0;
						return opCode;
					}
					else if (board[otherY][x]->getValue() != '#')
					{
						opCode = 6;
						return opCode;
					}
				}
			}
		}
		else if (this->_position[1] < otherX && this->_position[0] < otherY)
		{
			for (int x = this->_position[1]+1, y = this->_position[0]+1; x < 8 && y < 8; x++, y++)
			{
				if (x == otherX && y == otherY)
				{
					opCode = 0;
					return opCode;
				}
				else if (board[y][x]->getValue() != '#')
				{
					opCode = 6;
					return opCode;
				}
			}
		}
		else if (this->_position[1] > otherX && this->_position[0] > otherY)
		{
			for (int x = this->_position[1]-1, y = this->_position[0]-1; x >= 0 && y >= 0; x--, y--)
			{
				if (x == otherX && y == otherY)
				{
					opCode = 0;
					return opCode;
				}
				else if (board[y][x]->getValue() != '#')
				{
					opCode = 6;
					return opCode;
				}
			}
		}
		else if (this->_position[1] > otherX && this->_position[0] < otherY)
		{
			for (int x = this->_position[1]-1, y = this->_position[0]+1; x >= 0 && y < 8; x--, y++)
			{
				if (x == otherX && y == otherY)
				{
					opCode = 0;
					return opCode;
				}
				else if (board[y][x]->getValue() != '#')
				{
					opCode = 6;
					return opCode;
				}
			}
		}
		else if (this->_position[1] < otherX && this->_position[0] > otherY)
		{
			for (int x = this->_position[1]+1, y = this->_position[0]-1; x < 8 && y >= 0; x++, y--)
			{
				if (x == otherX && y == otherY)
				{
					opCode = 0;
					return opCode;
				}
				else if (board[y][x]->getValue() != '#')
				{
					opCode = 6;
					return opCode;
				}
			}
		}
	}
	return opCode;
}
