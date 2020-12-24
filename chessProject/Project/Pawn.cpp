#include "Pawn.h"
#define BLACK 'p'
#define WHITE 'P'

Pawn::Pawn(int x,int y, bool isWhite):
	Piece(x,y, isWhite), _isFirstMove(true)
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

int Pawn::isLegal(Piece* board[8][8], std::string& dst)
{
	//todo
	return 0;
}
