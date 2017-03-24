#pragma once

#include "entity.h"
#include "typedefs.h"

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
	Entity* const GetByName(std::string name) const;
	Entity* const GetByID(int ID) const;
	Entity* const GetByIndex(unsigned int index) const;

	void AddEntity(std::string name, Entity* entity);
	void RemoveByName(std::string name);
	void RemoveByID(int ID);
	void RemoveByIndex(unsigned int index);

	void UpdateAll();
	void RenderAll(float interpolation);
	/*
	 * Get Methods
	 */

	/*
	 * Set Methods
	 */
private:
	// eMap == std::map<std::string, Entity*>
	eMap _collection;
};
