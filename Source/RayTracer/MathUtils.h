#pragma once


class MathUtils
{

public:

	template <typename T>
	static inline T lerp(const T& a, const T& b, float t)
	{
		return (a * (1 - t)) + (t * b);
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
