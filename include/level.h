#pragma once

#include "types.h"
#include "entity.h"

class Level
{
public:
	Level();
	Level(std::string levelName);

	~Level();

	void SetFileName(std::string levelName);
	void SaveToFile();
	void LoadFromFile(std::string levelName);

private:

	std::string _name;

	eVector _objectList;
};
