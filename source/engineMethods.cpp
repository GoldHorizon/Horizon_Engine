#include "engineMethods.h"
#include "player.h"
#include "text.h"
#include "ball.h"
#include "wall.h"
#include "globals.h"

#include "states/console.h"

#include <sstream>
#include <iostream>

std::unique_ptr<std::vector<std::string>> ParseSerializedString(std::string str)
{
	auto strList = std::make_unique<std::vector<std::string>>();

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

std::unique_ptr<Entity> CreateSerializedObject(std::string str)
{
	if (str.find("@Entity") == std::string::npos)
	{
		std::cout << "Error: Trying to create serialized object that is not an entity!" << std::endl;
		return nullptr;
	}

	std::unique_ptr<Entity> obj;

	if (str.find("@Player") != std::string::npos)
	{
		obj = std::make_unique<Player>();
	}

	if (str.find("@Text") != std::string::npos)
	{
		obj = std::make_unique<Text>();
	}

	if (str.find("@Ball") != std::string::npos)
	{
		obj = std::make_unique<Ball>();
	}

	if (str.find("@Wall") != std::string::npos)
	{
		obj = std::make_unique<Wall>();
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
	//StateConsole::Instance()->AddOutput(str);
	//auto console = main_game.GetState(GameStateType::CONSOLE);
	//
	//if (console)
	//	console->AddOutput(str);
}

void AddError(std::string str)
{
	//StateConsole::Instance()->AddError(str);
	//auto console = main_game.GetState(GameStateType::CONSOLE);
	//
	//if (console)
	//	console->AddError(str);
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

bool ContainsPoint(const vec4<int> & rect, const vec2<int> & point)
{
	bool inside = false;

	inside = (point.x >= rect.x && point.x < rect.x + rect.z) && (point.y >= rect.y && point.y < rect.y + rect.w);

	return inside;
}

bool ContainsPoint(const vec2<int> & rect_pos, const vec2<int> & rect_dim, const vec2<int> & point)
{
	bool inside = false;

	inside = (point.x >= rect_pos.x && point.x < rect_pos.x + rect_dim.x) && (point.y >= rect_pos.y && point.y < rect_pos.y + rect_dim.y);

	return inside;
}

bool operator<(const SDL_Point &lhs, const SDL_Point &rhs) 
{
    return (lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y));
}
