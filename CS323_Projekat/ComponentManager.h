#pragma once
#include <unordered_map>
#include <memory>

#include "Components.h" 

using namespace Components;
using EntityID = int;


class ComponentManager
{
public:
	ComponentManager() = default;
	void AddNewComponent(EntityID id, std::unique_ptr<Component> component);
private:
	std::unordered_map<EntityID, std::unique_ptr<Component>> components;
};