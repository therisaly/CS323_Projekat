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
	auto transformComponent = std::make_unique<Transform>();

	componentManager.AddNewComponent(player, std::move(transformComponent));

	std::printf("Working\n");
}
