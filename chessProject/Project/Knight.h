#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(int x,int y, bool isWhite);
	~Knight();
	virtual int isLegal(Piece*& board, std::string dst);

};