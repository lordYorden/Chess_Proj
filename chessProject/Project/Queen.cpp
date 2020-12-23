#include "Queen.h"
#define BLACK 'q'
#define WHITE 'Q'

Queen::Queen(int x,int y, bool isWhite):
    Piece(x,y, isWhite)
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

int Queen::isLegal(Piece** board, std::string& dst)
{
    //todo
	return 0;
}
