#pragma once
#include <iostream>
#include "Piece.h"

class Queen : public Piece {
	Queen(int x,int y, bool isWhite);
	virtual int isLegal(Piece*& board, std::string& dst);
};