#pragma once
#include "Vec3.h"
#include "BoxCollider.h"
#include "Model.h"

class GameObject
{
public:
	GameObject() = default;

	void Initialize(Model& model_)
	{
		model = model_;
		collider = BoxCollider(model.center, model.dimensions);
		position = model.center;
	}

	void Update()
	{
		ChangePosition();
	}
	void Render()
	{
		model.draw();
	}
	BoxCollider GetCollider() const
	{
		return collider;
	}
	Vef3 GetPosition() const
	{
		return position;
	}
	void ChangePosition()
	{

	}
protected:
	Vef3 position;
	Vef3 scale = Vef3(1, 1, 1);

	Model model;
	BoxCollider collider;
};