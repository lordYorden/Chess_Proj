#pragma once
#include <iostream>
#include "Piece.h"

class Queen : public Piece 
{
public:
	Queen(int x,int y, bool isWhite);
	virtual int isLegal(Piece** board, std::string& dst);
};