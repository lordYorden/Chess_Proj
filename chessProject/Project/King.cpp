#include "King.h"

King::King(int x,int y, bool isWhite) :
	Piece(x,y,isWhite)
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
int King::isLegal(Piece* board[8][8], std::string& dst)
{
	int answer = 0;
	int y = dst[1] - '1';
	int x = dst[0] - 'a';
	if ((dst[0] > 'h' || dst[0] < 'a') || (dst[1] < '1' || dst[1] > '8'))
	{
		answer = 5;
	}
	else if (board[this->_position[0]][this->_position[1]]->getValue() == '#')
	{
		answer = 2;
	}
	else if (x == this->getPositionX() && y == this->getPositionY())
	{
		answer = 7;
	}
	else if (board[y][x]->getValue() != '#' && this->_isWhite == board[y][x]->isPieceWhite())
	{
		answer = 3;
	}
	else if (!this->isValid(board,dst))
	{
		answer = 6;
	}
	else
	{
		answer = 0;
	}

	return answer;
}
bool King::isValid(Piece* board[8][8], std::string& dst)
{
	int y = dst[1] - '1';
	int x = dst[0] - 'a';
	for (int i = this->_position[0]-1,count1 = 0 ; count1 < 3; i++,count1++)
	{
		for (int j = this->_position[1] - 1,count2=0; count2 < 3; j++,count2++)
		{
			if (x == j && y == i)
			{
				return true;
			}
		}
	}
	return false;

}