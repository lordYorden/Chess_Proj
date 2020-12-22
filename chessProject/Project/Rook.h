#pragma once
#include "Piece.h"
#include <iostream>
class Rook : public Piece
{
	Rook(int x,int y, bool isWhite);
	virtual int isLegal(Piece*& board, std::string& dst);
};