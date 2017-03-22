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

Entity& EntityCollection::GetByName(std::string name) const
{
	// eMap == std::map<std::string, Entity*>
	eMap::const_iterator it = _collection.begin();

	if (it != _collection.end())
	{

	}
	else
	{
		return NULL;
	}
}
