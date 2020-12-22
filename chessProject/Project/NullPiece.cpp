#include "NullPiece.h"
#define SYMBOL '#'

NullPiece::NullPiece(std::string& place, bool isWhite):
	Piece(place, isWhite)
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

int NullPiece::isLegal(Piece*& board, std::string& dst)
{
	//todo
}


