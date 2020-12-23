#pragma once
#include "Piece.h"
#include <iostream>
#define BLACK 'b'
#define WHITE 'B'
class Bishop : public Piece
{
public:
	Bishop(int x,int y, bool isWhite);
	virtual int isLegal(Piece** board, std::string& dst);
};