#pragma once
#include "Piece.h"
class Pawn : public Piece
{
private:
	bool _isFirstMove;
public:
	Pawn(std::string& place, bool isWhite);
	~Pawn();
	virtual int isLegal(Piece*& board, std::string& dst);

};