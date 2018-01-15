#include "../include/entityCollection.h"
#include "../include/globals.h"

#include <iostream>

EntityCollection::EntityCollection()
{
	nextID = 0;
}

EntityCollection::~EntityCollection()
{
	while (_REALcollection.size() > 0)
	{
		_REALcollection.erase(_REALcollection.begin());	
	}
}

int EntityCollection::GetCount() const
{
	return _REALcollection.size();
}

Entity* EntityCollection::GetByName(std::string name) const
{
	// eList == std::map<std::string, Entity*>
	eListt::const_iterator itt = _REALcollection.begin();
//	it = _collection.find(name);
//
//	if (it != _collection.end())
//	{
//		return it->second;
//	}
//	else
//	{
//		return nullptr;
//	}

	// Doesn't work while entity doesn't have a name attribute
	while (itt != _REALcollection.end())
	{
		name = "";
		return nullptr;
	}
	return nullptr;	
}

Entity* EntityCollection::GetByID(int ID) const
{
	// eList == std::map<std::string, Entity*>
//	eList::const_iterator it = _collection.begin();
	eListt::const_iterator itt = _REALcollection.begin();

	while (itt != _REALcollection.end())
	{
		if ((*itt)->ID() == ID)
		{
			return (*itt);
		}
	}
	return nullptr;

//	while (it != _collection.end() && it->second->ID() != ID)
//	{
//		it++;
//	}
//
//	if (it != _collection.end())
//	{
//		return it->second;
//	}
//	else
//	{
//		return nullptr;
//	}
}

Entity* EntityCollection::GetByIndex(unsigned int index) const
{
	// eList == std::map<std::string, Entity*>
//	eList::const_iterator it = _collection.begin();
	eListt::const_iterator itt = _REALcollection.begin();

	if (index < _REALcollection.size())
	{
		for (unsigned int i = 0; i < index; i++)
		{
			itt++;
		}
		return (*itt);
	}

//	if (index < _collection.size())
//	{
//		for (unsigned int i = 0; i < index; i++)
//		{
//			it++;
//		}
//
//		return it->second;
//	}

	return nullptr;
}

void EntityCollection::AddEntity(std::string name, Entity* entity)
{
//	if (_collection.size() == 0)
//	{
//		entity->SetID(0);
//	}
//	else
//	{
//		// eList == std::map<std::string, Entity*>
//		eList::const_iterator it = _collection.end();
//		it--;
//
//		entity->SetID(it->second->ID() + 1);
//	}
//
//	std::pair<std::string, Entity*> object;
//
//	object.first = name;
//	object.second = entity;
//
//	_collection.insert(object);

	// Need to insert name into entity later
	name = "";	

	entity->SetID(nextID++);
	
	_REALcollection.push_back(entity);
}

void EntityCollection::RemoveByName(std::string name)
{
	// eList == std::map<std::string, Entity*>
//	eList::const_iterator it = _collection.begin();
//
//	it = _collection.find(name);
//
//	if (it != _collection.end())
//	{
//		delete it->second;
//
//		_collection.erase(it);
//	}
}

void EntityCollection::RemoveByID(int ID)
{
	// eList == std::map<std::string, Entity*>
	eListt::const_iterator itt = _REALcollection.begin();
//	eList::const_iterator it = _collection.begin();
//
//	while (it != _collection.end() && it->second->ID() != ID)
//	{
//		it++;
//	}
//
//	if (it != _collection.end())
//	{
//		delete it->second;
//
//		_collection.erase(it);
//	}

	while (itt != _REALcollection.end() && (*itt)->ID() != ID)
	{
		itt++;
	}

	if (itt != _REALcollection.end())
	{
		delete (*itt);

		_REALcollection.erase(itt);
	}
}

void EntityCollection::RemoveByIndex(unsigned int index)
{
	// eList == std::map<std::string, Entity*>
	eListt::const_iterator itt = _REALcollection.begin();
//	eList::const_iterator it = _collection.begin();
//
//	if (index < _collection.size())
//	{
//		for (unsigned int i = 0; i < index; i++)
//		{
//			it++;
//		}
//
//		if (it->second != nullptr)
//		{
//			delete it->second;
//
//			_collection.erase(it);
//		}
//	}
	
	if (index < _REALcollection.size())
	{
		for (unsigned int i = 0; i < index; i++)
		{
			itt++;
		}

		if ((*itt) != nullptr)
		{
			delete (*itt);

			_REALcollection.erase(itt);
		}		
	}
}

void EntityCollection::HandleAllEvents(SDL_Event* event)
{
	// eList == std::map<std::string, Entity*>
//	eList::const_iterator it = _collection.begin();
//
//	while (it != _collection.end())
//	{
//		if (it->second != nullptr)
//		{
//			it->second->HandleEvents(event);
//		}
//
//		it++;
//	}
	
	eListt::const_iterator itt = _REALcollection.begin();

	while (itt != _REALcollection.end())
	{
		if ((*itt) != nullptr)
		{
			(*itt)->HandleEvents(event);
		}

		itt++;
	}
}

void EntityCollection::UpdateAll()
{
	// eList == std::map<std::string, Entity*>
	eListt::const_iterator itt = _REALcollection.begin();

	while (itt != _REALcollection.end())
	{
		// Uncomment to debug Update() on different entities
		//std::cerr << it->first << std::endl;
		if ((*itt) != nullptr && (*itt)->active())
		{
			(*itt)->Update();
		}

		itt++;
	}
}

void EntityCollection::RenderAll(float interpolation)
{
	// eList == std::map<std::string, Entity*>
	eListt::const_iterator itt = _REALcollection.begin();

	while (itt != _REALcollection.end())
	{
		// Uncomment to debug Render() on different entities
		//std::cerr << it->first << std::endl;
		if ((*itt) != nullptr && (*itt)->visible())
		{
			(*itt)->Render(interpolation);
		}

		itt++;
	}
}


