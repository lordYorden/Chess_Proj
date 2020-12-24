#include "GameBoard.h"
#include "Piece.h"
#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "NullPiece.h"
#include "Pawn.h"
#include "Knight.h"
#include <iostream>

GameBoard::GameBoard():
	_isWhiteTurn(true)
{
	initBoard();
}

GameBoard::~GameBoard()
{
	//delete[] &this->_board;
}

int GameBoard::move(std::string& move)
{
	std::string playerStr = move.substr(0, 2);
	std::string dst = move.substr(2, 2);
	int opCode = 0;
	std::cout << "sep: " << playerStr << ", " << dst << std::endl;
	Piece* srcPlayer = placeToPiece(playerStr);
	opCode = srcPlayer->isLegal(this->_board, dst);

	if(opCode == 0 || opCode == 1 || opCode == 8)
	{
		Piece* dstPlayer = placeToPiece(dst);
		swap(srcPlayer, dstPlayer);
	}
	return opCode;
}

std::string GameBoard::toStringBoard()
{
	std::string boardStr = "";
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			boardStr += this->_board[i][j]->getValue();
		}
		boardStr += '\n';
	}
	return boardStr;
}

void GameBoard::initBoard()
{
	this->_board[0][0] = new Rook(0, 0, false);
	this->_board[0][7] = new Rook(7, 0, false);
	this->_board[7][7] = new Rook(7, 7, true);
	this->_board[7][0] = new Rook(0, 7, true);

	this->_board[0][1] = new Knight(1, 0, false);
	this->_board[0][6] = new Knight(6, 0, false);
	this->_board[7][6] = new Knight(6, 7, true);
	this->_board[7][1] = new Knight(1, 7, true);

	this->_board[0][2] = new Bishop(2, 0, false);
	this->_board[0][5] = new Bishop(5, 0, false);
	this->_board[7][5] = new Bishop(5, 7, true);
	this->_board[7][2] = new Bishop(2, 7, true);

	this->_board[0][3] = new King(3, 0, false);
	this->_board[7][3] = new King(3, 7, true);

	this->_board[0][4] = new Queen(4, 0, false);
	this->_board[7][4] = new Queen(4, 7, true);

	for (int i = 0; i < 8; i++)
	{
		this->_board[6][i] = new Pawn(i, 6, true);
		this->_board[1][i] = new Pawn(i, 1, false);
	}

	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->_board[i][j] = new NullPiece(j, i);
		}
	}

}

void GameBoard::swap(Piece* a, Piece* b)
{
	int tempX = b->getPositionX();
	int tempY = b->getPositionY();
	this->_board[a->getPositionY()][a->getPositionX()] = b;
	this->_board[b->getPositionY()][b->getPositionX()] = a;

	b->setPositionX(a->getPositionX());
	b->setPositionY(a->getPositionY());
	a->setPositionX(tempX);
	a->setPositionY(tempY);
}

Piece*& GameBoard::placeToPiece(std::string& place)
{
	int opCode = 6;
	int otherX = 0;
	int otherY = 0;

	if (place.length() != 2)
	{
		//throw inputExption *why and how*
	}
	else if ((place[0] > 'h' || place[0] < 'a') || (place[1] > '8' || place[1] < '1'))
	{
		//throw outOfRange
	}
	else
	{
		otherX = place[0] - 'a';
		otherY = place[1] - '1';
	}
	Piece* piece = this->_board[otherY][otherX];
	return piece;
}
