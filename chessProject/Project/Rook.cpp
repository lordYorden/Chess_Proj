#include "Rook.h"
#define BLACK 'r'
#define WHITE 'R'
Rook::Rook(std::string& place, bool isWhite) :
	Piece(place, isWhite)
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
int Rook::isLegal(Piece*& board, std::string& dst)
{
	int answer = 0;
	if (dst[0] == this->getPositionX() + 97 && dst[1] == this->getPositionY() + 48) answer = 7;
	else if (dst[0] != this->getPositionX() + 97 || dst[1] != this->getPositionY()+48)answer = 6;
	//CONTINUE
	

}
