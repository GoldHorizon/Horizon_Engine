#include "mineBoard.h"

#include <iostream>
#include <cstdlib>
#include <time.h>

MineBoard::MineBoard()
{
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

	_board = new MineTile [_boardWidth * _boardHeight]; // Create tile array

	// Generate bombs
	for (int j = 0; j < _boardHeight; j++) {
		for (int i = 0; i < _boardWidth; i++) {
			int num = static_cast<int>(rand() % 5);

			if (num == 0)	{
				GetTile(i, j).SetBomb(true); // Set tile to have bomb
			}
			else {
				GetTile(i, j).SetBomb(false); // Set tile to be clear
			}
		}
	}

	// Clear starting position(s) (Should ALWAYS happen)
	if (startx >= 0 && startx < _boardWidth && starty >= 0 && starty < _boardHeight) {
		for (int j = starty - 1; j <= starty + 1; j++) {
			for (int i = startx - 1; i <= startx + 1; i++) {
				if (i >= 0 && i < _boardWidth
				 && j >= 0 && j < _boardHeight)
					
					GetTile(i, j).SetBomb(false); // Set tile to be clear
			}
		}
	}
	else {
		std::cout << "Error: Invalid starting position of minesweeper board!" << std::endl;
	}

	// Set adjacent bomb count of each tiles
	for (int j = 0; j < _boardHeight; j++) {
		for (int i = 0; i < _boardWidth; i++) {
			if (GetTile(i, j).bomb() == false) {
				int minx, miny, maxx, maxy;
				if (i == 0) 				minx = i; else minx = i - 1; 
				if (j == 0) 				miny = j; else miny = j - 1; 
				if (i == _boardWidth - 1)  	maxx = i; else maxx = i + 1; 
				if (j == _boardHeight - 1) 	maxy = j; else maxy = j + 1; 

				int count = 0;
				for (int yy = miny; yy <= maxy; yy++) {
					for (int xx = minx; xx <= maxx; xx++) {
						if (GetTile(xx, yy).bomb()) count++;
					}
				}

				if (count > 0) GetTile(i, j).SetCount(count);
			}
		}
	}
}

void MineBoard::PrintTestBoard()
{
	for (int j = 0; j < _boardHeight; j++) {
		for (int i = 0; i < _boardWidth; i++) {
			if (GetTile(i, j).bomb())
				std::cout << "*";
			else if (GetTile(i, j).count() == 0)
				std::cout << ".";
			else
				std::cout << GetTile(i, j).count();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void MineBoard::ClickTile(int x, int y)
{
	GetTile(x, y).SetClicked(true);
	
	if (GetTile(x, y).count() == 0) {
		for (int j = y - 1; j <= y + 1; j++) {
			for (int i = x - 1; i <= x + 1; i++) {
				if (i >= 0 && i < _boardWidth && j >= 0 && j < _boardHeight
					&& GetTile(i, j).clicked() == false && GetTile(i, j).count() == 0)
					ClickTile(i, j);
			}
		}
	}
}

void MineBoard::ClearBoard()
{
	if (_board != nullptr) delete [] _board;
}

MineTile& MineBoard::GetTile(int x, int y)
{
	return _board[_boardWidth * y + x];
}

int MineBoard::width()
{
	return _boardWidth;
}

int MineBoard::height()
{
	return _boardHeight;
}

