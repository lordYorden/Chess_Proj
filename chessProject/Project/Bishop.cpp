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
int Bishop::isLegal(Piece*& board, std::string& dst)
{
	//TODO
}