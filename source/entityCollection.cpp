#include "../include/entityCollection.h"

#include <iostream>

EntityCollection::EntityCollection()
{

}

EntityCollection::~EntityCollection()
{
	while (_collection.size() > 0)
	{
		if (_collection.begin()->second != nullptr)
		{
			delete _collection.begin()->second;
		}
		_collection.erase(_collection.begin());
	}
}

int EntityCollection::GetCount() const
{
	return _collection.size();
}

Entity* EntityCollection::GetByName(std::string name) const
{
	// eList == std::map<std::string, Entity*>
	eList::const_iterator it = _collection.begin();

	it = _collection.find(name);

	if (it != _collection.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

Entity* EntityCollection::GetByID(int ID) const
{
	// eList == std::map<std::string, Entity*>
	eList::const_iterator it = _collection.begin();

	while (it != _collection.end() && it->second->ID() != ID)
	{
		it++;
	}

	if (it != _collection.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

Entity* EntityCollection::GetByIndex(unsigned int index) const
{
	// eList == std::map<std::string, Entity*>
	eList::const_iterator it = _collection.begin();

	if (index < _collection.size())
	{
		for (unsigned int i = 0; i < index; i++)
		{
			it++;
		}

		return it->second;
	}

	return nullptr;
}

void EntityCollection::AddEntity(std::string name, Entity* entity)
{
	if (_collection.size() == 0)
	{
		entity->SetID(0);
	}
	else
	{
		// eList == std::map<std::string, Entity*>
		eList::const_iterator it = _collection.end();
		it--;

		entity->SetID(it->second->ID() + 1);
	}

	std::pair<std::string, Entity*> object;

	object.first = name;
	object.second = entity;

	_collection.insert(object);
}

void EntityCollection::RemoveByName(std::string name)
{
	// eList == std::map<std::string, Entity*>
	eList::const_iterator it = _collection.begin();

	it = _collection.find(name);

	if (it != _collection.end())
	{
		delete it->second;

		_collection.erase(it);
	}
}

void EntityCollection::RemoveByID(int ID)
{
	// eList == std::map<std::string, Entity*>
	eList::const_iterator it = _collection.begin();

	while (it != _collection.end() && it->second->ID() != ID)
	{
		it++;
	}

	if (it != _collection.end())
	{
		delete it->second;

		_collection.erase(it);
	}
}

void EntityCollection::RemoveByIndex(unsigned int index)
{
	// eList == std::map<std::string, Entity*>
	eList::const_iterator it = _collection.begin();

	if (index < _collection.size())
	{
		for (unsigned int i = 0; i < index; i++)
		{
			it++;
		}

		if (it->second != nullptr)
		{
			delete it->second;

			_collection.erase(it);
		}
	}
}

void EntityCollection::HandleAllEvents(SDL_Event* event)
{
	// eList == std::map<std::string, Entity*>
	eList::const_iterator it = _collection.begin();

	while (it != _collection.end())
	{
		if (it->second != nullptr)
		{
			it->second->HandleEvents(event);
		}

		it++;
	}
}

void EntityCollection::UpdateAll()
{
	// eList == std::map<std::string, Entity*>
	eList::const_iterator it = _collection.begin();

	while (it != _collection.end())
	{
        // Uncomment to debug Update() on different entities
        //std::cerr << it->first << std::endl;
		if (it->second != nullptr && it->second->active())
		{
			it->second->Update();
		}

		it++;
	}
}

void EntityCollection::RenderAll(float interpolation)
{
	// eList == std::map<std::string, Entity*>
	eList::const_iterator it = _collection.begin();

	while (it != _collection.end())
	{
        // Uncomment to debug Render() on different entities
        //std::cerr << it->first << std::endl;
		if (it->second != nullptr && it->second->visible())
		{
			it->second->Render(interpolation);
		}

		it++;
	}
}


