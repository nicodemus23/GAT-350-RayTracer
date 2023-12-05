#include "Material.h"
#include "Random.h"


bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, Color::color3_t& color, ray_t& scattered) const
{
	glm::vec3 target = raycastHit.point + raycastHit.normal + Random::randomInUnitSphere();
	// 
	glm::vec3 direction = glm::normalize(target - raycastHit.point); 

	scattered = { raycastHit.point, direction };
	color = m_albedo;

	return true;
}

bool Metal::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const
{
	glm::vec3 reflected = reflect(glm::normalize(ray.direction), raycastHit.normal);//<get reflected ray from normalized ray direction and raycast hit normal>;

	// set scattered ray from reflected ray + random point in sphere (fuzz = 0 no randomness, fuzz = 1 random reflected)
	// a mirror has a fuzz value of 0 and a diffused metal surface a higher value
	scattered = ray_t{ raycastHit.point, reflected + Random::randomInUnitSphere() * m_fuzz };
	color = m_albedo;
	// make sure that reflected ray is going away from surface normal (dot product > 0, angle between vectors < 90 degrees)
	return glm::dot(scattered.direction, raycastHit.normal) > 0;
}