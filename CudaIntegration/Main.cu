#include "config.h"
#include <cmath>
#include <iostream>
#include "Render.cuh"
#include "Export.h"



__global__ void renderPassKernel(float* data, RenderConfig config)
{
	int width = config.width;
	int height = config.height;
	int ix = blockIdx.x * blockDim.x + threadIdx.x;
	int iy = blockIdx.y * blockDim.y + threadIdx.y;

	Ray ray;


	if (ix < width && iy < height)
	{
		int widx = ix + iy * width;

		float u = (ix - 0.5f * (width-1)) / (float)(height-1);
		float v = (float)(iy) / (float)(height-1) - 0.5f;

		ray = config.cam.shootRay(glm::vec2(u,v));

		data[3 * widx + 0] = ray.direction.x;
		data[3 * widx + 1] = ray.direction.y;
		data[3 * widx + 2] = ray.direction.z;
	}
}




RenderData render(RenderConfig config)
{
	RenderData data;
	data.width = config.width;
	data.height = config.height;
	data.alloc();

	const static int num_threads_per_block = 16;

	dim3 threads(num_threads_per_block, num_threads_per_block);
	dim3 blocks((config.width + num_threads_per_block - 1) / num_threads_per_block, 
		(config.height + num_threads_per_block - 1) / num_threads_per_block);


	renderPassKernel<<<blocks,threads>>>(data.data, config);
	CUDA_CHECK(cudaGetLastError());
	CUDA_CHECK(cudaDeviceSynchronize());


	return data;

}

int main()
{
	RenderConfig config;
	config.width = 100;
	config.height = 100;
	config.cam = Camera();
	RenderData data = render(config);
	

	Exporter::RenderToPPM(data, "test.ppm");

}