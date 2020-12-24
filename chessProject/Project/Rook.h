#pragma once
#include "Piece.h"
#include <iostream>
class Rook : public Piece
{
public:
	Rook(int x,int y, bool isWhite);
	virtual int isLegal(Piece* board[8][8], std::string& dst);
private:
	bool inWay(Piece* board[8][8], std::string& dst);
};