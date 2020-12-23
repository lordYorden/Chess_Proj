#include "NullPiece.h"
#define SYMBOL '#'

NullPiece::NullPiece(int x, int y):
	Piece(x,y, false)
{
	this->setValue(SYMBOL);
}

NullPiece::NullPiece(Piece& other):
	Piece()
{
	this->setPositionX(other.getPositionX());
	this->setPositionY(other.getPositionY());
}

NullPiece::~NullPiece()
{
}

int NullPiece::isLegal(Piece** board, std::string& dst)
{
	//todo
	return 2;
}


