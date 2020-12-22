#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	Pawn(std::string& place, bool isWhite);
	~Pawn();
	virtual int isLegal(Piece*& board, std::string& dst);
};