#pragma once

#include "types.h"
#include "entity.h"
#include "entityCollection.h"

#include <map>

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

	void SaveToFile();
	void SaveLevel();	// NEW Save level

	bool LoadFromFile();
	bool LoadLevel();	// NEW Load level

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

	// @todo: maybe for level position later on, for multiple levels?
	int _lx;
	int _ly;
};
