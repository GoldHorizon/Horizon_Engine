#include "mineBoard.h"

#include <iostream>
#include <cstdlib>
#include <time.h>

MineBoard::MineBoard()
{
	_testBoard = nullptr;
	_board = nullptr;

	_boardWidth = 0;
	_boardHeight = 0;
}

MineBoard::~MineBoard()
{
	ClearBoard();
}

void MineBoard::InitTestBoard(int startx, int starty, int sizex, int sizey)
{
	std::srand(time(NULL));

	// Clear the board if it already exists
	ClearBoard();

	// Create new board
	_boardWidth = sizex;
	_boardHeight = sizey;

	_testBoard = new char [_boardWidth * _boardHeight]; // Create tile array
	_board = new MineTile [_boardWidth * _boardHeight]; // Create tile array

	// Generate bombs
	for (int j = 0; j < _boardHeight; j++) {
		for (int i = 0; i < _boardWidth; i++) {
			int num = static_cast<int>(rand() % 5);

			if (num == 0)	{
				_testBoard[_boardWidth * j + i] = '*'; // Set tile to have bomb
				//_board[_boardWidth * j + i] = '*'; // Set tile to have bomb
			}
			else {
				_testBoard[_boardWidth * j + i] = '.'; // Set tile to be clear
				//_board[_boardWidth * j + i] = '.'; // Set tile to be clear
			}
		}
	}

	// Clear starting position(s) (Should ALWAYS happen)
	if (startx >= 0 && startx < _boardWidth && starty >= 0 && starty < _boardHeight) {
		for (int j = starty - 1; j <= starty + 1; j++) {
			for (int i = startx - 1; i <= startx + 1; i++) {
				if (i >= 0 && i < _boardWidth
				 && j >= 0 && j < _boardHeight)
					
					_testBoard[_boardWidth * j + i] = '.'; // Set tile to be clear
					//_board[_boardWidth * j + i] = '.'; // Set tile to be clear
			}
		}
	}
	else {
		std::cout << "Error: Invalid starting position of minesweeper board!" << std::endl;
	}

	// Set adjacent bomb count of each tiles
	for (int j = 0; j < _boardHeight; j++) {
		for (int i = 0; i < _boardWidth; i++) {
			//if (_board[_boardWidth * j + i] == '.') {
			if (_testBoard[_boardWidth * j + i] == '.') {
				int minx, miny, maxx, maxy;
				if (i == 0) 				minx = i; else minx = i - 1; 
				if (j == 0) 				miny = j; else miny = j - 1; 
				if (i == _boardWidth - 1)  	maxx = i; else maxx = i + 1; 
				if (j == _boardHeight - 1) 	maxy = j; else maxy = j + 1; 

				int count = 0;
				for (int yy = miny; yy <= maxy; yy++) {
					for (int xx = minx; xx <= maxx; xx++) {
						if (_testBoard[_boardWidth * yy + xx] == '*') count++;
						//if (_board[_boardWidth * yy + xx] == '*') count++;
					}
				}

				if (count > 0) _testBoard[_boardWidth * j + i] = static_cast<char>(count + 48);
				//if (count > 0) _board[_boardWidth * j + i] = static_cast<char>(count + 48);
			}
		}
	}
}

void MineBoard::PrintTestBoard()
{
	for (int j = 0; j < _boardHeight; j++) {
		for (int i = 0; i < _boardWidth; i++) {
			std::cout << _testBoard[_boardWidth * j + i];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void MineBoard::ClearBoard()
{
	if (_testBoard != nullptr) delete [] _testBoard;
}
