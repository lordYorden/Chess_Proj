#include "Piece.h"

Piece::Piece(std::string& place, bool isWhite, char value) :
	_isWhite(isWhite), _value(value)
{
	setPosition(place);
}

void Piece::setPosition(std::string& place)
{
	if (place.length() > 2)
	{
		//throw inputExption
	}
	else if ((place[0] > 'h' || place[0] < 'a') || (place[1] > '8' || place[1] < '1'))
	{
		//throw outOfRange
	}
	else
	{
		this->_position[0] = place[0] - 'a';
		this->_position[1] = place[1] - '1';
	}
}

void Piece::setValue(char value)
{
	this->_value = value;
}

bool Piece::isPieceWhite()
{
	return this->_isWhite;
}
