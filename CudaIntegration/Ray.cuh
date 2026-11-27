#pragma once
#include "config.h"


struct Ray
{
	glm::vec3 position;
	glm::vec3 direction;

	__device__ glm::vec3 pointAt(float t);


	__device__ static Ray facingPoint(glm::vec3 position, glm::vec3 target);
};