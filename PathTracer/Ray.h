#pragma once
#include <glm/glm.hpp>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

struct Ray
{
	glm::vec3 position;
	glm::vec3 direction;

	glm::vec3 pointAt(float t);


	static Ray facingPoint(glm::vec3 position, glm::vec3 target);
};