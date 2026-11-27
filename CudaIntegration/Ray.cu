#include "Ray.cuh"

__device__ glm::vec3 Ray::pointAt(float t)
{
	return position + t * direction;
}

__device__ Ray Ray::facingPoint(glm::vec3 position, glm::vec3 target)
{
	Ray ray;
	ray.position = position;
	ray.direction = glm::normalize(target - position);
	return ray;
}