#pragma once
#include <vector>

#include "ComponentManager.h"

using EntityID = int;

class EntityManager
{
public:
	EntityManager(ComponentManager& cM);
    EntityID AddNewEntity();
private:
	ComponentManager& componentManager;
	std::vector<EntityID> entities;
	int entityCounter = 0;
};

