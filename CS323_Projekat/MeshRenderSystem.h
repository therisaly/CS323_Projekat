#pragma once
#include "ComponentManager.h"

class MeshRenderSystem
{
public:
	MeshRenderSystem() = default;
	void RenderMesh(EntityID entityID, std::unordered_map<EntityID, Mesh>& components)
	{
		auto iterator = components.find(entityID);

		if (iterator == components.end())
		{
			std::printf("No entity with ID %d", entityID);
			return;
		}

		glCallList(iterator->second.list);
	}
};