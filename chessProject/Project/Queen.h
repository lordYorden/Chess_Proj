#pragma once
#include <iostream>
#include "Piece.h"

class Queen : public Piece {
	Queen(std::string& place, bool isWhite);
	virtual int isLegal(Piece*& board, std::string& dst);
};