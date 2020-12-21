#pragma once
#include "Piece.h"
#include <iostream>
class Knight : public Piece
{
public:
	Knight(std::string& place, bool isWhite);
	~Knight();

	virtual bool isLegal(Piece*& board, std::string dst);
};