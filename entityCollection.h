#pragma once

#include <string>
#include <map>

#include "entity.h"

typedef std::map<std::string, Entity*> eMap;

class EntityCollection
{
public:
	/*
	 * Constructors/Destructors
	 */
	EntityCollection();
	~EntityCollection();

	/*
	 * Class Methods
	 */
	// GetCount()		- Return number of entities in collection
	int GetCount() const;

	// GetByName()		- Return the entity with specified name
	//	name:		string with name of entity
	Entity* const GetByName(std::string name) const;

	// GetByID()		- Return the entity with specified ID
	//	ID:			int with entity's ID
	Entity* const GetByID(int ID) const;

	// GetByIndex()		- Return the entity at specified index
	//	index:		index entity is at
	Entity* const GetByIndex(unsigned int index) const;

	// AddEntity()		- Add an entity into the collection
	//	name:		name of the entity being added
	//	entity:		pointer to the entity to add
	void AddEntity(std::string name, Entity* entity);

	// RemoveByName()	- Remove an entity with the specified name
	//	name:		name of entity to remove
	void RemoveByName(std::string name);

	// RemoveByID()		- Remove an entity with the specified ID
	//	ID:			ID of entity to remove
	void RemoveByID(int ID);

	// RemoveByIndex()	- Remove an entity at given index
	//	index:		index at which to remove entity
	void RemoveByIndex(unsigned int index);

	// UpdateAll()		- Update every entity in collection
	void UpdateAll();

	// RenderAll()		- Render every entity in collection
	//	interpolation:		how much interpolation (prediction) to account for
	void RenderAll(float interpolation);
	/*
	 * Get Methods
	 */

	/*
	 * Set Methods
	 */
private:
	// _collection			// Collection of entities
	eMap _collection;
};
