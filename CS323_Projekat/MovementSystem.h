#pragma once
#include "ComponentManager.h"

class MovementSystem
{
public:
	MovementSystem() = default;
	void MoveEntity(EntityID entityID, Vef3 velocity, std::unordered_map<EntityID, Transform>& components)
	{
		auto iterator = components.find(entityID);

		if (iterator == components.end())
		{
			std::printf("No entity with ID %d", entityID);
			return;
		}

		for (auto& comp : iterator->second)
		{
			if (auto transform = dynamic_cast<Transform*>(comp.get()))
			{
				transform->position += velocity;
			}
		}
	}
private:
};