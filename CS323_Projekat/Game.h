#pragma once
#include "EntityManager.h"
#include "MeshLoader.h"
#include "MeshRenderSystem.h"

class Game
{
public:
	Game(ComponentManager& componentManager, EntityManager& entityManager, MeshRenderSystem& meshRenderSystem);
	void Go();
	void RenderTest();
private:
	ComponentManager& componentManager;
	EntityManager& entityManager;

	MeshRenderSystem& meshRenderSystem;

	EntityID player;
	EntityID player2;
};

