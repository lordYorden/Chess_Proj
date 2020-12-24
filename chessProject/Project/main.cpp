#include <iostream>
#include "GameBoard.h"

int main()
{
	int opCode = 0;
	GameBoard g = GameBoard();
	std::string move = "b1c3";
	std::cout << g.toStringBoard() << std::endl;
	opCode = g.move(move);
	std::cout << "op code is: " << opCode << std::endl;
	std::cout << g.toStringBoard() << std::endl;
	move = "a1c1";
	std::cout << g.toStringBoard() << std::endl;
	opCode = g.move(move);
	std::cout << "op code is: " << opCode << std::endl;
	std::cout << g.toStringBoard() << std::endl;
	
	return 0;
}