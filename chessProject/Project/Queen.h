#pragma once
#include <iostream>
#include "Piece.h"
#define BOARD_SIZE 8

class Queen : public Piece 
{
public:
	//contructor
	Queen(int x,int y, bool isWhite);
	//piece abstract method
	virtual int isLegal(Piece* board[BOARD_SIZE][BOARD_SIZE], std::string& dst);
};