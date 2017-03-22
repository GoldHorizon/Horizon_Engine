#pragma once

#include "entity.h"

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
	int GetCount() const;
	Entity GetByName(std::string name) const;
	Entity GetByID(int ID) const;
	Entity GetByIndex(int index) const;

	void AddEntity(std::string name, Entity* entity);
	void RemoveByName(std::string name);
	void RemoveByID(int ID);
	void RemoveByIndex(int index);

	void UpdateAll();
	void RenderAll();
	/*
	 * Get Methods
	 */

	/*
	 * Set Methods
	 */
private:
	std::map<std::string, Entity*> _collection;
};
