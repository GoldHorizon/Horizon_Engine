#pragma once

#include "types.h"
#include "entity.h"
#include "entityCollection.h"

class Level
{
public:
	Level();
	Level(std::string levelName);

	~Level();

	void SetFileName(std::string levelName);
	std::string GetFileName();
	void SaveToFile();
	void LoadFromFile();

	EntityCollection* GetObjectList();

private:

	std::string _name;

	//eVector _objectList;
	EntityCollection _objectList;
};
