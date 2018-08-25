#include "../include/level.h"
#include "file.h"
#include "types.h"
#include "engineMethods.h"

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
	File levelFile;
	
	levelFile.OpenFile(_name, false, true);

	sVector* svp = levelFile.GetDataVector();

	for (int i = 0; i < _objectList.GetCount(); i++)
	{
		svp->push_back(_objectList[i]->Serialize());
	}

	levelFile.WriteFileData();
	levelFile.CloseFile();
}

void Level::LoadFromFile()
{
	File levelFile;

	levelFile.OpenFile(_name);

	if (levelFile.IsOpen())
	{
		std::cout << "Error: Trying to load level file from non-existent level" << std::endl;
		return;
	}

	sVector* svp = levelFile.GetDataVector();
	levelFile.ReadFileAll();

	for (int i = 0; i < svp->size(); i++)
	{
		Entity* obj = nullptr;
		obj = CreateSerializedObject((*svp)[i]);
		if (obj == nullptr)
			std::cout << "Error: Could not create serialized object from string " << i << " (returned -1 to playing.cpp)" << std::endl;
		else
			_objectList.AddEntity(obj);
	}

	levelFile.CloseFile();
}

void Level::AddEntity(Entity* obj)
{
	_objectList.AddEntity(obj);

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
	Entity* ep = _objectList.GetByIndex(index);
	if (ep != nullptr)
	{
		peMap::iterator it;

		SDL_Point point = {ep->x(), ep->y()};
		it = _pointList.find(point);

		if (it != _pointList.end())
			_pointList.erase(it);

		_objectList.RemoveByIndex(index);
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
	for (index = 0; index < _objectList.GetCount(); index++)
	{
		temp = _objectList.GetByIndex(index);
		if (temp->x() == x && temp->y() == y)
		{
			ep = temp;
			break;
		}
	}

	if (ep != nullptr && index < _objectList.GetCount())
	{
		peMap::iterator it;

		SDL_Point point = {ep->x(), ep->y()};
		it = _pointList.find(point);

		if (it != _pointList.end())
			_pointList.erase(it);

		_objectList.RemoveByIndex(index);
	}
}

void Level::RemoveLastEntity()
{
	int count;

	_objectList.RemoveByIndex(count - 1);
}

EntityCollection* Level::GetObjectList()
{
	return &_objectList;
}
