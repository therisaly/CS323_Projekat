#include "EntityManager.h"

EntityManager::EntityManager(ComponentManager& cM)
	:
	componentManager(cM)
{
}

EntityID EntityManager::AddNewEntity()
{
	entities.push_back(entityCounter); 
	std::printf("Created new entity, ID: %d\n", entityCounter);
	entityCounter++;
	return entityCounter - 1;
}
