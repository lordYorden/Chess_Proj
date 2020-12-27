#pragma once
#include "Piece.h"
#define BOARD_SIZE 8
class Pawn : public Piece
{
private:
	bool _isFirstMove;
public:
	//c'tructor and d'structor
	Pawn(int x,int y, bool isWhite);
	~Pawn();
	//piece abstract method
	virtual int isLegal(Piece* board[BOARD_SIZE][BOARD_SIZE], std::string& dst);

};