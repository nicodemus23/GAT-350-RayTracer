#pragma once
#include "Ray.h"
#include "Color.h"

class Material
{
public: 
	// <pure virtual Scatter() method> / can be overridden by derived classes / const qualifier means that the method cannot modify the object's state
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, Color::color3_t& color, ray_t& scattered) const = 0;// <make this pure virtual>
};
// <derive from Material>
class Lambertian : public Material
{
public: // pass as const reference to albedo 
	Lambertian(const Color::color3_t albedo) : m_albedo{ albedo } {}
	// <override the Scatter() method>
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, Color::color3_t& color, ray_t& scattered) const override {  //the parent Scatter() method>
		// <calculate the scatter direction>//
		color = m_albedo;
		return true;
	}

protected:
	// <add albedo member variable>
	Color::color3_t m_albedo;
};