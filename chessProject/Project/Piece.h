#pragma once
#include <iostream>

class Piece {
protected:
	bool _isWhite;
	int _position[2];
	char _value;

public:
	Piece(std::string& place, bool isWhite, char value);
	virtual int isLegal(Piece*& board, std::string dst) = 0;
	void setPosition(std::string& place);
	void setValue(char value);
	int getPositionX();
	int getPositionY();
	bool isPieceWhite();

};