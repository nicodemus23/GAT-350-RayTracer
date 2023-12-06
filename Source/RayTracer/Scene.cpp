#include "Scene.h"
#include "Canvas.h"
#include "Camera.h"
#include "Color.h"
#include "MathUtils.h"
#include "Ray.h"
#include "Random.h"
#include <iostream>

void Scene::Render(Canvas& canvas, int numSamples)
{
	// Iterate over each pixel of the canvas
	for (int y = 0; y < canvas.GetSize().y; y++) {
		for (int x = 0; x < canvas.GetSize().x; x++) {
			// create vec2 pixel from canvas x,y
			glm::vec2 pixel = glm::vec2{ x, y };
			// set initial color
			Color::color3_t color{ 0, 0, 0 };

			// cast ray for each sample, accumulate color value for each sample
			// reach ray will have a random offset from the pixel center
			for (int sample = 0; sample < numSamples; sample++)
			{


				// get normalized (0 - 1) point coordinates from pixel
				glm::vec2 point = (pixel + glm::vec2{ Random::random01(), Random::random01() }) / glm::vec2(canvas.GetSize().x, canvas.GetSize().y); // < divide pixel by canvas size to normalize(0 - 1)

				// flip y Since screen coordinates usually have the origin at the top left, but mathematical representations often use the bottom left need to flip y coordinate
				point.y = 1.0f - point.y;

				// create ray from camera (using point) // since m_camera is shared ptr object you can't call GetRay directly on the shared ptr<Camera> object. 
				// ... it's a smart pointer so doesn't directly expose the member of te objects it holds. have to use -> to access members of the pointed-to object 
				ray_t ray = m_camera->GetRay(point); //<get ray from camera using point>

				// cast ray into scene
				raycastHit_t raycastHit;
				// set color value from trace
				color += Trace(ray, 0, 100, raycastHit, m_depth);
			}
			// get average color (average = (color + color + color) / number of samples)
			color /= numSamples;

			canvas.DrawPoint(pixel, Color::color4_t(color, 1));
		}
	}
}

// COLOR TRACE
// 
Color::color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth)
{
	bool rayHit = false;
	float closestDistance = maxDistance;

	// check if scene objects are hit by the ray
	for (const auto& object : m_objects)
	{
		// when checking objects don't include objects farther than closest hit (starts at max distance)
		if (object->Hit(ray, minDistance, closestDistance, raycastHit))
		{
			rayHit = true;
			// set closest distance to the raycast hit distance (only hit objects closer than closest distance)
			closestDistance = raycastHit.distance;
		}
	}

	// if ray hit object, scatter (bounce) ray and check for next hit
	if (rayHit)
	{
		ray_t scattered;
		Color::color3_t color;

		// check if maximum depth (number of bounces) is reached, get color from material and scattered ray
		if (depth > 0 && raycastHit.material->Scatter(ray, raycastHit, color, scattered))
		{	// recursive function, call self and modulate (multiply) colors of depth bounces
			return color * Trace(scattered, minDistance, maxDistance, raycastHit, depth -1);
		}
		else
		{	// reached maximum depth of bounces (color is black)
			//return Color::color3_t{ 0, 0, 0 };
			
			// reached maximum depth of bounces (get emissive color, will be black except for Emissive materials)
			return raycastHit.material->GetEmissive();
		}
	}

	// if ray not hit, return scene sky color
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
	Color::color3_t color = MathUtils::lerp(m_bottomColor, m_topColor, t);

	return color;
}


