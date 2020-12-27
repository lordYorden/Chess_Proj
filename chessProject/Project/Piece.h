#pragma once
#include <iostream>
#define BOARD_SIZE 8

class Piece {
protected:
	bool _isWhite;
	int _position[2];
	char _value;

public:
	//empty constructor for nullpiece
	Piece();
	Piece(int x,int y, bool isWhite);
	virtual int isLegal(Piece* board[BOARD_SIZE][BOARD_SIZE], std::string& dst) = 0;
	//geters and seters for piece properties
	void setPosition(std::string& place);
	void setPositionX(int x);
	void setPositionY(int y);
	void setValue(char value);
	char getValue() const;
	int getPositionX();
	int getPositionY();
	bool isPieceWhite();

};