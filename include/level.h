#pragma once

#include "types.h"
#include "entity.h"
#include "entityCollection.h"

#include <string>
#include <map>

const std::string LEVEL_FOLDER = "levels"; // Base folder for levels 

class Level : public EntityCollection
{
public:
	/*
	 * Constructors/Destructors
	 */
	Level();
	Level(std::string levelName);

	~Level();

	/*
	 * Class Methods
	 */
	void SetFileName(std::string levelName);
	std::string GetFileName();

	void SaveLevel();
	bool LoadLevel();
	void LoadEntity(std::string filePath, std::string fileName);

	void AddEntity(Entity* obj);
	void AddEntity(Entity* obj, int x, int y);
	
	void RemoveEntity(Entity* obj);
	void RemoveEntity(int index);
	void RemoveEntity(SDL_Point point);
	void RemoveEntity(int x, int y);
	void RemoveLastEntity();

	bool CheckPoint(int x, int y);

private:
	/*
	 * Private Attributes
	 */
	std::string _name;

	peMap _pointList;
};
