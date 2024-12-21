#include "ComponentManager.h"

void ComponentManager::AddNewComponent(EntityID id, std::unique_ptr<Component> component)
{
	components.insert({ id,std::move(component)});
	printf("New component added for entity: %d\n", id);
}
