#pragma once
#include "Entity.h"
#include "Memory.h"
#include <vector>
class EntityList {
private:
	std::vector<Entity*> entList;
public:
	EntityList(int entCount)
	{
		int entsToRead = entCount; // This is because the entity list doesn't count local player but the ent count does
		entList.resize(entsToRead);
	}

	std::vector<Entity*> getEntVector() {
		return entList;
	}
};