#include "Bishop.h"

Bishop::Bishop(int x,int y, bool isWhite) :
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
int Bishop::isLegal(Piece* board[8][8], std::string& dst)
{
	//TODO
	return 0;
}