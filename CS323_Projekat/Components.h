#pragma once
#include "Vec3.h"

namespace Components{

	using EntityID = int;

	class Component
	{
	public:
		virtual ~Component()
		{
			std::printf("Deconstructing Component\n");
		}
		int GetEntityID() const
		{
			return entityID;
		}
	protected:
		EntityID entityID = 0;

		Component(EntityID entityID)
			: entityID(entityID)
		{}
	};
	class Transform : public Component
	{
	public:
		Transform(EntityID eID)
			:
			Component(eID)
		{
			std::printf("Constructing Transform Component\n");
		}
		Vef3 position;
		Vef3 scale;
		Vef3 rotation;
	};

	class Mesh : public Component
	{
	public:
		Mesh(EntityID eID)
			:
			Component(eID)
		{
			std::printf("Constructing Mesh Component\n");
		}
	private:

	};

	class Collider : public Component
	{
	public:
		Collider(EntityID eID)
			:
			Component(eID)
		{
			std::printf("Constructing Collider Component\n");
		}
	};
}