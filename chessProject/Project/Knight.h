#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(std::string& place, bool isWhite);
	~Knight();
	virtual int isLegal(Piece*& board, std::string dst);

};