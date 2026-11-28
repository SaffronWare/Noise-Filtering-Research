#pragma once

#include "config.h"

#include "Ray.cuh"



struct Camera
{
private:
	glm::mat3 orientation = glm::mat3{glm::vec3(1,0,0), glm::vec3(0,1,0), glm::vec3(0,0,1)};

public:
	glm::vec3 position = glm::vec3(0,0,0);
	float focal_length = 1.0f;

	Camera() = default;
	~Camera() = default;
	
	__device__ Ray shootRay(glm::vec2 uv) const;

	__device__ glm::mat3 getOrientation() const;
	__device__ glm::vec3 getFront() const;
	__device__ glm::vec3 getRight() const ;
	__device__ glm::vec3 getUp() const;
	__device__ glm::vec3 getPixelv(glm::vec2 uv) const;

	
};