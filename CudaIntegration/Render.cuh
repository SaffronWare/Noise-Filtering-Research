#pragma once
#include <glm/glm.hpp>
#include "debug.h"
#include "Camera.cuh"

struct RenderData
{
	
	unsigned int width;
	unsigned int height;
	float* data;


	RenderData();
	~RenderData();

	void alloc();
	void dealloc();
};

struct RenderConfig
{
	int width;
	int height;
	Camera cam;
};