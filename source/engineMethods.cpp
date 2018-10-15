#include "engineMethods.h"
#include "player.h"
#include "text.h"
#include "ball.h"
#include "wall.h"
#include "globals.h"

#include "states/console.h"

#include <sstream>
#include <iostream>

sVector* ParseSerializedString(std::string str)
{
	sVector* strList = new sVector;

	std::stringstream stream(str);
	std::string temp;

	stream >> temp;
	
	while (stream)
	{
		if (temp.at(0) == '"')
		{
			if (temp.at(temp.length() - 1) == '"')
			{
				std::string total = temp.substr(1, temp.length() - 2);
				//std::cout << total << std::endl;
				strList->push_back(total);
			}
			else
			{
				//std::cout << temp.substr(1) << std::endl;
				std::string total = temp.substr(1);	

				stream >> temp;
				while (temp.at(temp.length() - 1) != '"')
				{
					total += " " + temp;

					stream >> temp;
				}

				total += " " + temp.substr(0, temp.length() - 1);
				//std::cout << total << std::endl;
				strList->push_back(total);
			}
		}
		else
		{
			//std::cout << temp << std::endl;
			strList->push_back(temp);
		}
		stream >> temp;
	}

	return strList;
}

Entity* CreateSerializedObject(std::string str)
{
	if (str.find("@Entity") == std::string::npos)
	{
		std::cout << "Error: Trying to create serialized object that is not an entity!" << std::endl;
		return nullptr;
	}

	Entity* obj = nullptr;

	if (str.find("@Player") != std::string::npos)
	{
		obj = new Player;
	}

	if (str.find("@Text") != std::string::npos)
	{
		obj = new Text;
	}

	if (str.find("@Ball") != std::string::npos)
	{
		obj = new Ball;
	}

	if (str.find("@Wall") != std::string::npos)
	{
		obj = new Wall;
	}

	if (obj != nullptr)
	{
		obj->Unserialize(str);	
		return obj;
	}

	return nullptr;
}

void AddOutput(std::string str)
{
	StateConsole::Instance()->AddOutput(str);
}

void AddError(std::string str)
{
	StateConsole::Instance()->AddError(str);
}

vec2<int> WorldToScreen(const vec2<int> &coords)
{
	int x = coords.x - globalCam->x();
	int y = coords.y - globalCam->y();

	return {x, y};
}

vec2<int> WorldToScreen(int x, int y)
{
	return WorldToScreen({x, y});
}

vec2<int> ScreenToWorld(const vec2<int> &coords)
{
	int x = coords.x + globalCam->x();
	int y = coords.y + globalCam->y();

	return {x, y};
}

vec2<int> ScreenToWorld(int x, int y)
{
	return ScreenToWorld({x, y});
}

bool operator<(const SDL_Point &lhs, const SDL_Point &rhs) 
{
    return (lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y));
}
