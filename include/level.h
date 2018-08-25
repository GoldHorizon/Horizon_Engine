#pragma once

#include "types.h"
#include "entity.h"
#include "entityCollection.h"

#include <map>

class Level : public EntityCollection
{
public:
	Level();
	Level(std::string levelName);

	~Level();

	void SetFileName(std::string levelName);
	std::string GetFileName();
	void SaveToFile();
	void LoadFromFile();

	void AddEntity(Entity* obj);
	void AddEntity(Entity* obj, int x, int y);
	
	void RemoveEntity(Entity* obj);
	void RemoveEntity(int index);
	void RemoveEntity(SDL_Point point);
	void RemoveEntity(int x, int y);
	void RemoveLastEntity();

	//EntityCollection* GetObjectList();

private:
	std::string _name;

	peMap _pointList;
};
