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
	Piece* dstPlayer = placeToPiece(dst);
	Piece* nullPlayer = nullptr;
	opCode = srcPlayer->isLegal(this->_board, dst);
	
	if (srcPlayer->isPieceWhite() == this->_isWhiteTurn)
	{
		if (opCode == 0 || opCode == 1 || opCode == 8)
		{
			if (checkForEat(srcPlayer, dstPlayer))
			{
				nullPlayer = new NullPiece(*dstPlayer);
				this->_board[dstPlayer->getPositionY()][dstPlayer->getPositionX()] = nullPlayer;
				delete dstPlayer;
				swap(srcPlayer, nullPlayer);
			}
			else
			{
				swap(srcPlayer, dstPlayer);
			}
		}
		flipTurn();
	}
	else
	{
		opCode = 2;
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
	this->_board[0][0] = new Rook(0, 0, true);
	this->_board[0][7] = new Rook(7, 0, true);
	this->_board[7][7] = new Rook(7, 7, false);
	this->_board[7][0] = new Rook(0, 7, false);

	this->_board[0][1] = new Knight(1, 0, true);
	this->_board[0][6] = new Knight(6, 0, true);
	this->_board[7][6] = new Knight(6, 7, false);
	this->_board[7][1] = new Knight(1, 7, false);

	this->_board[0][2] = new Bishop(2, 0, true);
	this->_board[0][5] = new Bishop(5, 0, true);
	this->_board[7][5] = new Bishop(5, 7, false);
	this->_board[7][2] = new Bishop(2, 7, false);

	this->_board[0][3] = new King(3, 0, true);
	this->_board[7][3] = new King(3, 7, false);

	this->_board[0][4] = new Queen(4, 0, true);
	this->_board[7][4] = new Queen(4, 7, false);

	for (int i = 0; i < 8; i++)
	{
		this->_board[6][i] = new Pawn(i, 6, false);
		this->_board[1][i] = new Pawn(i, 1, true);
	}

	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->_board[i][j] = new NullPiece(j, i);
		}
	}

}

bool GameBoard::checkForEat(Piece* src, Piece* dst)
{
	if ((src->isPieceWhite() != dst->isPieceWhite()) && (src->getValue() != '#' || dst->getValue() != '#'))
	{
		return true;
	}
	return false;
}

void GameBoard::swap(Piece* src, Piece* dst)
{
	int tempX = dst->getPositionX();
	int tempY = dst->getPositionY();
	this->_board[src->getPositionY()][src->getPositionX()] = dst;
	this->_board[dst->getPositionY()][dst->getPositionX()] = src;

	dst->setPositionX(src->getPositionX());
	dst->setPositionY(src->getPositionY());
	src->setPositionX(tempX);
	src->setPositionY(tempY);
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

void GameBoard::flipTurn()
{
	if (this->_isWhiteTurn)
	{
		this->_isWhiteTurn = false;
	}
	else
	{
		this->_isWhiteTurn = true;
	}
}
