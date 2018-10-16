#include "mineTile.h"
#include "drawing.h"

MineTile::MineTile()
{
	_clicked = false;	
	_bomb = false;	
	_flagged = false; 

	_count = 0;	

	LoadImage("images/minesweeper_tiles.png", 32, 32);

	image()->index = (0);
	image()->speed = (0);
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

void MineTile::RevealTile()
{
	image()->index = (9);
}

bool MineTile::clicked()
{
	return _clicked;
}

bool MineTile::flagged()
{
	return _flagged;
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
	if (_flagged) return;

	_clicked = c;
	// Update image
	if (_clicked) {
		if (_bomb) {
			image()->index = (7);
		} else if (_count > 0) {
			switch (_count) {
				case 1: image()->index = (3); break;
				case 2: image()->index = (4); break;
				case 3: image()->index = (5); break;
				case 4: image()->index = (6); break;
				case 5: image()->index = (10); break;
				case 6: image()->index = (11); break;
				case 7: image()->index = (12); break;
				case 8: image()->index = (13); break;
				default: std::cout << "Error: Invalid count on mine tile" << std::endl;
			}
		} else image()->index = (1);
	} else {
		image()->index = (0);
	}
}

void MineTile::SetFlagged(bool f)
{
	if (!_clicked) {
		_flagged = f;
		if (_flagged) {
			image()->index = (2);
		} else {
			image()->index = (0);
		}
	}
}

void MineTile::SetBomb(bool b)
{
	_bomb = b;
}

void MineTile::SetCount(int c)
{
	_count = c;
}

