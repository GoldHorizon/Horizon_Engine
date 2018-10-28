#include "level.h"
#include "file.h"
#include "types.h"
#include "engineMethods.h"

//#include <dirent.h>		// For searching directory for files
#include <sys/stat.h>	// For stat structure of files to get access time
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
	// Called in parent destructor
	//ClearEntities();
}

void Level::SetFileName(std::string levelName)
{
	_name = levelName;
}

std::string Level::GetFileName()
{
	return _name;
}

void Level::SaveLevel()
{
	// Save level procedure:
	// 	1)	Create level folder (if nonexistent)
	// 	1.5)	NEED TO DELETE ALL EXISTING ENTITY FILES (to account for deleted entities in editor)
	// 	2)  Save level details in level file (level width? gamemode? camera? maybe for future use) 
	// 	3)  Save individual entity files (instead of all in one, for easier readability)

	assert (_name != "" && "Tried saving level without filename!");

	if (_name == "") return;

	// Create folder
	std::string thisLevelsFolder = "";
	std::string saveName = _name;

	// Make sure our folder name doesn't have a file extension (for legacy names?)
	auto dot = _name.find('.');

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

	// Windows API functions
	CreateDirectory(thisLevelsFolder.c_str(), NULL);
#else
	assert(false && "Level saving not implemented on current OS!");
#endif

	assert (thisLevelsFolder != "" && "Couldn't create level folder (OS not supported?)");
	
	// Save level file (skip for now?)
	// ...
	
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

bool Level::LoadLevel()
{
	assert(_name != "" && "Tried saving level without filename!");

	if (_name == "") return false;

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

#ifdef _WIN32
	HANDLE fileHandle;
	WIN32_FIND_DATA fileData;

	fileHandle = FindFirstFile(std::string(thisLevelsFolder + "*").c_str(), &fileData);

	if (fileHandle == INVALID_HANDLE_VALUE) {
		//std::cout << "Error: Could not get a file handle using the directory " << thisLevelsFolder << std::endl;
		FindClose(fileHandle);
		return success;
	}
	
	// Remove all old entities, now that we found a folder with our new level
	ClearEntities();

	std::cout << "DIRECTORY CONTENTS:" << std::endl;
	do 
	{
		if (fileData.cFileName[0] == '.') continue;
		std::cout << fileData.cFileName << std::endl;

		LoadEntity(thisLevelsFolder + fileData.cFileName, fileData.cFileName);

	} while (FindNextFile(fileHandle, &fileData));

	assert(FindClose(fileHandle) && "Could not close the file handle when loading level");

	success = true;
#else
	assert(false && "Level loading not implemented on current OS!");
#endif
	
	if (!success)
		std::cout << "Error: Couldn't find level folder named " << thisLevelsFolder << " to load!" << std::endl;

	return success;
}

void Level::LoadEntity(std::string filePath, std::string fileName)
{
	// If entry is referring to the '.' or '..' directories, ignore
	if (fileName == "." || fileName == "..") {
		return;
	} else if (fileName.find(".entity") != std::string::npos) {
		// If we find an entity file, deserialize it. Else ignore.
		//
		int fileID = std::stoi(fileName.substr(0, fileName.find(".entity")));
			
		// Deserialize objects here
		File entityFile;
		entityFile.OpenFile(filePath);

		Entity* obj = nullptr;
		
		// @Todo: Need to rework how entity string is read, for when formatting changes
		entityFile.ReadFileAll();
		sVector* svp = entityFile.GetDataVector();
		obj = CreateSerializedObject((*svp)[0]);

		assert (obj != nullptr && "Could not create serialized object from string");

		obj->ID = fileID;
		
		AddEntity(obj);
		entityFile.CloseFile();
	}
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
	delete obj;
	_collection.remove(obj);
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
			ep = it->second;
			_pointList.erase(it);

		RemoveByIndex(index);
	}
}

void Level::RemoveLastEntity()
{
	int count = GetCount();

	RemoveByIndex(count - 1);
}

void Level::RemoveEntities(int x, int y)
{
	for (auto ep : _collection) {
		// If the entity has an image loaded...
		if (ep->image()->width() > 0) {
			vec2<int> e_pos;
			vec2<int> e_dim;

			// Get image position based on it's offset
			if (ep->image()->origin.x != 0 || ep->image()->origin.y != 0) {
				e_pos = { static_cast<int>(ep->x - ep->image()->origin.x), static_cast<int>(ep->y - ep->image()->origin.y) };
			} else {
				e_pos = { static_cast<int>(ep->x), static_cast<int>(ep->y) };

			}

			// Check if it's a sprite sheet or not...
			if (ep->image()->spriteDimensions().x > 0) {
				// Is a sprite sheet
				e_dim = { static_cast<int>(ep->image()->spriteDimensions().x), static_cast<int>(ep->image()->spriteDimensions().y) };
			} else {
				// Not a sprite sheet
				e_dim = { static_cast<int>(ep->image()->width()), static_cast<int>(ep->image()->height()) };
			}
			
			if (ContainsPoint(e_pos, e_dim, vec2<int>{x, y})) {
				RemoveEntity(ep);
				return;
			}
		}
	}
}

bool Level::CheckPoint(int x, int y)
{
	peMap::iterator it = _pointList.find(SDL_Point {x, y});

	return (it != _pointList.end());
}
