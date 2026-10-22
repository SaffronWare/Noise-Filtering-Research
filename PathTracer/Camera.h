#pragma once

#include <glm/glm.hpp>

#include "Ray.h"

struct Camera
{
private:
	glm::mat3 orientation;

public:
	glm::vec3 position;
	float focal_length;

	Ray shootRay(glm::vec2 uv);

	glm::mat4 getOrientation();
	glm::vec3 getFront();
	glm::vec3 getRight();
	glm::vec3 getUp();
	glm::vec3 getPixel(glm::vec2 uv);

	
};