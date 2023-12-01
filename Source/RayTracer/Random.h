#pragma once
#include <stdlib.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>



class Random
{
public:
	// sets seed for random # generation
	static void seedRandom(unsigned int seed)
	{
		srand(seed);
	}

	// returns floating point number between 0-1
	static float random01()
	{	// scales int result of rand() to float 0-1 and divides by RAND_MAX
		return (float)rand() / RAND_MAX; // << normalizes to range 0-1
	}

	static float random(float min, float max)
	{
		if (min > max)
		{
			std::swap(min, max);
		}
		// generate random float ('tween 0-1)
		float randomFraction = (float)rand() / RAND_MAX;

		// scales to range (min, max) and return result
		return min + randomFraction * (max - min);
	}
	// returns random vector between min and max
	static inline glm::vec3 random(const glm::vec3& min, const glm::vec3& max)
	{  
		return glm::vec3(random(min.x, max.x), random(min.y, max.y), random(min.z, max.z));
	}


	inline glm::vec3 randomInUnitSphere()
	{
		glm::vec3 v;
		// generate random vectors between -1 <-> +1, return vector if length is less than 1
		do
		{
			v = random(glm::vec3(-1.0f), glm::vec3(1.0f)); //get random vector between(-1, -1, -1) and (1, 1, 1) 

		} while (glm::length2(v) >= 1.0f);

			return v;
	}
};
