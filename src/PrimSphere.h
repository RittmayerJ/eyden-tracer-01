// Code completed by:
// Author: Jonathan Rittmayer & Jose Villeda
// Date: 09.26.2019

// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param center Position of the center of the sphere
	 * @param radius Radius of the sphere
	 */
	CPrimSphere(Vec3f color, Vec3f center, float radius)
		: CPrim(color)
		, m_center(center)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;


virtual bool Intersect(Ray &ray) override{
	// --- PUT  YOUR CODE HERE ---
		Vec3f difference = ray.org - m_center;
		float a = ray.dir.dot(ray.dir);
		float b = 2 * ray.dir.dot(difference);
		float m_radSqrt = m_radius * m_radius;
		float c = difference.dot(difference) - m_radSqrt;
		float discriminant = (b * b) - (4 * a * c);

		float d_root = sqrtf(discriminant);
		float distance = ((-b) - d_root) / (2 * a);

		if(distance < Epsilon){
			distance = (-b + d_root) / (2 * a);
			if(distance > ray.t || distance < Epsilon){
				return false;
			}
		}
		ray.t = distance;

	return true;
}


private:
	Vec3f m_center;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};
