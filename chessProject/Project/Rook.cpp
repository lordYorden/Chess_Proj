#include "Rook.h"
#define BLACK 'r'
#define WHITE 'R'
Rook::Rook(int x,int y, bool isWhite) :
	Piece(x,y, isWhite)
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
int Rook::isLegal(Piece* board[8][8], std::string& dst)
{
	int answer = 0;
	int y = dst[1] - '1';
	int x = dst[0] - 'a';
	std::cout << board[y][x]->getValue() << std::endl;;
	std::cout << board[this->_position[0]][this->_position[1]]->getValue() << std::endl;
	if ((dst[0] > 'h' || dst[0] < 'a') || (dst[1] < '1' || dst[1] > '8'))answer = 5;
	else if (board[this->_position[0]][this->_position[1]]->getValue() == '#') answer = 2;
	else if (x == this->getPositionX() && y == this->getPositionY()) answer = 7;
	else if (board[y][x]->getValue() != '#' && this->_isWhite == board[y][x]->isPieceWhite())answer = 3;
	else if ((this->_position[0] != y && this->_position[1] != x) || this->inWay(board, dst))answer = 6;
	else answer = 0;
	return answer;
}

bool Rook::inWay(Piece* board[8][8], std::string& dst)
{
	bool answer = false;
	if (this->_position[0] == dst[1] - '1') //checking horzontally
	{
		if (dst[0] - 'a' > this->_position[1])
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
		else
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
		if (dst[1] - '1' > this->_position[0]) //checking forwards
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
			for (int i = this->_position[0]-1  ; i > dst[1] - '1' && !answer; i--) //checking checking backwards
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

