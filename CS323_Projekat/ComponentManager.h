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
	void AddNewComponent(std::unique_ptr<Component> component);

	auto& GetComponents()
	{
		return components;
	}
private:
	std::unordered_map<EntityID, std::vector<std::unique_ptr<Component>>> components; 
};