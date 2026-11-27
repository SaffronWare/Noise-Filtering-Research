#include "Camera.cuh"

__device__ glm::mat3 Camera::getOrientation()
{
	return orientation;
}

__device__ glm::vec3 Camera::getFront()
{
	return orientation[2];
}

__device__ glm::vec3 Camera::getRight()
{
	return orientation[0];
}

__device__ glm::vec3 Camera::getUp()
{
	return orientation[1];
}

__device__ glm::vec3 Camera::getPixelv(glm::vec2 uv)
{
	return position + glm::vec3(uv, focal_length) * orientation;
}

__device__ Ray Camera::shootRay(glm::vec2 uv)
{
	return Ray::facingPoint(position, getPixelv(uv));
}
