#pragma once
#include "config.h"
#include "Camera.cuh"

struct RenderData
{
	
	unsigned int width;
	unsigned int height;
	float* data = nullptr;


	RenderData();
	~RenderData();
	RenderData(RenderData&& other);
	RenderData(const RenderData& other) = delete;
	RenderData& operator=(const RenderData& other) = delete;

	void alloc();
	void dealloc();
};

struct RenderConfig
{
	int width;
	int height;
	Camera cam;
};