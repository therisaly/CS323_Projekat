#include "Game.h"

Game::Game(ComponentManager& componentManager, EntityManager& entityManager)
	:
	componentManager(componentManager),
	entityManager(entityManager)
{
}

void Game::Go()
{

	EntityID player = entityManager.AddNewEntity();
	EntityID player2 = entityManager.AddNewEntity();

	componentManager.AddNewComponent(std::make_unique<Transform>(player));
	componentManager.AddNewComponent(std::make_unique<Transform>(player));
	componentManager.AddNewComponent(std::make_unique<Transform>(player2));

	std::printf("Working\n");
}
