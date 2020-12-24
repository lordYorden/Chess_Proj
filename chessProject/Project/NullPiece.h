#pragma once
#include <iostream>
#include "Piece.h"

class NullPiece : public Piece
{
public:
	NullPiece(int x, int y);
	NullPiece(Piece& other);
	~NullPiece();
	virtual int isLegal(Piece* board[8][8], std::string& dst);
};