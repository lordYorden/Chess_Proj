#pragma once
#include "Knight.h"
#define BLACK 'n'
#define WHITE 'N'
#include <typeinfo>

Knight::Knight(int x,int y, bool isWhite):
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

Knight::~Knight()
{
}

int Knight::isLegal(Piece* board[8][8], std::string& dst)
{
	int opCode = 0;
	int otherX = 0;
	int otherY = 0;

	if (dst.length() > 2)
	{
		//throw inputExption *why and how*
	}
	else if ((dst[1] > 'h' || dst[1] < 'a') || (dst[0] > '8' || dst[0] < '1'))
	{
		opCode = 5;
	}
	else
	{
		otherX = dst[1] - 'a';
		otherY = dst[0] - '1';
	}

	if (board[otherY][otherX]->getValue() != '#')
	{

		if ((otherX == this->_position[1]) && (otherY == this->_position[0]))
		{
			opCode = 7;
		}
		else if (this->_isWhite == board[otherX][otherY]->isPieceWhite())
		{
			opCode = 3;
		}
	}

	if (!opCode)
	{
		if ((otherX == this->_position[1] + 1) && (otherY == this->_position[0] + 2))
		{
			opCode = 0;
		}
		else if ((otherX == this->_position[1] + 2) && (otherY == this->_position[0] + 1))
		{
			opCode = 0;
		}
		else if ((otherX == this->_position[1] - 1) && (otherY == this->_position[0] + 2))
		{
			opCode = 0;
		}
		else if ((otherX == this->_position[1] - 2) && (otherY == this->_position[0] + 1))
		{
			opCode = 0;
		}
		else if ((otherX == this->_position[1] + 1) && (otherY == this->_position[0] - 2))
		{
			opCode = 0;
		}
		else if ((otherX == this->_position[1] + 2) && (otherY == this->_position[0] - 1))
		{
			opCode = 0;
		}
		else if ((otherX == this->_position[1] - 1) && (otherY == this->_position[0] - 2))
		{
			opCode = 0;
		}
		else if ((otherX == this->_position[1] - 2) && (otherY == this->_position[0] - 1))
		{
			opCode = 0;
		}
		else
		{
			opCode = 6;
		}
	}


	return opCode;
}