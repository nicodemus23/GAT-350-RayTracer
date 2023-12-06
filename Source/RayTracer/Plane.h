#pragma once
#include "Object.h"

class Plane : public Object
{
public:
	Plane() = default;
	Plane(const glm::vec3& center, const glm::vec3& normal, std::shared_ptr<Material> material) :
		Object{ material }, //<call object constructor passing material>,
		m_center{ center }, // <set center>,
		m_normal{ normal }  // <set normal>
		
		
	{
	}

	bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) override;

private:
	glm::vec3 m_center{ 0 }; //	<center of the plane>

	glm::vec3 m_normal{ 0 }; // <normal of the plane>

};