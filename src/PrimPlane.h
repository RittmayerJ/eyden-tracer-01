// Code completed by:
// Author: Jonathan Rittmayer & Jose Villeda
// Date: 09.26.2019

// Plane Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief The Plane Geaometrical Primitive class
 */
class CPrimPlane : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param origin Point on the plane
	 * @param normal Normal to the plane
	 */
	CPrimPlane(Vec3f color, Vec3f origin, Vec3f normal)
		: CPrim(color)
		, m_normal(normal)
		, m_origin(origin)
	{
		normalize(m_normal);
	}
	virtual ~CPrimPlane(void) = default;

	virtual bool Intersect(Ray& ray) override{
		// --- PUT YOUR CODE HERE ---
		Vec3f p0 = m_origin - ray.org;
		Vec3f p1 = m_normal;
		float denominator = ray.dir.dot(m_normal);
		float t = (p0).dot(p1) / denominator;
		if (t < Epsilon || t > ray.t){
			return false;
		}
		ray.t = t;
		return true;
	}


private:
	Vec3f m_normal;	///< Point on the plane
	Vec3f m_origin;	///< Normal to the plane
};
