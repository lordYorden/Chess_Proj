#include "King.h"

King::King(int x,int y, bool isWhite) :
	Piece(x,y,isWhite)
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
int King::isLegal(Piece* board[8][8], std::string& dst)
{
	//todo
	return 0;
}