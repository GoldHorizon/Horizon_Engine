#include "../entityCollection.h"

EntityCollection::EntityCollection()
{

}

EntityCollection::~EntityCollection()
{

}

int EntityCollection::GetCount() const
{
	return _collection.size();
}

Entity* const EntityCollection::GetByName(std::string name) const
{
	// eMap == std::map<std::string, Entity*>
	eMap::const_iterator it = _collection.begin();

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

Entity* const EntityCollection::GetByID(int ID) const
{
	// eMap == std::map<std::string, Entity*>
	eMap::const_iterator it = _collection.begin();


}

Entity* const EntityCollection::GetByIndex(unsigned int index) const
{
	// eMap == std::map<std::string, Entity*>
	eMap::const_iterator it = _collection.begin();

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
