#pragma once
#include <SDL.h>
#include <glm/glm.hpp>


struct ray_t
{
	ray_t() = default; // default constructor

	// parameterized constructor that initializes a ray_t object with specific origin and direction vectors. The origin and direction parameters are references to glm::vec3 objects
	ray_t(const glm::vec3& origin, const glm::vec3& direction) :
		origin{ origin },
		direction{ direction }
	{}


	glm::vec3 At(float t) const {
		return origin + t * direction;
	}

	// member function calculates a point along the ray at a given distance from the origin. It does this by multiplying the ray's direction vector by the distance and then 
	// adding this to the ray's origin. 
	glm::vec3 GetPoint(float distance) const { return origin + (direction * distance); }

	//This is a member variable representing the origin of the ray, initialized to a 3D vector with all components set to zero.
	glm::vec3 origin{ 0 };
	// member variable representing the direction of the ray, initialized to a 3D vector with all components set to zero.
	glm::vec3 direction{ 0 };

	// operator overload for a float that returns the 3D point. Another way to GetPoint()
	glm::vec3 operator* (float distance) const { return origin + (direction * distance); }

};

struct raycastHit_t
{
	// distance along the ray direction, from the origin to the hit point
	float distance = 0;

	// world point of raycast hit
	glm::vec3 point{ 0 };
	// surface normal of raycast hit
	glm::vec3 normal{ 0 };

	// material attached to hit object
	class Material* material{ nullptr };
};


// NOTES:
// GetPoint()
//GetPoint() is a named member function of the ray_t structure.
//It calculates a point along the ray by scaling the direction vector by distance and then adding this to the origin vector.
//To use this function, you would call it on an instance of ray_t like this: ray.GetPoint(distance); 

// operator*
//This is an operator overload for the multiplication operator *.It allows instances of ray_t to directly use the* operator with a float operand.
//Just like GetPoint, it computes a point along the ray using the same formula.
//The difference is in usage : you can use this operator in a more natural and succinct way that resembles mathematical notation.For instance, ray* distance.