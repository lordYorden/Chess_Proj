#pragma once
#include <iostream>
#include "Piece.h"

class NullPiece : public Piece
{
public:
	NullPiece(std::string& place, bool isWhite);
	NullPiece(Piece& other);
	~NullPiece();
	virtual int isLegal(Piece*& board, std::string& dst);
};