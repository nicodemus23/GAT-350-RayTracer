#pragma once
#include <glm/glm.hpp>
#include <cmath>  // for std::fabs
#include <cfloat> // for FLT_EPSILON


class MathUtils
{

public:

	template <typename T>
	static inline T lerp(const T& a, const T& b, float t)
	{
		return (a * (1 - t)) + (t * b);
	}

	static inline glm::vec3 cross(const glm::vec3& v1, const glm::vec3& v2)
	{
		return glm::vec3((v1.y * v2.z) - (v1.z * v2.y),
						 (v1.z * v2.x) - (v1.x * v2.z),
						 (v1.x * v2.y) - (v1.y * v2.x));

	}

	inline float dot(const glm::vec3& v1, const glm::vec3& v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

	}

	inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n)
	{
		return (v - (n * dot(n, v)) * glm::vec3{ 2 });
	}

	static inline bool approximately(float value1, float value2)
	{
		// check if the difference between the values is less than epsilon
		 //(get floating - point absolute value(subtract value 1 from value 2) 
		return	(std::fabs(value1 - value2) < FLT_EPSILON);
	}

	inline bool refract(const glm::vec3& v, const glm::vec3& n, float index, glm::vec3& refracted)
	{
		// normalize the incoming vector (v)
		glm::vec3 nv = glm::normalize(v);

		float dt = dot(nv, n);
		float discriminant = 1 - (index * index) * (1 - dt * dt);
		if (discriminant > 0)
		{
			refracted = index * (nv - (n * dt)) - (n * std::sqrt(discriminant));
			return true;
		}

		return false;
	}


	// a = start of the interpolation
	// b = end value for interpolation
	// float t = interpolation factor
		// [0-1] 0 returns a, 1 returns b and linear blend between the two

	// if the type isn't clear or you want to use a specific type then call (when a static member function) specifying type: 
	// auto result = MathUtils::lerp<double>(0.5, 1.0, 0.5); // Explicitly specifying T as double // <double> is the type, yo 
	// 
	// otherwise, if the compiler can interpret what the type is then:
	// 	auto result = MathUtils::lerp(0.0f, 1.0f, .05f);


};
