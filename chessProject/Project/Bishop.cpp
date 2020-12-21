#include "Bishop.h"

Bishop::Bishop(std::string& place, bool isWhite) :
	Piece(place,isWhite)
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