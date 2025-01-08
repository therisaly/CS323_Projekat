#include "Game.h"

Game::Game(ComponentManager& componentManager, EntityManager& entityManager, MeshRenderSystem& meshRenderSystem)
	:
	componentManager(componentManager),
	entityManager(entityManager),
	meshRenderSystem(meshRenderSystem)
{
}

void Game::Go()
{

	player = entityManager.AddNewEntity();
	player2 = entityManager.AddNewEntity();

	componentManager.AddNewComponent(player, Transform{});
	componentManager.AddNewComponent(player2, Transform{});

	Mesh mesh1;
	MeshLoader::LoadMesh("models/rotatingPlatform1.obj", mesh1);

	componentManager.AddNewComponent(player, Velocity{});
	componentManager.AddNewComponent(player2, Velocity{});
	componentManager.AddNewComponent(player, mesh1); 

}

void Game::RenderTest()
{
	meshRenderSystem.RenderMesh(player, componentManager.GetComponentMap<Mesh>());
}

