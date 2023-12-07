#pragma once
#include "Color.h"
#include "Ray.h"
#include "Camera.h"
#include <memory>
#include "Object.h"
#include <vector>

class Scene
{
public:
	Scene() = default;
	Scene(int depth, const Color::color3_t& topColor, const Color::color3_t& bottomColor) :
		m_topColor{ topColor },
		m_bottomColor{ bottomColor }
	{}
	
	// constructor that takes a top and bottom color>
	void Render(class Canvas& canvas, int numSamples, int depth);
	// SetCamera() method>
	void SetCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }

	// Trace() method that takes a ray, min distance, max distance, and a raycastHit_t reference
	Color::color3_t Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth);
	//Color::color3_t TraceDistance(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit);

	// method to add objects to the scene>
	void AddObject(std::unique_ptr<Object> object) { m_objects.push_back(std::move(object)); }

private:
	std::shared_ptr<Camera> m_camera;

	Color::color3_t m_topColor{ 1 };
	Color::color3_t m_bottomColor{ 0 };

	std::vector<std::unique_ptr<Object>> m_objects;

	raycastHit_t raycastHit;

	int m_depth{ 5 };


	
};