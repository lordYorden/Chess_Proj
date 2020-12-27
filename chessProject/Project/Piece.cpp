#include "Piece.h"
#define EMPTY '#'
#define DEFAULT 0
#define LESS_THEN_PLACE 2
#define X_MAX_RANGE 'h'
#define X_MIN_RANGE 'a'
#define Y_MIN_RANGE '1'
#define Y_MAX_RANGE '8'
#define Y_POSITION 0
#define X_POSITION 1
#define X_PLACE 0
#define Y_PLACE 1
#define BOARD_SIZE 8

/*
* the Empty constructor of class Piece
* input: none
* output: none
*/
Piece::Piece() :
	_isWhite(false), _value(EMPTY)
{
	setPositionX(DEFAULT);
	setPositionY(DEFAULT);
}

/*
* the constructor of class Piece
* input: the place in the board (x,y), is the piece white
* output: none
*/
Piece::Piece(int x,int y, bool isWhite):
	_isWhite(isWhite)
{
	setPositionX(x);
	setPositionY(y);
}

//garbage not used 
void Piece::setPosition(std::string& place)
{
	if (place.length() > 2)
	{
		//throw inputExption
	}
	else if ((place[X_PLACE] > X_MAX_RANGE || place[X_PLACE] < X_MIN_RANGE) || (place[Y_PLACE] > Y_MAX_RANGE || place[Y_PLACE] < Y_MIN_RANGE))
	{
		//throw outOfRange
	}
	else
	{
		this->_position[X_POSITION] = place[X_PLACE] - X_MIN_RANGE;
		this->_position[Y_POSITION] = place[Y_PLACE] - Y_MIN_RANGE;
	}
}

/*
* set method for x of piece
* input: x the new value
* output: none
*/
void Piece::setPositionX(int x)
{
	this->_position[X_POSITION] = x;
}

/*
* set method for y of piece
* input: y the new value
* output: none
*/
void Piece::setPositionY(int y)
{
	this->_position[Y_POSITION] = y;
}

/*
* set method for the value of the piece
* input: the new value of the piece
* output: none
*/
void Piece::setValue(char value)
{
	this->_value = value;
}

/*
* get method for the value of the piece
* input: none
* output: the value of the piece
*/
char Piece::getValue() const
{
	return this->_value;
}

/*
* get method of x value in piece
* input: none
* output: x the new value
*/
int Piece::getPositionX()
{
	return this->_position[X_POSITION];
}

/*
* get method of y value in piece
* input: none
* output: y the new value
*/
int Piece::getPositionY()
{
	return this->_position[Y_POSITION];
}

/*
* get method for is the curr piece white
* input: none
* output: is the curr piece white
*/
bool Piece::isPieceWhite()
{
	return this->_isWhite;
}
