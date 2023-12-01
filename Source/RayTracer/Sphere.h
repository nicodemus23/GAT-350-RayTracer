#pragma once
#include "Object.h"

class Sphere : public Object
{
public:
	Sphere() = default;
	Sphere(const glm::vec3& center, float radius, std::shared_ptr<Material> material) :
		//Object(std::shared_ptr<Material> material)
		Object(material),
		//<class Object base class constructor passing material>,
		m_center(center), // <set center>,
		m_radius(radius)    //<set radius>
	{}

	bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) override;

private:
	//<vector 3, default to 0> m_center;
	glm::vec3 m_center = glm::vec3(0);

	float m_radius = 0;
};