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
	if (dst[0] == this->getPositionX() + 97 && dst[1] == this->getPositionY() + 48) answer = 7;
	else if (dst[0] != this->getPositionX() + 97 || dst[1] != this->getPositionY() + 48) answer = 6;
	else if ((dst[0] > 'h' || dst[0] < 'a') || (dst[1] < '1' || dst[1] > '8'));
	//CONTINUE
	return 0;
}
