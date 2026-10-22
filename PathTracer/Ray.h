#pragma once
#include <glm/glm.hpp>

struct Ray
{
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 color;

	glm::vec3 pointAt(float t);


	static Ray facingPoint(glm::vec3 position, glm::vec3 target);
};