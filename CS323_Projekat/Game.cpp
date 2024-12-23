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

	componentManager.AddNewComponent(player, Transform{});
	componentManager.AddNewComponent(player, Transform{});

	componentManager.AddNewComponent(player, Mesh{});
	componentManager.AddNewComponent(player2, Transform{});

	componentManager.PrintAllComponents<Transform>();
	componentManager.PrintAllComponents<Mesh>();



	std::printf("Working\n");
}
