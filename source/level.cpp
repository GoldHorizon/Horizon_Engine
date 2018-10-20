#include "level.h"
#include "file.h"
#include "types.h"
#include "engineMethods.h"

#include <sys/stat.h>	// For stat structure of files to get access time
#include <dirent.h>		// For searching directory for files
#include <iostream>
#include <cassert>		// Finally start using assert?

#ifdef _WIN32
#include <windows.h>	// For creating directory in windows
#endif

Level::Level() : Level("")
{
}

Level::Level(std::string levelName)
{
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

	for (int i = GetCount() - 1; i >= 0 ; i--)
	{
		svp->push_back(GetByIndex(i)->Serialize());
	}

	levelFile.WriteFileData();
	levelFile.CloseFile();

	// DEBUG
	//SaveLevel();
}

void Level::SaveLevel()
{
	// Save level procedure:
	// 	1)	Create level folder (if nonexistent)
	// 	2)  Save level details in level file (level width? gamemode? camera? maybe for future use) 
	// 	3)  Save individual entity files (instead of all in one, for easier readability)

	// Create folder
	std::string thisLevelsFolder = "";
	std::string saveName = _name;

	// Make sure our folder name doesn't have a file extension (for legacy names?)
	unsigned int dot = _name.find('.');

	if (dot != std::string::npos) {
		saveName = _name.substr(0, dot);
	}

#ifdef _WIN32
	thisLevelsFolder = LEVEL_FOLDER + "\\" + saveName + "\\";

	// Level should not have any spaces in it
	if (thisLevelsFolder.find(' ') != std::string::npos) {
		std::cout << "Error: Can't save level with spaces in name" << std::endl;
		return;
	}

	// Windows API function
	CreateDirectory(thisLevelsFolder.c_str(), NULL);
#endif

	assert (thisLevelsFolder != "" && "Couldn't create level folder (OS not supported?)");

	//if (thisLevelsFolder == "") {	// Couldn't create folder, so exiting...
	//	std::cout << "Error: Couldn't create level folder! (OS not supported?)" << std::endl;
	//	return;
	//}

	// Save level file (skip for now?)

	// Save entity files
	File entityFile;

	for (int i = 0; i < GetCount(); i++)
	{
		auto ent = GetByIndex(i);

		// Saves entity files as ID number
		entityFile.OpenFile(thisLevelsFolder + std::to_string(ent->ID) + ".entity", false, true);
		
		// Write serialization string to file (eventually better formatted)
		entityFile.WriteFileLine(ent->SerializeFile());

		entityFile.CloseFile();
	}
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

	for (size_t i = 0; i < svp->size(); i++)
	{
		Entity* obj = nullptr;

		obj = CreateSerializedObject((*svp)[i]);

		//if (obj == nullptr)
		//	std::cout << "Error: Could not create serialized object from string " << i << " (returned -1 to playing.cpp)" << std::endl;
		//else
		//{
		//	AddEntity(obj);
		//}

		assert (obj != nullptr && "Could not create serialized object from string");
		
		AddEntity(obj);
	}

	levelFile.CloseFile();
	success = true;

	//LoadLevel();

	return success;
}

bool Level::LoadLevel()
{
	bool success = false;

	// Create folder
	std::string thisLevelsFolder = "";
	std::string loadName = _name;

	// Make sure our folder name doesn't have a file extension (for legacy names?)
	unsigned int dot = _name.find('.');

	if (dot != std::string::npos) {
		loadName = _name.substr(0, dot);
	}

	thisLevelsFolder = LEVEL_FOLDER + "/" + loadName + "/";

	// Begin looping through level directory
	DIR *directory;
	struct dirent *entry;
	
	directory = opendir(thisLevelsFolder.c_str());

	if (directory != NULL) {
		std::string filePath;
		std::string fileName;
		
		entry = readdir(directory);
		while (entry != NULL) {
			// Found entry in folder, deserialize the object
			fileName = std::string(entry->d_name);

			// If entry is referring to the '.' or '..' directories, ignore
			if (fileName == "." || fileName == "..") {
				//std::cout << "Not checking " << fileName << std::endl;
			} else {
				filePath = (thisLevelsFolder + fileName);
					
				// Deserialize objects here
				File entityFile;
				entityFile.OpenFile(filePath);

				Entity* obj = nullptr;
				
				// @Todo: Need to rework how entity string is read, for when formatting changes
				entityFile.ReadFileAll();
				sVector* svp = entityFile.GetDataVector();
				obj = CreateSerializedObject((*svp)[0]);

				assert (obj != nullptr && "Could not create serialized object from string");
				
				AddEntity(obj);
				entityFile.CloseFile();
			}

			entry = readdir(directory);
		}

		success = true;

		closedir(directory);
	} else {
		std::cout << "Error: Couldn't find level folder named " << thisLevelsFolder << " to load!" << std::endl;
	}

	return success;
}

void Level::AddEntity(Entity* obj)
{
	//AddEntity(obj);
	//
	EntityCollection::AddEntity(obj);

	const SDL_Point p = {(int)obj->x, (int)obj->y};

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

		SDL_Point point = {(int)ep->x, (int)ep->y};
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
		if (temp->x == x && temp->y == y)
		{
			ep = temp;
			break;
		}
	}

	if (ep != nullptr && index < GetCount())
	{
		peMap::iterator it;

		SDL_Point point = {(int)ep->x, (int)ep->y};
		it = _pointList.find(point);

		if (it != _pointList.end())
			_pointList.erase(it);

		RemoveByIndex(index);
	}
}

void Level::RemoveLastEntity()
{
	int count = GetCount();

	RemoveByIndex(count - 1);
}


bool Level::CheckPoint(int x, int y)
{
	peMap::iterator it = _pointList.find(SDL_Point {x, y});

	return (it != _pointList.end());
}
