#include "NullPiece.h"
#define SYMBOL '#'
//opCode
#define NO_PLAYER 2

/*
* the constructor of class NullPiece
* input: the place in the board (x,y), is the piece white
* output: none
*/
NullPiece::NullPiece(int x, int y):
	Piece(x,y, false)
{
	this->setValue(SYMBOL);
}

/*
* the copy constructor of class NullPiece
* input: other - another piece
* output: none
*/
NullPiece::NullPiece(Piece& other):
	Piece()
{
	this->setPositionX(other.getPositionX());
	this->setPositionY(other.getPositionY());
	this->setValue(SYMBOL);
}

NullPiece::~NullPiece()
{
}

/*
* is the is legal method is called in the empty piece class
* returns no_player opCode 2
* input: the board, the place in the board to move the NullPiece to
* output: opCode - the protocol code no_player
*/
int NullPiece::isLegal(Piece* board[8][8], std::string& dst)
{
	//todo
	return NO_PLAYER;
}


