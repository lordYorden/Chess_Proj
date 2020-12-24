#pragma once
#include "Piece.h"
class GameBoard
{
private:
	Piece* _board[8][8];
	bool _isWhiteTurn;

	void initBoard();
	bool checkForEat(Piece* src, Piece* dst);
	void swap(Piece* src, Piece* dst);
	Piece*& placeToPiece(std::string& place);
	void flipTurn();

public:
	GameBoard();
	~GameBoard();
	void eat(std::string& move);
	int move(std::string& move);
	std::string toStringBoard();

};