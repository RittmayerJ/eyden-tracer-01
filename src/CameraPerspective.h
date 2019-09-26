// Code completed by:
// Author: Jonathan Rittmayer & Jose Villeda
// Date: 09.26.2019

// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"

/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{
public:
	/**
	 * @brief Constructor
	 * @param pos Camera origin (center of projection)
	 * @param dir Camera viewing direction
	 * @param up Up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
	 * @param resolution The image resolution
	 */
	CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)//Vec3f(0, 0, 10), Vec3f(0, 0, -1), Vec3f(0, 1, 0), 60, resolution
		: ICamera(resolution)
		, m_pos(pos)
		, m_dir(dir)
		, m_up(up)
	{
		// --- PUT YOUR CODE HERE ---
		m_focus = 1.f / tanf(angle * Pif / 360);
		m_aspect = resolution.width/float(resolution.height);
		m_zAxis = normalize(m_dir);										//Vec3f(0, 0, 0);
		m_xAxis = normalize(m_zAxis.cross(m_up));			//Vec3f(0, 0, 0);
		m_yAxis = normalize(m_zAxis.cross(m_xAxis));	//Vec3f(0, 0, 0);
	}
	virtual ~CCameraPerspective(void) = default;

	virtual bool InitRay(float x, float y, Ray& ray) override
	{
		float shift = 0.5f;
		float sscx = 2 * (x + shift) / getResolution().width - 1;
		float sscy = 2 * (y + shift) / getResolution().height - 1;
		ray.org = m_pos;
		ray.dir = normalize(m_aspect * sscx * m_xAxis + sscy * m_yAxis + m_focus * m_zAxis);
		ray.t = std::numeric_limits<float>::infinity();

		return true;
	}


private:
	// input values
	Vec3f m_pos;
	Vec3f m_dir;
	Vec3f m_up;

	// preprocessed values
	float m_focus;
	Vec3f m_xAxis;
	Vec3f m_yAxis;
	Vec3f m_zAxis;
	float m_aspect;
};
