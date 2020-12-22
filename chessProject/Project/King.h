#pragma once
#define BLACK 'k'
#define WHITE 'K'
#include "Piece.h"
#include <iostream>
class King : public Piece
{
public:
	King(int x,int y, bool isWhite);
	virtual int isLegal(Piece*& board, std::string& dst);
};
