#include "Piece.h"
#define EMPTY '#'
#define DEFAULT 0
Piece::Piece() :
	_isWhite(false), _value(EMPTY)
{
	setPositionX(DEFAULT);
	setPositionY(DEFAULT);
}

Piece::Piece(std::string& place, bool isWhite):
	_isWhite(isWhite)
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
		this->_position[1] = place[1] - '0';
	}
}

void Piece::setPositionX(int x)
{
	this->_position[0] = x;
}

void Piece::setPositionY(int y)
{
	this->_position[1] = y;
}

void Piece::setValue(char value)
{
	this->_value = value;
}

char Piece::getValue() const
{
	return this->_value;
}

int Piece::getPositionX()
{
	return this->_position[0];
}

int Piece::getPositionY()
{
	return this->_position[1];
}

bool Piece::isPieceWhite()
{
	return this->_isWhite;
}
