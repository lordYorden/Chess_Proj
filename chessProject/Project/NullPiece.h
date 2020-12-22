#pragma once
#include <iostream>
#include "Piece.h"

class NullPiece : public Piece
{
public:
	NullPiece(int x, int y, bool isWhite);
	NullPiece(Piece& other);
	~NullPiece();
	virtual int isLegal(Piece*& board, std::string& dst);
};