#pragma once
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <glm/glm.hpp>

#include "Ray.cuh"



struct Camera
{
private:
	glm::mat3 orientation = glm::mat3{glm::vec3(1,0,0), glm::vec3(0,1,0), glm::vec3(0,0,-1)};

public:
	glm::vec3 position;
	float focal_length;

	Camera() = default;
	~Camera() = default;
	
	__device__ Ray shootRay(glm::vec2 uv);

	__device__ glm::mat4 getOrientation();
	__device__ glm::vec3 getFront();
	__device__ glm::vec3 getRight();
	__device__ glm::vec3 getUp();
	__device__ glm::vec3 getPixelv(glm::vec2 uv);

	
};