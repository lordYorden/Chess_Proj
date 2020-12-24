#pragma once
#include "Piece.h"
class Pawn : public Piece
{
private:
	bool _isFirstMove;
public:
	Pawn(int x,int y, bool isWhite);
	~Pawn();
	virtual int isLegal(Piece* board[8][8], std::string& dst);

};