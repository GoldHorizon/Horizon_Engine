#pragma once

#include "entity.h"
#include "types.h"
#include "event.h"

template <typename T> bool PComp(const T * const &a, const T * const &b)
{
	return *a < *b;
}

// Used to compare entities for sorting by their depths (or ID?)
//bool EComp(const Entity * const &a, const Entity * const &b);
bool EComp(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity> &b);

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
		//	entity:		pointer to the entity to add
		//	name:		name of the entity being added
		void AddEntity(std::unique_ptr<Entity> entity);

		void Remove(Entity* entity);
		void Remove(std::unique_ptr<Entity>& entity);

		// RemoveByName()	- Remove an entity with the specified name
		//	name:		name of entity to remove
		void RemoveByName(std::string name);

		// RemoveByID()		- Remove an entity with the specified ID
		//	ID:			ID of entity to remove
		void RemoveByID(int ID);

		// RemoveByIndex()	- Remove an entity at given index
		//	index:		index at which to remove entity
		void RemoveByIndex(unsigned int index);

		// ClearEntities() 	- Remove all entities from the collection
		void ClearEntities();

		// HandleAllEvents()- Handles events (such as input) for all entities in collection
		void HandleAllEvents(Event&);

		// UpdateAll()		- Update every entity in collection
		void UpdateAll();

		// RenderAll()		- Render every entity in collection
		//	interpolation:		how much interpolation (prediction) to account for
		void RenderAll(float interpolation, int xOffset = 0, int yOffset = 0);

		/*
		 * Get Methods
		 */
		Entity* operator[](int ID);
		std::list<std::unique_ptr<Entity>>& collection();

		/*
		 * Set Methods
		 */
	protected:
		// _collection			// Collection of entities
		std::list<std::unique_ptr<Entity>> _collection;


	private:
		int nextID;
};
