#pragma once
#include "Knight.h"
#define BLACK 'n'
#define WHITE 'N'

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

int Knight::isLegal(Piece*& board, std::string& dst)
{
	//todo
}
