#include "../include/level.h"
#include "file.h"

#include <iostream>

Level::Level() : Level("")
{
}

Level::Level(std::string levelName) :
	_name(levelName)
{
}

Level::~Level()
{

}

void Level::SetFileName(std::string levelName)
{
	if (levelName != "")
		_name = levelName;
	else
		std::cout << "Invalid level name being set" << std::endl;
}

std::string Level::GetFileName()
{
	return _name;
}

void Level::SaveToFile()
{

}

void Level::LoadFromFile()
{

}

eVector* Level::GetObjectList()
{
	return &_objectList;
}
