#pragma once

#include "entity.h"
#include "types.h"

template <typename T> bool PComp(const T * const &a, const T * const &b)
{
	return *a < *b;
}

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
		Entity* GetByName(std::string name) const;

		// GetByID()		- Return the entity with specified ID
		//	ID:			int with entity's ID
		Entity* GetByID(int ID) const;

		// GetByIndex()		- Return the entity at specified index
		//	index:		index entity is at
		Entity* GetByIndex(unsigned int index) const;

		// AddEntity()		- Add an entity into the collection
		//	name:		name of the entity being added
		//	entity:		pointer to the entity to add
		void AddEntity(Entity* entity);

		// RemoveByName()	- Remove an entity with the specified name
		//	name:		name of entity to remove
		void RemoveByName(std::string name);

		// RemoveByID()		- Remove an entity with the specified ID
		//	ID:			ID of entity to remove
		void RemoveByID(int ID);

		// RemoveByIndex()	- Remove an entity at given index
		//	index:		index at which to remove entity
		void RemoveByIndex(unsigned int index);

		// HandleAllEvents()- Handles events (such as input) for all entities in collection
		void HandleAllEvents(SDL_Event*);

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
		eList _collection;

		int nextID;
};
