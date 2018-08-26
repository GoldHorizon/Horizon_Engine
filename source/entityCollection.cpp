#include "../include/entityCollection.h"
#include "../include/globals.h"

#include <iostream>

EntityCollection::EntityCollection()
{
	nextID = 0;
}

EntityCollection::~EntityCollection()
{
	while (_collection.size() > 0)
	{
		_collection.erase(_collection.begin());	
	}
}

int EntityCollection::GetCount() const
{
	return _collection.size();
}

Entity* EntityCollection::GetByName(std::string name) const
{
	eList::const_iterator it = _collection.begin();

	// Doesn't work while entity doesn't have a name attribute
	while (it != _collection.end())
	{
		if ((*it)->name() == name)
		{
			return (*it);
		}
	}
	return nullptr;	
}

Entity* EntityCollection::GetByID(int ID) const
{
	eList::const_iterator it = _collection.begin();

	while (it != _collection.end())
	{
		if ((*it)->ID() == ID)
		{
			return (*it);
		}
	}
	return nullptr;
}

Entity* EntityCollection::GetByIndex(unsigned int index) const
{
	eList::const_iterator it = _collection.begin();

	if (index < _collection.size())
	{
		for (unsigned int i = 0; i < index; i++)
		{
			it++;
		}
		return (*it);
	}

	return nullptr;
}

void EntityCollection::AddEntity(Entity* entity)
{
	entity->SetID(nextID++);
	
	_collection.push_back(entity);
}

void EntityCollection::RemoveByName(std::string name)
{
	eList::const_iterator it = _collection.begin();

	// Doesn't work while entity doesn't have a name attribute
	while (it != _collection.end())
	{
		if ((*it)->name() == name)
		{
			delete (*it);
			_collection.erase(it);
		}

		it++;
	}
}

void EntityCollection::RemoveByID(int ID)
{
	eList::const_iterator it = _collection.begin();

	while (it != _collection.end() && (*it)->ID() != ID)
	{
		it++;
	}

	if (it != _collection.end())
	{
		delete (*it);

		_collection.erase(it);
	}
}

void EntityCollection::RemoveByIndex(unsigned int index)
{
	eList::const_iterator it = _collection.begin();
	
	if (index < _collection.size())
	{
		for (unsigned int i = 0; i < index; i++)
		{
			it++;
		}

		if ((*it) != nullptr)
		{
			delete (*it);

			_collection.erase(it);
		}		
	}
}

void EntityCollection::HandleAllEvents(SDL_Event* event)
{
	eList::const_iterator it = _collection.begin();

	while (it != _collection.end())
	{
		if ((*it) != nullptr)
		{
			(*it)->HandleEvents(event);
		}

		it++;
	}
}

void EntityCollection::UpdateAll()
{
	eList::const_iterator it = _collection.begin();

	while (it != _collection.end())
	{
		// Uncomment to debug Update() on different entities
		//std::cerr << it->first << std::endl;
		if ((*it) != nullptr && (*it)->active())
		{
			(*it)->Update();
		}

		it++;
	}
}

void EntityCollection::RenderAll(float interpolation)
{
	_collection.sort(PComp<Entity>);
	_collection.reverse();

	eList::const_iterator it = _collection.begin();

	while (it != _collection.end())
	{
		// Uncomment to debug Render() on different entities
		//std::cerr << it->first << std::endl;
		if ((*it) != nullptr && (*it)->visible())
		{
			(*it)->Render(interpolation);
		}

		it++;
	}
}

Entity* EntityCollection::operator[](int ID)
{
	return GetByIndex(ID);
}

