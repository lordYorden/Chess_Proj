#pragma once
#include "Knight.h"
#define BLACK 'k'
#define WHITE 'K'

Knight::Knight(std::string& place, bool isWhite):
	Piece(place, isWhite)
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

int Knight::isLegal(Piece*& board, std::string dst)
{
	//todo
}
