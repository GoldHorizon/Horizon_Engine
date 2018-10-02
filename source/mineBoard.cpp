#include "mineBoard.h"

#include <iostream>
#include <cstdlib>
#include <time.h>

void MineBoard::InitTestBoard(int startx, int starty)
{
	std::srand(time(NULL));

	for (int j = 0; j < BOARD_HEIGHT; j++) {
		for (int i = 0; i < BOARD_WIDTH; i++) {
			int num = static_cast<int>(rand() % 5);

			if (num == 0 
				&& i != startx
			   	&& j != starty)	_testBoard[i][j] = '*';
			else				_testBoard[i][j] = '.';
		}
	}

	for (int j = 0; j < BOARD_HEIGHT; j++) {
		for (int i = 0; i < BOARD_WIDTH; i++) {
			if (_testBoard[i][j] == '.') {
				int minx, miny, maxx, maxy;
				if (i == 0) 				minx = i; else minx = i - 1; 
				if (j == 0) 				miny = j; else miny = j - 1; 
				if (i == BOARD_WIDTH - 1)  	maxx = i; else maxx = i + 1; 
				if (j == BOARD_HEIGHT - 1) 	maxy = j; else maxy = j + 1; 

				int count = 0;
				for (int yy = miny; yy <= maxy; yy++) {
					for (int xx = minx; xx <= maxx; xx++) {
						if (_testBoard[xx][yy] == '*') count++;
					}
				}

				if (count > 0) _testBoard[i][j] = static_cast<char>(count + 48);
			}
		}
	}
}

void MineBoard::PrintTestBoard()
{
	for (int j = 0; j < BOARD_HEIGHT; j++) {
		for (int i = 0; i < BOARD_WIDTH; i++) {
			std::cout << _testBoard[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
