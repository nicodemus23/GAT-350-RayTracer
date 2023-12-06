#include "Camera.h"
#include "MathUtils.h"
#include <iostream>

Camera::Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, float fov, float aspectRatio) :
	m_fov{ fov },
	m_aspectRatio{ aspectRatio }
{
	LookAt(eye, target, up);
}

void Camera::LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{

	m_eye = eye;

	// set the camera axis vectors (forward, right, up)
	// use cross product to create vectors
	//m_forward = glm::normalize(eye - target); // forward vector (eye <- target)
	m_forward = glm::normalize(target - eye); // forward vector (eye <- target)
	m_right = glm::normalize(MathUtils::cross(up, m_forward)); // right = up x forward 
	m_up = MathUtils::cross(m_forward, m_right); // up = forward x right (already normalized since both of those vectors were already normalized

	// debug: print camera vectors
	std::cout << "Camera Vectors after LookAt:" << std::endl;
	std::cout << "Forward: (" << m_forward.x << ", " << m_forward.y << ", " << m_forward.z << ")" << std::endl;
	std::cout << "Right: (" << m_right.x << ", " << m_right.y << ", " << m_right.z << ")" << std::endl;
	std::cout << "Up: (" << m_up.x << ", " << m_up.y << ", " << m_up.z << ")" << std::endl;


	CalculateViewPlane();
}

void Camera::CalculateViewPlane()
{
	// convert fov angle (degrees) to radians
	float theta = glm::radians(m_fov);

	// calculate the width / height of the view plane
	float halfHeight = tan(theta * 0.5f);
	float height = 2 * halfHeight;
	float width = height * m_aspectRatio;

	// calculate horizontal vector (right vector * width)
	m_horizontal = m_right * width;
	// calculate vertical vector (up vector * height)
	m_vertical = m_up * height;
	// calculate lower left location (origin)
	m_lowerLeft = m_eye - (m_horizontal * 0.5f) - (m_vertical * 0.5f) - m_forward;

	// debug: print camera vectors
	std::cout << "Camera Vectors after CalculateViewPlane:" << std::endl;
	std::cout << "Horizontal: (" << m_horizontal.x << ", " << m_horizontal.y << ", " << m_horizontal.z << ")" << std::endl;
	std::cout << "Vertical: (" << m_vertical.x << ", " << m_vertical.y << ", " << m_vertical.z << ")" << std::endl;
	std::cout << "Lower Left: (" << m_lowerLeft.x << ", " << m_lowerLeft.y << ", " << m_lowerLeft.z << ")" << std::endl;
}

ray_t Camera::GetRay(const glm::vec2& point) const
{
	ray_t ray;
	// the ray origin is the camera eye
	ray.origin = m_eye;
	// calculate direction from point
	ray.direction = m_lowerLeft + (m_horizontal * point.x) + (m_vertical * point.y) - m_eye;

	// Print ray for the center of the screen (NDC (0.5, 0.5))
	if (point.x == 0.5f && point.y == 0.5f)
	{
		std::cout << "Ray direction for center (NDC 0.5, 0.5): ("
			<< ray.direction.x << ", "
			<< ray.direction.y << ", "
			<< ray.direction.z << ")" << std::endl;
	}


	return ray;
}


