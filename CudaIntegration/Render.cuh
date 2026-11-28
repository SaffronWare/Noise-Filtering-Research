#pragma once
#include "config.h"
#include "Camera.cuh"
#include "Scene.cuh"

#define MAX_TRACE_STEPS 5

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
	Scene scene;
};

__global__ void renderPassKernel(RenderData* data, RenderConfig config);

RenderData render(RenderConfig config);