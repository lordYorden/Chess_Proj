#pragma once
#define BLACK 'k'
#define WHITE 'K'
#include "Piece.h"
#include <iostream>
class King : public Piece
{
public:
	King(int x,int y, bool isWhite);
	virtual int isLegal(Piece* board[8][8], std::string& dst); //if the moevement is legal
	bool isValid(Piece* board[8][8], std::string& dst); //if the movement is valid
};
