#pragma once
#include "Piece.h"
#include <iostream>
#define BLACK 'b'
#define WHITE 'B'
#define BOARD_SIZE 8
class Bishop : public Piece
{
public:
	//contructor
	Bishop(int x,int y, bool isWhite);
	//piece abstract method
	virtual int isLegal(Piece* board[BOARD_SIZE][BOARD_SIZE], std::string& dst);
};