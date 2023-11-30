#pragma once
#include <stdlib.h>
#include <algorithm>


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
};
