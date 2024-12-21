#pragma once
#include "EntityManager.h"

class Game
{
public:
	Game(ComponentManager& componentManager, EntityManager& entityManager);
	void Go();
private:
	ComponentManager& componentManager;
	EntityManager& entityManager;
};

