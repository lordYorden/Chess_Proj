#pragma once
#include "Piece.h"
#include <iostream>
class Rook : public Piece
{
	Rook(std::string& place, bool isWhite, char value);
	virtual int isLegal(Piece*& board, std::string& dst);
};