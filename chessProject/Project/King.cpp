#include "King.h"

King::King(std::string& place, bool isWhite) :
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
int King::isLegal(Piece*& board, std::string& dst)
{
	//todo
}