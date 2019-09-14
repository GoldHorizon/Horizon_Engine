#include "entityCollection.h"
#include "globals.h"

#include <iostream>

bool EComp(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b)
{
	if (*a == *b)
	{
		return (*a).ID < (*b).ID;
	}
	else
		return *a < *b;
}

EntityCollection::EntityCollection()
{
	nextID = 1;
}

EntityCollection::~EntityCollection()
{
	ClearEntities();
}

int EntityCollection::GetCount() const
{
	return _collection.size();
}

Entity* EntityCollection::GetByName(std::string name) const
{
	for (auto& e : _collection) {
		if (e->name() == name) return e.get();
	}

	return nullptr;	
}

Entity* EntityCollection::GetByID(int ID) const
{
	for (auto& e : _collection) {
		if (e->ID == ID) return e.get();
	}

	return nullptr;	
}

Entity* EntityCollection::GetByIndex(unsigned int index) const
{
	if (index >= _collection.size()) return nullptr;

	auto it = _collection.begin();

	for (unsigned int i = 0; i < index; i++)
	{
		it++;
	}
	return it->get();
}

void EntityCollection::AddEntity(std::unique_ptr<Entity> entity)
{
	if (entity->ID == 0)
		entity->ID = (nextID++);
	
	_collection.push_back(std::move(entity));
}

void EntityCollection::Remove(Entity* entity)
{
	for (auto& e : _collection) {
		if (e.get() == entity)
			_collection.remove(e);
	}
}

void EntityCollection::Remove(std::unique_ptr<Entity>& entity) 
{
	_collection.remove(entity);
}

// @Cleanup: should we be deleteing the member when removing it?
// 	Look at ALL remove functions to check this
void EntityCollection::RemoveByName(std::string name)
{
	auto it = _collection.begin();

	// Doesn't work while entity doesn't have a name attribute
	while (it != _collection.end())
	{
		if ((*it)->name() == name)
		{
			_collection.erase(it);
		}

		it++;
	}
}

void EntityCollection::RemoveByID(int ID)
{
	auto it = _collection.begin();

	while (it != _collection.end() && (*it)->ID != ID)
	{
		it++;
	}

	if (it != _collection.end())
	{
		_collection.erase(it);
	}
}

void EntityCollection::RemoveByIndex(unsigned int index)
{
	auto it = _collection.begin();
	
	if (index < _collection.size())
	{
		for (unsigned int i = 0; i < index; i++)
		{
			it++;
		}

		if ((*it) != nullptr)
		{
			_collection.erase(it);
		}		
	}
}

void EntityCollection::ClearEntities()
{
	_collection.clear();
}

void EntityCollection::HandleAllEvents(Event& event)
{
	auto it = _collection.rbegin();

	while (it != _collection.rend())
	{
		if ((*it) != nullptr && (*it)->visible)
		{
			(*it)->HandleEvents(event);
		}

		it++;
	}
}

void EntityCollection::UpdateAll()
{
	auto it = _collection.rbegin();

	while (it != _collection.rend())
	{
		if ((*it) != nullptr && (*it)->visible)
		{
			(*it)->Update();
		}

		it++;
	}
}

void EntityCollection::RenderAll(float interpolation, int xOffset, int yOffset)
{
	
	_collection.sort(EComp);
	_collection.reverse();

	for (auto& e : _collection) {
		if (e != nullptr && e->visible)
			e->Render(interpolation, xOffset, yOffset);
	}

	//auto it = _collection.begin();

	//while (it != _collection.end())
	//{
	//	// Uncomment to debug Render() on different entities
	//	//std::cerr << it->first << std::endl;
	//	if ((*it) != nullptr && (*it)->visible)
	//	{
	//		(*it)->Render(interpolation, xOffset, yOffset);
	//	}

	//	it++;
	//}
}

Entity* EntityCollection::operator[](int ID)
{
	return GetByIndex(ID);
}

std::list<std::unique_ptr<Entity>>& EntityCollection::collection()
{
	return _collection;
}

