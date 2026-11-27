#include "Ray.cuh"

__device__ glm::vec3 Ray::pointAt(float t)
{
	return position + t * direction;
}

__device__ Ray Ray::facingPoint(glm::vec3 position, glm::vec3 target)
{
	
	return Ray{ position, glm::normalize(target - position) };
}