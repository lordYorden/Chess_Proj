#pragma once
#include <iostream>
#include "Piece.h"

class Queen : public Piece 
{
public:
	Queen(int x,int y, bool isWhite);
	virtual int isLegal(Piece* board[8][8], std::string& dst);
};