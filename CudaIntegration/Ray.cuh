#pragma once
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <glm/glm.hpp>


struct Ray
{
	glm::vec3 position;
	glm::vec3 direction;

	__device__ glm::vec3 pointAt(float t);


	__device__ static Ray facingPoint(glm::vec3 position, glm::vec3 target);
};