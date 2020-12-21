#include "Knight.h"

#pragma once

Knight::Knight(std::string& place, bool isWhite):
	Piece(place, isWhite)
{

}

Knight::~Knight()
{
}

int Knight::isLegal(Piece*& board, std::string dst)
{
	//todo
}
