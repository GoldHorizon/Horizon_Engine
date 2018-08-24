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

EntityCollection* Level::GetObjectList()
{
	return &_objectList;
}
