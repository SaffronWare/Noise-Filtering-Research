#include "Camera.cuh"

__device__ glm::mat3 Camera::getOrientation() const
{
	return orientation;
}

__device__ glm::vec3 Camera::getFront() const
{
	return orientation[2];
}

__device__ glm::vec3 Camera::getRight() const 
{
	return orientation[0];
}

__device__ glm::vec3 Camera::getUp() const
{
	return orientation[1];
}

__device__ glm::vec3 Camera::getPixelv(glm::vec2 uv) const 
{
	return position + glm::vec3(uv, focal_length) * orientation;
}

__device__ Ray Camera::shootRay(glm::vec2 uv) const
{
	return Ray::facingPoint(position, getPixelv(uv));
}
