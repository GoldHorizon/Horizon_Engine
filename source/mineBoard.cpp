#include "mineBoard.h"
#include "drawing.h"
#include "engineMethods.h"

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

void MineBoard::HandleEvents(SDL_Event* e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN) {
		int mx, my; 
		SDL_GetMouseState(&mx, &my);

		Vec2<int> coords = ScreenToWorld(mx, my);

		mx = coords.x;
		my = coords.y;

		mx -= static_cast<int>(Entity::x());
		my -= static_cast<int>(Entity::y());

		if (mx >= 0 && mx < _boardWidth * 32 && my >= 0 && my < _boardHeight * 32) {
			mx /= 32;
			my /= 32;

			//std::cout << mx << " " << my << std::endl;

			ClickTile(mx, my);
		}
	}
}

void MineBoard::Update()
{
	//if (_board != nullptr)
	//{
	//	for (int j = 0; j < _boardHeight; j++) {
	//		for (int i = 0; i < _boardWidth; i++) {
	//			//std::cout << "::: " << xOffset << std::endl;
	//			GetTile(i, j).Update();
	//		}
	//	}
	//}
}

void MineBoard::Render(float interpolation, int xOffset, int yOffset)
{
	if (_board != nullptr)
	{
		for (int j = 0; j < _boardHeight; j++) {
			for (int i = 0; i < _boardWidth; i++) {
				//std::cout << "::: " << xOffset << std::endl;
				GetTile(i, j).Render(interpolation, Entity::x() + xOffset + (i * 32), Entity::y() + yOffset + (j * 32));
			}
		}

		DrawText("Test", TextQuality::SHADED, defaultFont, 8, 8, TextAlignment::ALIGN_LEFT, {255, 255, 255});
	}
}

void MineBoard::CreateBoard(int sizex, int sizey)
{
	// Clear the board if it already exists
	ClearBoard();

	// Create new board
	_boardWidth = sizex;
	_boardHeight = sizey;

	_board = new MineTile [_boardWidth * _boardHeight]; // Create tile array
}

void MineBoard::GenerateBombs(int startx, int starty)
{
	std::srand(time(NULL));

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
}

void MineBoard::SetTileCounters()
{
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

void MineBoard::ClickTile(int x, int y)
{
	GetTile(x, y).SetClicked(true);
	
	if (GetTile(x, y).bomb()) {

	}
	else if (GetTile(x, y).count() == 0) {
		// Check all surrounding tiles
		for (int j = y - 1; j <= y + 1; j++) {
			for (int i = x - 1; i <= x + 1; i++) {
				if (i >= 0 && i < _boardWidth && j >= 0 && j < _boardHeight
					&& GetTile(i, j).clicked() == false)
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

void MineBoard::InitTestBoard(int startx, int starty, int sizex, int sizey)
{
	CreateBoard(sizex, sizey);
	GenerateBombs(startx, starty);
	SetTileCounters();
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

int MineBoard::width()
{
	return _boardWidth;
}

int MineBoard::height()
{
	return _boardHeight;
}

