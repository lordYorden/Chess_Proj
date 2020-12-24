#pragma once
#include "Piece.h"
class GameBoard
{
private:
	Piece* _board[8][8];
	bool _isWhiteTurn;

	void initBoard();
	bool checkForEat(std::string& move);
	void swap(Piece* a, Piece* b);
	Piece*& placeToPiece(std::string& place);

public:
	GameBoard();
	~GameBoard();
	void eat(std::string& move);
	int move(std::string& move);
	std::string toStringBoard();

};