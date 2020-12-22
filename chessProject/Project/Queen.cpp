#include "Queen.h"
#define BLACK 'q'
#define WHITE 'Q'

Queen::Queen(std::string& place, bool isWhite):
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

int Queen::isLegal(Piece*& board, std::string& dst)
{
    //todo
}
