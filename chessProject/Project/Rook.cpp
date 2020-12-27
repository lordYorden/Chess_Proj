#include "Rook.h"
#define BLACK 'r'
#define WHITE 'R'
#define OUTRANGE 5
#define SAME 7
#define ISNTMINE 2
#define ISNTFREE 3
#define INVALID 6
/*
* rook c'tor,
*/
Rook::Rook(int x,int y, bool isWhite) : 
	Piece(x,y, isWhite) //inits x and y position and value matching the color
{
	if (this->_isWhite)
	{
		setValue(WHITE);
	}
	else
	{
		setValue(BLACK);
	}
}
/*
* function that checks if a rook's move is legal
* input: board with pieces, dst location
* output: opCode
*/
int Rook::isLegal(Piece* board[8][8], std::string& dst)
{
	int answer = 0;
	int y = dst[1] - '1';
	int x = dst[0] - 'a';
	std::cout << board[y][x]->getValue() << std::endl;;
	std::cout << board[this->_position[0]][this->_position[1]]->getValue() << std::endl;
	if ((dst[0] > 'h' || dst[0] < 'a') || (dst[1] < '1' || dst[1] > '8'))answer = OUTRANGE; //out of range
	else if (board[this->_position[0]][this->_position[1]]->getValue() == '#') answer = ISNTMINE; //isnt my piece
	else if (x == this->getPositionX() && y == this->getPositionY()) answer = SAME; //dst same as src
	else if (board[y][x]->getValue() != '#' && this->_isWhite == board[y][x]->isPieceWhite())answer = ISNTFREE; //cell isn't free, containing piece of same color
	else if ((this->_position[0] != y && this->_position[1] != x) || this->inWay(board, dst))answer = INVALID;//invalid movement
	else answer = 0;
	return answer;
}
/*
* function that checks if a piece is found in a way of a rook that wants to move to that location
* input: board of pieces, dst location
* output: true/false
*/
bool Rook::inWay(Piece* board[8][8], std::string& dst)
{
	bool answer = false;
	if (this->_position[0] == dst[1] - '1') //checking horizontally
	{
		if (dst[0] - 'a' > this->_position[1]) //if we need to chek left
		{
			for (int i = this->_position[1]+1; i < dst[0] - 'a' && !answer; i++) //checking forward
			{
				std::cout << "horizontalf" << std::endl;
				if ((board[this->_position[0]][i]->getValue() != '#'))
				{
					answer = true;
				}
			}
		}
		else //if we need to check right
		{
			for (int i = this->_position[1]-1; i > dst[0] - 'a' && !answer; i--) //checking backwards
			{
				std::cout << "horizontalb" << std::endl;
				if ((board[this->_position[0]][i]->getValue() != '#'))
				{
					answer = true;
				}
			}
		}
		
	}
	else
	{
		if (dst[1] - '1' > this->_position[0]) //checking vetically up
		{
			for (int i = this->_position[0]+1; i < dst[1] - '1' && !answer; i++)
			{
				std::cout << "vertical" << std::endl;
				if ((board[i][this->_position[1]]->getValue() != '#'))
				{
					answer = true;
				}
			}
		}
		else if(dst[1] - '1' < this->_position[0])
		{
			for (int i = this->_position[0]-1  ; i > dst[1] - '1' && !answer; i--) //checking verticall down
			{
				std::cout << "vertical" << std::endl;
				if ((board[i][this->_position[1]]->getValue() != '#') )
				{
					answer = true;
				}
			}
			
		}
		
	}
	return answer;


}

