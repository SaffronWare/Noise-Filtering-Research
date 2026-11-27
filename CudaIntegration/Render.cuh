#pragma once
#include <glm/glm.hpp>
#include "debug.h"

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
};