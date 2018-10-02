#include "mineTile.h"

MineTile::MineTile()
{
	_clicked = false;	
	_bomb = false;	
	_count = 0;	
}

MineTile::~MineTile()
{

}

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
}

void MineTile::SetBomb(bool b)
{
	_bomb = b;
}

void MineTile::SetCount(int c)
{
	_count = c;
}

