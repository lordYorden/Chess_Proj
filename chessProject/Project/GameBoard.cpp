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
	//king black and king white default values
	this->_blackKingPlace = "d8";
	this->_whiteKingPlace = "d1";
}

GameBoard::~GameBoard()
{
	//delete[] &this->_board;
}

int GameBoard::move(std::string& move)
{
	std::string playerStr = move.substr(0, 2);
	std::string dst = move.substr(2, 2);
	bool isEat = false;
	int opCode = 0;
	std::cout << "sep: " << playerStr << ", " << dst << std::endl;
	Piece* srcPlayer = placeToPiece(playerStr);
	Piece* dstPlayer = placeToPiece(dst);
	Piece* nullPlayer = nullptr;
	
	if (srcPlayer->isPieceWhite() == this->_isWhiteTurn)
	{
		opCode = srcPlayer->isLegal(this->_board, dst);
		if (opCode == 0)
		{
			if (srcPlayer->getValue() == 'k' || srcPlayer->getValue() == 'K')
			{
				if (srcPlayer->isPieceWhite())
				{
					this->_whiteKingPlace = dst;
				}
				else
				{
					this->_blackKingPlace = dst;
				}
			}

			if (dstPlayer->getValue() == 'k' || dstPlayer->getValue() == 'K')
			{
				opCode = 8;
				return opCode;
			}
			isEat = checkForEat(srcPlayer, dstPlayer);
			if (isEat)
			{
				nullPlayer = new NullPiece(*dstPlayer);
				this->_board[dstPlayer->getPositionY()][dstPlayer->getPositionX()] = nullPlayer;
				swap(srcPlayer, nullPlayer);
			}
			else
			{
				swap(srcPlayer, dstPlayer);
			}

			if (isThreatened(!this->_isWhiteTurn))
			{
				opCode = 1;
			}
			else if (isThreatened(this->_isWhiteTurn))
			{
				opCode = 4;
				
				if (isEat)
				{
					swap(nullPlayer, srcPlayer);
				}
				swap(dstPlayer, srcPlayer);
				if (isEat)
				{
					delete nullPlayer;
				}
				
			}
			if (opCode == 0 || opCode == 1 || opCode == 8)
			{
				flipTurn();
			}
		}
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
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			boardStr += this->_board[i][j]->getValue();
		}
		boardStr += '\n';
	}
	return boardStr;
}

bool GameBoard::isThreatened(bool isCheckingWhite)
{
	int xB = _blackKingPlace[0] - 'a';
	int yB = _blackKingPlace[1] - '1';
	int xW = _whiteKingPlace[0] - 'a';
	int yW = _whiteKingPlace[1] - '1';

	bool isFirstDiagonalInstance = false;
	bool isFirstLineInstance = false;
	if (isCheckingWhite)
	{
		//checking white diagonals
		for (int x = xW + 1, y = yW + 1; x < 8 && y < 8; x++, y++)
		{
			if ((this->_board[y][x]->getValue() == 'q' || this->_board[y][x]->getValue() == 'b') && !isFirstDiagonalInstance)
			{
				return true;
			}
			else if (this->_board[y][x]->getValue() != '#' && !isFirstDiagonalInstance)
			{
				isFirstDiagonalInstance = true;
			}
		}

		isFirstDiagonalInstance = false;
		for (int x = xW - 1, y = yW - 1; x >= 0 && y >= 0; x--, y--)
		{
			if ((this->_board[y][x]->getValue() == 'q' || this->_board[y][x]->getValue() == 'b') && !isFirstDiagonalInstance)
			{
				return true;
			}
			else if (this->_board[y][x]->getValue() != '#' && !isFirstDiagonalInstance)
			{
				isFirstDiagonalInstance = true;
			}
		}

		isFirstDiagonalInstance = false;
		for (int x = xW - 1, y = yW + 1; x >= 0 && y < 8; x--, y++)
		{
			if ((this->_board[y][x]->getValue() == 'q' || this->_board[y][x]->getValue() == 'b') && !isFirstDiagonalInstance)
			{
				return true;
			}
			else if (this->_board[y][x]->getValue() != '#' && !isFirstDiagonalInstance)
			{
				isFirstDiagonalInstance = true;
			}
		}
			
		isFirstDiagonalInstance = false;
		for (int x = xW + 1, y = yW - 1; x < 8 && y >= 0; x++, y--)
		{
			if ((this->_board[y][x]->getValue() == 'q' || this->_board[y][x]->getValue() == 'b') && !isFirstDiagonalInstance)
			{
				return true;
			}
			else if (this->_board[y][x]->getValue() != '#' && !isFirstDiagonalInstance)
			{
				isFirstDiagonalInstance = true;
			}
		}

		//checking lines white
		//vertical
		isFirstLineInstance = false;
		for (int y = yW - 1; y >= 0; y--)
		{
			if ((this->_board[y][xW]->getValue() == 'q' || this->_board[y][xW]->getValue() == 'r') && !isFirstLineInstance)
			{
				return true;
			}
			else if (this->_board[y][xW]->getValue() != '#' && !isFirstLineInstance)
			{
				isFirstLineInstance = true;
			}
		}

		isFirstLineInstance = false;
		for (int y = yW + 1; y < 8; y++)
		{
			if ((this->_board[y][xW]->getValue() == 'q' || this->_board[y][xW]->getValue() == 'r') && !isFirstLineInstance)
			{
				return true;
			}
			else if (this->_board[y][xW]->getValue() != '#' && !isFirstLineInstance)
			{
				isFirstLineInstance = true;
			}
		}

		//horizontal
		isFirstLineInstance = false;
		for (int x = xW - 1; x >= 0; x--)
		{
			if ((this->_board[yW][x]->getValue() == 'q' || this->_board[yW][x]->getValue() == 'r') && !isFirstLineInstance)
			{
				return true;
			}
			else if (this->_board[yW][x]->getValue() != '#' && !isFirstLineInstance)
			{
				isFirstLineInstance = true;
			}
		}

		isFirstLineInstance = false;
		for (int x = xW + 1; x < 8; x++)
		{
			if ((this->_board[yW][x]->getValue() == 'q' || this->_board[yW][x]->getValue() == 'r') && !isFirstLineInstance)
			{
				return true;
			}
			else if (this->_board[yW][x]->getValue() != '#' && !isFirstLineInstance)
			{
				isFirstLineInstance = true;
			}
		}

		//checking pawn white
		if ((yW - 1 > 0 && xW + 1 < 8) && _board[yW - 1][xW + 1]->getValue() == 'p')
		{
			return true;
		}
		else if ((yW - 1 > 0 && xW - 1 > 0) && _board[yW - 1][xW - 1]->getValue() == 'p')
		{
			return true;
		}
		//checking knights black
		if ((yW + 2 < 8 && xW + 2 < 8) && _board[yW + 2][xW + 1]->getValue() == 'n')
		{
			return true;
		}
		else if ((yW + 1 < 8 && xW + 2 < 8) && _board[yW + 1][xW + 2]->getValue() == 'n')
		{
			return true;
		}
		else if ((yW + 2 < 8 && xW - 1 > 0) && _board[yW + 2][xW - 1]->getValue() == 'n')
		{
			return true;
		}
		else if ((yW + 1 < 8 && xW - 2 > 0) && _board[yW + 1][xW - 2]->getValue() == 'n')
		{
			return true;
		}
		else if ((yW - 1 > 0 && xW - 2 > 0) && _board[yW - 1][xW - 2]->getValue() == 'n')
		{
			return true;
		}
		else if ((yW - 2 > 0 && xW - 1 > 0) && _board[yW - 2][xW - 1]->getValue() == 'n')
		{
			return true;
		}
		else if ((yW - 2 > 0 && xW + 1 < 8) && _board[yW - 2][xW + 1]->getValue() == 'n')
		{
			return true;
		}
		else if ((yW - 1 > 0 && xW + 2 < 8) && _board[yW - 1][xW + 2]->getValue() == 'n')
		{
			return true;
		}

		
	}
	else
	{
		//checking Black diagonals
		isFirstDiagonalInstance = false;
		for (int x = xB + 1, y = yB + 1; x < 8 && y < 8; x++, y++)
		{
			if ((this->_board[y][x]->getValue() == 'Q' || this->_board[y][x]->getValue() == 'B') && !isFirstDiagonalInstance)
			{
				return true;
			}
			else if (this->_board[y][x]->getValue() != '#' && !isFirstDiagonalInstance)
			{
				isFirstDiagonalInstance = true;
			}
		}

		isFirstDiagonalInstance = false;
		for (int x = xB - 1, y = yB - 1; x >= 0 && y >= 0; x--, y--)
		{
			if ((this->_board[y][x]->getValue() == 'Q' || this->_board[y][x]->getValue() == 'B') && !isFirstDiagonalInstance)
			{
				return true;
			}
			else if (this->_board[y][x]->getValue() != '#' && !isFirstDiagonalInstance)
			{
				isFirstDiagonalInstance = true;
			}
		}

		isFirstDiagonalInstance = false;
		for (int x = xB - 1, y = yB + 1; x >= 0 && y < 8; x--, y++)
		{
			if ((this->_board[y][x]->getValue() == 'Q' || this->_board[y][x]->getValue() == 'B') && !isFirstDiagonalInstance)
			{
				return true;
			}
			else if (this->_board[y][x]->getValue() != '#' && !isFirstDiagonalInstance)
			{
				isFirstDiagonalInstance = true;
			}
		}

		isFirstDiagonalInstance = false;
		for (int x = xB + 1, y = yB - 1; x < 8 && y >= 0; x++, y--)
		{
			if ((this->_board[y][x]->getValue() == 'Q' || this->_board[y][x]->getValue() == 'B') && !isFirstDiagonalInstance)
			{
				return true;
			}
			else if (this->_board[y][x]->getValue() != '#' && !isFirstDiagonalInstance)
			{
				isFirstDiagonalInstance = true;
			}
		}

		//checking lines black
		//vertical
		isFirstLineInstance = false;
		for (int y = yB - 1; y >= 0; y--)
		{
			if ((this->_board[y][xB]->getValue() == 'Q' || this->_board[y][xB]->getValue() == 'R') && !isFirstLineInstance)
			{
				return true;
			}
			else if (this->_board[y][xB]->getValue() != '#' && !isFirstLineInstance)
			{
				isFirstLineInstance = true;
			}
		}

		isFirstLineInstance = false;
		for (int y = yB + 1; y < 8; y++)
		{
			if ((this->_board[y][xB]->getValue() == 'Q' || this->_board[y][xB]->getValue() == 'R') && !isFirstLineInstance)
			{
				return true;
			}
			else if (this->_board[y][xB]->getValue() != '#' && !isFirstLineInstance)
			{
				isFirstLineInstance = true;
			}
		}

		//horizontal
		isFirstLineInstance = false;
		for (int x = xB - 1; x >= 0; x--)
		{
			if ((this->_board[yB][x]->getValue() == 'Q' || this->_board[yB][x]->getValue() == 'R') && !isFirstLineInstance)
			{
				return true;
			}
			else if (this->_board[yB][x]->getValue() != '#' && !isFirstLineInstance)
			{
				isFirstLineInstance = true;
			}
		}

		isFirstLineInstance = false;
		for (int x = xB + 1; x < 8; x++)
		{
			if ((this->_board[yB][x]->getValue() == 'Q' || this->_board[yB][x]->getValue() == 'R') && !isFirstLineInstance)
			{
				return true;
			}
			else if (this->_board[yB][x]->getValue() != '#' && !isFirstLineInstance)
			{
				isFirstLineInstance = true;
			}
		}

		//checking pawn black
		if ((yB-1 > 0 && xB +1 < 8) && _board[yB - 1][xB + 1]->getValue() == 'P' )
		{
			return true;
		}
		else if ((yB - 1 > 0 && xB - 1 > 0) && _board[yB - 1][xB - 1]->getValue() == 'P')
		{
			return true;
		}
		//checking knight black
		if ((yB + 2 < 8 && xB + 2 < 8) && _board[yB + 2][xB + 1]->getValue() == 'N')
		{
			return true;
		}
		else if ((yB + 1 < 8 && xB + 2 < 8) && _board[yB + 1][xB + 2]->getValue() == 'N')
		{
			return true;
		}
		else if ((yB + 2 < 8 && xB - 1 > 0) && _board[yB + 2][xB - 1]->getValue() == 'N')
		{
			return true;
		}
		else if ((yB + 1 < 8 && xB - 2 > 0) && _board[yB + 1][xB - 2]->getValue() == 'N')
		{
			return true;
		}
		else if ((yB - 1 > 0 && xB - 2 > 0) && _board[yB - 1][xB - 2]->getValue() == 'N')
		{
			return true;
		}
		else if ((yB - 2 > 0 && xB - 1 > 0) && _board[yB - 2][xB - 1]->getValue() == 'N')
		{
			return true;
		}
		else if ((yB - 2 > 0 && xB + 1 < 8) && _board[yB - 2][xB + 1]->getValue() == 'N')
		{
			return true;
		}
		else if ((yB-1> 0 && xB + 2 < 8) && _board[yB - 1][xB + 2]->getValue() == 'N')
		{
			return true;
		}	
	}
	return false;
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
	if ((src->isPieceWhite() != dst->isPieceWhite()) && (dst->getValue() != '#'))
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
