#include "Knight.h"
#include "Piece.h"

#define BLACK 'k'
#define WHITE 'K'

Knight::Knight(std::string& place, bool isWhite):
	Piece(place, isWhite)
{
	if (isWhite)
	{
		this->setValue(WHITE);
	}
	else 
	{
		this->setValue(BLACK);
	}
}

Knight::~Knight()
{
}

bool Knight::isLegal(Piece*& board, std::string dst)
{
	if ((dst[0] > 'h' || dst[0] < 'a') || (dst[1] > '8' || dst[1] < '1'))
	{
		//throw outOfRange
	}
	else
	{
		this->_position[0] = dst[0] - 'a';
		this->_position[1] = dst[1] - '1';
	}


}
