#pragma once

#include <glm/glm.hpp>

#include "Ray.h"

struct Camera
{
private:
	glm::mat3 orientation = glm::mat3{glm::vec3(1,0,0), glm::vec3(0,1,0), glm::vec3(0,0,-1)};

public:
	glm::vec3 position;
	float focal_length;

	Ray shootRay(glm::vec2 uv);

	glm::mat4 getOrientation();
	glm::vec3 getFront();
	glm::vec3 getRight();
	glm::vec3 getUp();
	glm::vec3 getPixelv(glm::vec2 uv);

	
};