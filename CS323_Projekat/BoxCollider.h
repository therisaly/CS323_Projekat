#pragma once
#include "Vec3.h"

class BoxCollider
{
public:
	BoxCollider() = default;
	BoxCollider(const Vef3& center, const Vef3& dimensions)
		:
		center(center),
		dimensions(dimensions)
	{}
    Vef3 GetMin() const
    {
        return Vef3(center.x - dimensions.x / 2.0f,
            center.y - dimensions.y / 2.0f,
            center.z - dimensions.z / 2.0f);
    }

    // Function to get the maximum corner of the box
    Vef3 GetMax() const
    {
        return Vef3(center.x + dimensions.x / 2.0f,
            center.y + dimensions.y / 2.0f,
            center.z + dimensions.z / 2.0f);
    }

    //AABB collision detection
    bool CheckCollision(const BoxCollider& other) const
    {
        // Get the minimum and maximum corners for both colliders
        Vef3 min1 = this->GetMin();
        Vef3 max1 = this->GetMax();
        Vef3 min2 = other.GetMin();
        Vef3 max2 = other.GetMax();

        // Check if there is an overlap on all three axes
        return (min1.x <= max2.x && max1.x >= min2.x) &&   
            (min1.y <= max2.y && max1.y >= min2.y) &&   
            (min1.z <= max2.z && max1.z >= min2.z);     
    }
public:
	Vef3 dimensions; // (width, height, depth)
	Vef3 center;
};