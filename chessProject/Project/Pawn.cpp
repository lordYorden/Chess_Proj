#include "Pawn.h"
#define BLACK 'p'
#define WHITE 'P'

Pawn::Pawn(std::string& place, bool isWhite):
	Piece(place, isWhite)
{
	if (this->_isWhite)
	{
		setValue(WHITE);
	}
	else
	{
		setValue(BLACK);
	}
}

Pawn::~Pawn()
{
}

int Pawn::isLegal(Piece*& board, std::string& dst)
{
	//todo
}
