#include "Render.cuh"

void RenderData::alloc()
{
	dealloc();
	CUDA_CHECK(cudaMallocManaged(&data, 3 * width * height * sizeof(float)));
}

void RenderData::dealloc()
{
	if (data != nullptr)
	{
		CUDA_CHECK(cudaFree(data));
	}
	data = nullptr;
}

RenderData::RenderData()
{
	data = nullptr;
}

RenderData::~RenderData()
{
	dealloc();
}