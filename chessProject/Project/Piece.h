#pragma once
#include <iostream>

class Piece {
protected:
	bool _isWhite;
	int _position[2];
	char _value;

public:
	//empty constructor for nullpiece
	Piece();
	Piece(int x,int y, bool isWhite);
	virtual int isLegal(Piece* board[8][8], std::string& dst) = 0;
	void setPosition(std::string& place);
	void setPositionX(int x);
	void setPositionY(int y);
	void setValue(char value);
	char getValue() const;
	int getPositionX();
	int getPositionY();
	bool isPieceWhite();

};