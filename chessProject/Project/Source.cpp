/*
* used thair exemple for gui integration
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include "GameBoard.h"

using std::cout;
using std::endl;
using std::string;


void main()
{
	srand(time_t(NULL));

	
	Pipe p;
	int opCode = 0;
	GameBoard g = GameBoard(); //review: meaningful names are preferable
	bool isConnect = p.connect();
	
	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return;
		}
	}
	

	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0"); // just example...
	
	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
		
		// YOUR CODE
		/*strcpy_s(msgToGraphics, "YOUR CODE");*/ // msgToGraphics should contain the result of the operation

		///******* JUST FOR EREZ DEBUGGING ******/
		//int r = rand() % 10; // just for debugging......
		//msgToGraphics[0] = (char)(1 + '0');
		//msgToGraphics[1] = 0;
		///******* JUST FOR EREZ DEBUGGING ******/

		//integration itself
		std::cout << g.toStringBoard() << std::endl;
		opCode = g.move(msgFromGraphics);
		//make the opCode message graphics
		msgToGraphics[0] = opCode + '0';
		msgToGraphics[1] = 0;
		//print board info
		std::cout << opCode << std::endl;
		std::cout << g.toStringBoard() << std::endl;

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);   

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}