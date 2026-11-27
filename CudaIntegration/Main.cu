
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cmath>
#include <iostream>
#include "Render.cuh"
#include "Export.h"

#include "debug.h"




__global__ void renderPassKernel(float* data, RenderConfig config)
{
	int width = config.width;
	int height = config.height;
	int ix = blockIdx.x * blockDim.x + threadIdx.x;
	int iy = blockIdx.y * blockDim.y + threadIdx.y;

	if (ix < width && iy < height)
	{
		int widx = ix + iy * height;

		float u = (ix + 1.0f) / (float)(width);
		float v = (iy + 1.0f) / (float)(height);



		data[3 * widx + 0] = u;
		data[3 * widx + 1] = v;
		data[3 * widx + 2] = 1.0f;
	}
}




RenderData render(RenderConfig config)
{
	RenderData data{};
	data.width = config.width;
	data.height = config.height;
	data.alloc();

	const static int num_threads_per_block = 16;

	dim3 threads(num_threads_per_block, num_threads_per_block);
	dim3 blocks((config.width + num_threads_per_block - 1) / num_threads_per_block, 
		(config.height + num_threads_per_block - 1) / num_threads_per_block);


	renderPassKernel<<<blocks,threads>>>(data.data, config);

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