#pragma once
#include <iostream>
#include "Piece.h"

class NullPiece : public Piece
{
public:
	//c'tructor and d'structor
	NullPiece(int x, int y);
	NullPiece(Piece& other);
	~NullPiece();
	//piece abstract method
	virtual int isLegal(Piece* board[8][8], std::string& dst);
};