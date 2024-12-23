#include "ComponentManager.h"

void ComponentManager::AddNewComponent(std::unique_ptr<Component> component)
{
	printf("New component added for entity: %d\n", component->GetEntityID());

	auto& componentVector = components[component->GetEntityID()]; 

	componentVector.push_back(std::move(component));
}
