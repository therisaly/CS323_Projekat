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

		components[entityID].push_back(componentType);
	}
	template<typename T>
	void PrintAllComponents() 
	{
		T component; 
		for (const auto& pair : GetComponentMap<T>())
		{
			std::printf("Entity ID: %d\n", pair.first);
			for (int i = 0; i < pair.second.size(); i++)
			{
				std::printf("Component %d: %s\n", i, typeid(component).name());
			}

		}
	}
private:
	template<typename T>
	std::unordered_map<EntityID, std::vector<T>>& GetComponentMap()
	{
		static std::unordered_map<EntityID, std::vector<T>> components;
		return components;
	}
};
