#include "Bishop.h"

int Bishop::isLegal(Piece*& board, std::string& dst)
{
	//TODO
}
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