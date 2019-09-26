// Code completed by:
// Author: Jonathan Rittmayer & Jose Villeda
// Date: 09.26.2019

// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Triangle Geaometrical Primitive class
 */
class CPrimTriangle : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 */
	CPrimTriangle(Vec3f color, Vec3f a, Vec3f b, Vec3f c)
		: CPrim(color)
		, m_a(a)
		, m_b(b)
		, m_c(c)
  	{}
	virtual ~CPrimTriangle(void) = default;

	virtual bool Intersect(Ray& ray) override{
		// ---  PUT YOUR CODE HERE ---
		const Vec3f e1 = m_b - m_a;
		const Vec3f e2 = m_c - m_a;
		const Vec3f pvector = ray.dir.cross(e2);
		const float det = e1.dot(pvector);

		if(fabs(det) < Epsilon){
			return false;
		}

		const float inverse_det = 1.0f / det;
		const Vec3f tvector = ray.org - m_a;
		float lambda = tvector.dot(pvector);
		lambda *= inverse_det;
		if(lambda < 0.0f){
			return false;
		}
		const Vec3f qvector = tvector.cross(e1);
		float mue = ray.dir.dot(qvector);
		mue *= inverse_det;
		if(mue + lambda > 1.0f){
			return false;
		}
		float f = e2.dot(qvector);
		f = f * inverse_det;
		if(ray.t <= f || f <  1E-4 ){
			return false;
		}
		ray.t = f;

		return true;
}


private:
	Vec3f m_a;	///< Position of the first vertex
	Vec3f m_b;	///< Position of the second vertex
	Vec3f m_c;	///< Position of the third vertex
};
