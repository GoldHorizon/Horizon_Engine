#pragma once

#include <string>
#include <vector>

#include "../include/entity.h"

typedef std::vector<Entity*> eVector;

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
