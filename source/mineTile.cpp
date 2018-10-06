#include "mineTile.h"
#include "drawing.h"

MineTile::MineTile()
{
	_clicked = false;	
	_bomb = false;	
	_count = 0;	

	LoadImage("images/minesweeper_tiles.png", 32, 32);

	image()->SetIndex(0);
	image()->SetSpeed(0);
}

MineTile::~MineTile()
{

}

void MineTile::HandleEvents(SDL_Event* e)
{

}

void MineTile::Update()
{

}

//void MineTile::UpdateTile()
//{
//
//}

bool MineTile::clicked()
{
	return _clicked;
}

bool MineTile::bomb()
{
	return _bomb;
}

int  MineTile::count()
{
	return _count;
}

void MineTile::SetClicked(bool c)
{
	_clicked = c;
	// Update image
	if (_clicked) {
		if (_bomb) {
			image()->SetIndex(7);
		} else if (_count > 0) {
			switch (_count) {
				case 1: image()->SetIndex(3); break;
				case 2: image()->SetIndex(4); break;
				case 3: image()->SetIndex(5); break;
				case 4: image()->SetIndex(6); break;
				case 5: image()->SetIndex(10); break;
				case 6: image()->SetIndex(11); break;
				case 7: image()->SetIndex(12); break;
				case 8: image()->SetIndex(13); break;
				default: std::cout << "Error: Invalid count on mine tile" << std::endl;
			}
		} else image()->SetIndex(1);
	} else {
		image()->SetIndex(0);
	}
}

void MineTile::RevealTile()
{
	image()->SetIndex(9);
}

void MineTile::SetBomb(bool b)
{
	_bomb = b;
}

void MineTile::SetCount(int c)
{
	_count = c;
}

