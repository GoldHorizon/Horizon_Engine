#include "../include/level.h"
#include "file.h"
#include "types.h"
#include "engineMethods.h"

#include <iostream>

Level::Level() : Level("")
{
}

Level::Level(std::string levelName)
{
	if (levelName != "")
		SetFileName(levelName);
}

Level::~Level()
{

}

void Level::SetFileName(std::string levelName)
{
	if (levelName != "")
		_name = levelName;
	else
		std::cout << "Error: Invalid level name being set" << std::endl;
}

std::string Level::GetFileName()
{
	return _name;
}

void Level::SaveToFile()
{
	File levelFile;
	
	levelFile.OpenFile(_name, false, true);

	sVector* svp = levelFile.GetDataVector();

	for (int i = 0; i < GetCount(); i++)
	{
		svp->push_back(GetByIndex(i)->Serialize());
	}

	levelFile.WriteFileData();
	levelFile.CloseFile();
}

bool Level::LoadFromFile()
{
	bool success = false;

	File levelFile;

	levelFile.OpenFile(_name);

	if (!levelFile.IsOpen())
	{
		std::cout << "Error: Trying to load level file from non-existent level" << std::endl;
		return false;
	}
	
	ClearEntities();

	sVector* svp = levelFile.GetDataVector();
	levelFile.ReadFileAll();
	//levelFile.PrintData();

	for (int i = 0; i < svp->size(); i++)
	{
		Entity* obj = nullptr;
		obj = CreateSerializedObject((*svp)[i]);
		if (obj == nullptr)
			std::cout << "Error: Could not create serialized object from string " << i << " (returned -1 to playing.cpp)" << std::endl;
		else
		{
			AddEntity(obj);
		}
	}

	levelFile.CloseFile();
	success = true;

	return success;
}

void Level::AddEntity(Entity* obj)
{
	//AddEntity(obj);
	//
	EntityCollection::AddEntity(obj);

	const SDL_Point p = {obj->x(), obj->y()};

	_pointList.insert(pePair(p, obj));
}

void Level::AddEntity(Entity* obj, int x, int y)
{
	obj->SetPosition(x, y);
	AddEntity(obj);
}

void Level::RemoveEntity(Entity* obj)
{
	// @Todo: if needed
}

void Level::RemoveEntity(int index)
{
	Entity* ep = GetByIndex(index);
	if (ep != nullptr)
	{
		peMap::iterator it;

		SDL_Point point = {ep->x(), ep->y()};
		it = _pointList.find(point);

		if (it != _pointList.end())
			_pointList.erase(it);

		RemoveByIndex(index);
	}
}

void Level::RemoveEntity(SDL_Point point)
{
	RemoveEntity(point.x, point.y);
}

void Level::RemoveEntity(int x, int y)
{
	Entity* ep = nullptr;
	Entity* temp;
	int index;
	for (index = 0; index < GetCount(); index++)
	{
		temp = GetByIndex(index);
		if (temp->x() == x && temp->y() == y)
		{
			ep = temp;
			break;
		}
	}

	if (ep != nullptr && index < GetCount())
	{
		peMap::iterator it;

		SDL_Point point = {ep->x(), ep->y()};
		it = _pointList.find(point);

		if (it != _pointList.end())
			_pointList.erase(it);

		RemoveByIndex(index);
	}
}

void Level::RemoveLastEntity()
{
	int count;

	RemoveByIndex(count - 1);
}


bool Level::CheckPoint(int x, int y)
{
	peMap::iterator it = _pointList.find(SDL_Point {x, y});

	return (it != _pointList.end());
}
