#pragma once
#include <memory>
#include "Material.h"

class Object
{
public:
	// SETUP OBJECT WITH ITS MATERIAL

	// <add a constructor that takes a shared_ptr<Material>>
	Object() = default;
	// define constructor for object /          // initialization list for member variables for class Material / "material" is passed to constructor
	Object(std::shared_ptr<Material> material) : m_material{ material } {}

	// <add a pure virtual Hit() method> / can be overridden by derived classes / 
	virtual bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) = 0;

	// GetMaterial() method to return raw pointer to Material
	Material* GetMaterial() { return m_material.get(); } // <return the material.get()> raw pointer

protected:
	// <add a shared_ptr<Material> member variable>
	std::shared_ptr<Material> m_material; // shared pointer to Material
};
																																																														