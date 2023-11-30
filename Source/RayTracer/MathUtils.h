#pragma once
#include <glm/glm.hpp>


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
		return glm::vec3((v1.y * v2.z) - (v1.z - v2.y),
						 (v1.z * v2.x) - (v1.x - v2.z),
						 (v1.x * v2.y) - (v1.y - v2.x));

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
