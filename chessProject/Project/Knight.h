#pragma once
#include "Piece.h"
#define BOARD_SIZE 8

class Knight : public Piece
{
public:
	//c'tructor and d'structor
	Knight(int x,int y, bool isWhite);
	~Knight();
	//piece abstract method
	virtual int isLegal(Piece* board[BOARD_SIZE][BOARD_SIZE], std::string& dst);

};