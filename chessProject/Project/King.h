#pragma once
#define BLACK 'k'
#define WHITE 'K'
#include "Piece.h"
#include <iostream>
class King : public Piece
{
	King(std::string& place, bool isWhite);
	virtual int isLegal(Piece*& board, std::string& dst);

};
