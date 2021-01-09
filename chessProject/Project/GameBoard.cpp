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
#define CHECKING 1
#define VALID 0
#define CHECKED 4
#define MATE 8
#define ISNTFREE 2
#define MAX 8
#define MIN 0
GameBoard::GameBoard():
	_isWhiteTurn(true)
{
	initBoard();
	//king black and king white default values
	this->_blackKingPlace = "d8";
	this->_whiteKingPlace = "d1";
	//review: you can deduct the default values from the string "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0" or from init board.
}

GameBoard::~GameBoard()
{
	//delete[] &this->_board;
	//review: here you need to delete all data from the board (not like this) 
}
/*
* fucntion that makes a move operation, eat or every other operation you could imagine in chess
* input: the string setn from frontend with the src cell and dst cell
* output: opcode 
*/
int GameBoard::move(std::string& move)
{
	std::string playerStr = move.substr(0, 2); //src player place
	std::string dst = move.substr(2, 2); //dst player place
	bool isEat = false;
	int opCode = 0;
	std::cout << "sep: " << playerStr << ", " << dst << std::endl;
	Piece* srcPlayer = placeToPiece(playerStr); //getting the piece in the src place
	Piece* dstPlayer = placeToPiece(dst); //getting the piece value in the dst place
	Piece* nullPlayer = nullptr; //for eating later
	std::string oldWhiteKingPlace = this->_whiteKingPlace; //saving original hwite king values
	std::string oldBlackKingPlace = this->_blackKingPlace;
	
	if (srcPlayer->isPieceWhite() == this->_isWhiteTurn) //if the src piece is matching the current turn
	{
		opCode = srcPlayer->isLegal(this->_board, dst); //getting opcode from islegal
		if (opCode == 0) //if its a valid move
		{
			if (srcPlayer->getValue() == 'k' || srcPlayer->getValue() == 'K') //if its the king, we update the class fields
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

			if (dstPlayer->getValue() == 'k' || dstPlayer->getValue() == 'K') //if we managed to eat the king the game will ned
				/*
				* 
				* NOTE: sometime the player is in mate, and he cannot escape it or avoid it, so the
				game would be stuck on player's turn and the player should stop playing by himself
				because we didn't check checkmate
				*/
			{
				opCode = MATE;
				return opCode;
			}
			isEat = checkForEat(srcPlayer, dstPlayer); //we're checking if an eat occurs
			if (isEat)
			{
				nullPlayer = new NullPiece(*dstPlayer); //making a null piece with dstPlayers fields
				this->_board[dstPlayer->getPositionY()][dstPlayer->getPositionX()] = nullPlayer; //setting the dstPlayers position to the nullPiece on the board
				swap(srcPlayer, nullPlayer);//swapping between src and null
			}
			else
			{
				swap(srcPlayer, dstPlayer); //if there wasn't an eating operation,switch between src and dst
			}
			std::cout << this->toStringBoard() << std::endl;

			if (isThreatened(!this->_isWhiteTurn) && !isThreatened(this->_isWhiteTurn)) //if we made check but didn't get ourselves into check
			{
				opCode = CHECKING;
			}
			else if (isThreatened(this->_isWhiteTurn)) //if we are threatened by a certain move
			{
				opCode = CHECKED;
				//if we were threatened we need to revert the move we already did before
				if (isEat) //if we chose to eat before
				{
					swap(srcPlayer, nullPlayer); //restoring src player to his original position
					this->_board[dstPlayer->getPositionY()][dstPlayer->getPositionX()] = dstPlayer; //restoring eaten  player
					//delete nullPlayer;
				}
				else
				{
					swap(dstPlayer, srcPlayer); //just swapping places
				}

				if (srcPlayer->getValue() == 'k' || srcPlayer->getValue() == 'K') //if we reverted a king moevement
				{
					if (srcPlayer->isPieceWhite()) //we update its place in the class field
					{
						this->_whiteKingPlace = oldWhiteKingPlace;
					}
					else
					{
						this->_blackKingPlace = oldBlackKingPlace;
					}
				}
			}
			if (opCode == VALID || opCode == CHECKING || opCode == MATE) //if there was a valid operation, we flip the turn
			{
				flipTurn();
			}
		}
	}
	else
	{
		opCode = ISNTFREE;
	}
	return opCode;
}
/*
* prints the board
* (upside down, easy for debugging)
*/

std::string GameBoard::toStringBoard()
{
	std::string boardStr = "";
	for (int i = 7; i >= MIN; i--)
	{
		for (int j = MIN; j < MAX; j++)
		{
			boardStr += this->_board[i][j]->getValue();
		}
		boardStr += '\n';
	}
	return boardStr;
}
/*
* A function that checks if a black/white king is threatened, by checking for a threat in his diagonals,lines, and frame
* input: what king to check
* output: true if threatened false if not
*/
bool GameBoard::isThreatened(bool isCheckingWhite)
{
	int xB = _blackKingPlace[0] - 'a';
	int yB = _blackKingPlace[1] - '1';
	int xW = _whiteKingPlace[0] - 'a';
	int yW = _whiteKingPlace[1] - '1';
	std::cout << _board[yB][xB]->getValue() << _board[yW][xW]->getValue() << std::endl;

	bool isFirstDiagonalInstance = false;
	bool isFirstLineInstance = false;
	if (isCheckingWhite) //if we want to check the white king
	//review: you can use the code you already wrote of each piece, and test with it all the pieces on the board.
	//as consequence, the code turn out to be complicated and hard to follow.
	//forther more, if you writing in this manner, please pay attention that actions are very similar for balck and white, 
	//so even here you can reuse code.
	{
		//checking white diagonals
		for (int x = xW + 1, y = yW + 1; x < MAX && y < MAX; x++, y++) //checking white upper right diagonal
		{
			if ((this->_board[y][x]->getValue() == 'q' || this->_board[y][x]->getValue() == 'b') && !isFirstDiagonalInstance) //checking if our first instance is either a queen or a bishop,if so the king is threatened
			{
				return true;
			}
			else if (this->_board[y][x]->getValue() != '#' && !isFirstDiagonalInstance) //turning on our first instance flag if its not a queen or bishop
			{
				isFirstDiagonalInstance = true;
			}
		}

		isFirstDiagonalInstance = false; //resetting this var
		for (int x = xW - 1, y = yW - 1; x >= MIN && y >= MIN; x--, y--) //checking hwite king lower left diagonal
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
		for (int x = xW - 1, y = yW + 1; x >= MIN && y < MAX; x--, y++) //checking upper left diagonal
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
		for (int x = xW + 1, y = yW - 1; x < MAX && y >= MIN; x++, y--) //checking lower right diagonal
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
		for (int y = yW - 1; y >= MIN; y--) //checking vertical lines down
		{
			if ((this->_board[y][xW]->getValue() == 'q' || this->_board[y][xW]->getValue() == 'r') && !isFirstLineInstance)//if our frst instance is a rook or queen he is thereatened
			{
				return true;
			}
			else if (this->_board[y][xW]->getValue() != '#' && !isFirstLineInstance) //turning on our first instance flag
			{
				isFirstLineInstance = true;
			}
		}

		isFirstLineInstance = false;
		for (int y = yW + 1; y < MAX; y++) //checking vertical up
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
		for (int x = xW - 1; x >= MIN; x--) //cehcking horizontal left
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
		for (int x = xW + 1; x < MAX; x++) //checking horizontal right
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
		std::cout << "Pawn Debugging: " << _board[yW + 1][xW + 1]->getValue() << _board[yW + 1][xW - 1]->getValue() << std::endl;
		//checking pawn white
		if ((yW +1  < MAX && xW + 1 < MAX) && _board[yW + 1][xW + 1]->getValue() == 'p') //checking for pawn values
		{
			return true;
		}
		else if ((yW + 1 < MAX && xW - 1 >= MIN) && _board[yW + 1][xW - 1]->getValue() == 'p')
		{
			return true;
		}
		//checking knights optional position to threat the king
		if ((yW + 2 < MAX && xW + 2 < MAX) && _board[yW + 2][xW + 1]->getValue() == 'n')
		{
			return true;
		}
		else if ((yW + 1 < MAX && xW + 2 < MAX) && _board[yW + 1][xW + 2]->getValue() == 'n')
		{
			return true;
		}
		else if ((yW + 2 < MAX && xW - 1 >= MIN) && _board[yW + 2][xW - 1]->getValue() == 'n')
		{
			return true;
		}
		else if ((yW + 1 < MAX && xW - 2 >= MIN) && _board[yW + 1][xW - 2]->getValue() == 'n')
		{
			return true;
		}
		else if ((yW - 1 >= MIN && xW - 2 >= MIN) && _board[yW - 1][xW - 2]->getValue() == 'n')
		{
			return true;
		}
		else if ((yW - 2 >= MIN && xW - 1 >= MIN) && _board[yW - 2][xW - 1]->getValue() == 'n')
		{
			return true;
		}
		else if ((yW - 2 >= MIN && xW + 1 < MAX) && _board[yW - 2][xW + 1]->getValue() == 'n')
		{
			return true;
		}
		else if ((yW - 1 >= MIN && xW + 2 < MAX) && _board[yW - 1][xW + 2]->getValue() == 'n')
		{
			return true;
		}
		for (int i = yW - 1, count1 = 0; count1 < 3; count1++, i++) //checking if a king is found in a frame
		{
			for (int j = xW - 1, count2 = 0; count2 < 3; count2++, j++)
			{
				if ((j < MAX && j >= MIN) && (i < MAX && i >= MIN)) //if its a legal place
				{
					if (_board[i][j]->getValue() == 'k') 
					{
						return true;
					}
				}
			}
		}

		
	}
	else //checking the balck king
	{
		//checking Black diagonals
		isFirstDiagonalInstance = false;
		for (int x = xB + 1, y = yB + 1; x < MAX && y < MAX; x++, y++) //checking upper right diagonal
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
		for (int x = xB - 1, y = yB - 1; x >= MIN && y >= MIN; x--, y--) //checking lower left diagonal
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
		for (int x = xB - 1, y = yB + 1; x >= MIN && y < MAX; x--, y++) //checking upper left diagonal
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
		for (int x = xB + 1, y = yB - 1; x < MAX && y >= MIN; x++, y--) //checking lower right diagonal
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
		for (int y = yB - 1; y >= MIN; y--) //checking vertcial down
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
		for (int y = yB + 1; y < MAX; y++) //checking vertical up
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
		for (int x = xB - 1; x >= MIN; x--) //checking horizontal right
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
		for (int x = xB + 1; x < MAX; x++) //checking horizontal left
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

		//checking pawn values that threat the king
		std::cout << "Pawn Debugging: " << _board[yB - 1][xB + 1]->getValue() << _board[yB -1 ][xB - 1]->getValue() << std::endl;
		if ((yB-1 >= MIN && xB +1 < MAX) && _board[yB - 1][xB + 1]->getValue() == 'P' )
		{
			return true;
		}
		else if ((yB - 1 >= MIN && xB - 1 > MIN) && _board[yB - 1][xB - 1]->getValue() == 'P')
		{
			return true;
		}
		//checking knight values the might oppose a threat to the black KING
		if ((yB + 2 < MAX && xB + 2 < MAX) && _board[yB + 2][xB + 1]->getValue() == 'N')
		{
			return true;
		}
		else if ((yB + 1 < MAX && xB + 2 < MAX) && _board[yB + 1][xB + 2]->getValue() == 'N')
		{
			return true;
		}
		else if ((yB + 2 < MAX && xB - 1 >= MIN) && _board[yB + 2][xB - 1]->getValue() == 'N')
		{
			return true;
		}
		else if ((yB + 1 < MAX && xB - 2 >= MIN) && _board[yB + 1][xB - 2]->getValue() == 'N')
		{
			return true;
		}
		else if ((yB - 1 >= MIN && xB - 2 >= MIN) && _board[yB - 1][xB - 2]->getValue() == 'N')
		{
			return true;
		}
		else if ((yB - 2 >= MIN && xB - 1 >= MIN) && _board[yB - 2][xB - 1]->getValue() == 'N')
		{
			return true;
		}
		else if ((yB - 2 >= MIN && xB + 1 < MAX) && _board[yB - 2][xB + 1]->getValue() == 'N')
		{
			return true;
		}
		else if ((yB-1 >= MIN && xB + 2 < MAX) && _board[yB - 1][xB + 2]->getValue() == 'N')
		{
			return true;
		}	
		for (int i = yB - 1, count1 = 0; count1 < 3; count1++, i++)
		{
			for (int j = xB - 1, count2 = 0; count2 < 3; count2++, j++) //if a white king is found in frame
			{
				if ((j < MAX && j >= MIN) && (i < MAX && i >= MIN))
				{
					if (_board[i][j]->getValue() == 'K')
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
/*
* this function inits the board with the pieces at the right place according to the gui
*/
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

	for (int i = 0; i < 8; i++) //initing pawns
	{
		this->_board[6][i] = new Pawn(i, 6, false);
		this->_board[1][i] = new Pawn(i, 1, true);
	}

	for (int i = 2; i < 6; i++) //initing nullpieces
	{
		for (int j = 0; j < 8; j++) //review: better to write '8' in a define - it is the size of the row/col in chess board
		{
			this->_board[i][j] = new NullPiece(j, i);
		}
	}

}
/*
* if an eat occurs return true, else false
* output: true/false
* input: src piece and dst piece
*/
bool GameBoard::checkForEat(Piece* src, Piece* dst) 
{
	if ((src->isPieceWhite() != dst->isPieceWhite()) && (dst->getValue() != '#'))
	{
		return true;
	}
	return false;
}
/*
* swaps board location between two pieces and the object data itself
* input: src piece and dst piece
* output: none
*/
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
/*
* returns the piece in place parameter
* input: place of piece to return
* output: piece to return
*/
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

void GameBoard::flipTurn() //turn management system. fli[s turn to matching one
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
