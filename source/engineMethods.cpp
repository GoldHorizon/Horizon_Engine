#include "engineMethods.h"
#include "player.h"
#include "text.h"
#include "ball.h"

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
	if (str.find("@Entity") == -1)
	{
		std::cout << "Error: Trying to create serialized object that is not an entity!" << std::endl;
		return nullptr;
	}

	Entity* obj;

	if (str.find("@Player") != -1)
	{
		obj = new Player;
		obj->Unserialize(str);	
		return obj;
	}

	if (str.find("@Text") != -1)
	{
		std::cout << "Found text object to unserialized" << std::endl;
		obj = new Text;
		obj->Unserialize(str);	
		std::cout << "Created text object, returning it..." << std::endl;
		return obj;
	}

	if (str.find("@Ball") != -1)
	{
		obj = new Ball;
		obj->Unserialize(str);	
		return obj;
	}

	return nullptr;
}

bool operator<(const SDL_Point &lhs, const SDL_Point &rhs) 
{
    return (lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y));
}
