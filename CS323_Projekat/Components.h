#pragma once
#include "Vec3.h"

namespace Components{

	class Component
	{
	public:
		virtual ~Component()
		{
			std::printf("Deconstructing Component\n");
		}
	};
	class Transform : public Component
	{
	public:
		Transform()
		{
			std::printf("Constructing Transform Component\n");
		}
	private:
		Vef3 position;
		Vef3 scale;
		Vef3 rotation;
	};

	class Mesh : public Component
	{
	public:
		Mesh()
		{
			std::printf("Constructing Mesh Component\n");
		}
	private:

	};

	class Collider : public Component
	{
	public:
		Collider()
		{
			std::printf("Constructing Collider Component\n");
		}
	};
}