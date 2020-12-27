#pragma once
#include "Piece.h"
#include <iostream>
class Rook : public Piece
{
public:
	Rook(int x,int y, bool isWhite); //c'tor
	virtual int isLegal(Piece* board[8][8], std::string& dst); //if a rook's move is legal
private:
	bool inWay(Piece* board[8][8], std::string& dst); //if a piece is found in a way of a moving rook
};