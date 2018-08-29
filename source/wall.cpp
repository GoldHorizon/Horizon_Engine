#include "wall.h"

Wall::Wall()
{
	LoadFromFile("images/Wall.png");
}

//void Wall::HandleEvents(SDL_Event*)
//{
//
//}

void Wall::Update()
{
	Entity::Update();
}

Entity* Wall::NewInstance()
{
    return new Wall();
}

std::string Wall::Serialize()
{
	std::string serialize_string = Entity::Serialize();

	serialize_string += "@Wall ";

	return serialize_string;
}

void Wall::Unserialize(std::string str)
{
	Entity::Unserialize(str);
}
