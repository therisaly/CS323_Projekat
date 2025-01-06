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

	template<typename T> 
	void AddNewComponent(EntityID entityID, T componentType)
	{
		auto& components = GetComponentMap<T>();

		components[entityID] = componentType;
	}
	template<typename T>
	void PrintAllComponents() 
	{
		T component; 
		for (const auto& pair : GetComponentMap<T>())
		{
			std::printf("Entity ID: %d\n", pair.first);
			std::printf("Component: %s\n", typeid(component).name());
		}
	}
	template<typename T>
	std::unordered_map<EntityID, T>& GetComponentMap()
	{
		static std::unordered_map<EntityID, T> components; 
		return components;
	}
};
