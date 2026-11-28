#include "Render.cuh"

void RenderData::alloc()
{
	std::cout << "constructor check: " << data << std::endl;
	std::cout << "try to dealloc\n" << std::endl;
	dealloc();
	CUDA_CHECK(cudaMallocManaged(&data, 3 * width * height * sizeof(float)));
}

void RenderData::dealloc()
{
	std::cout << data << std::endl;
	if (data != nullptr)
	{
		std::cout << "data was not nullptr: " << data << " " << (data == nullptr) << std::endl;
		CUDA_CHECK(cudaFree(data));
	}
	data = nullptr;
}

RenderData::RenderData() {}

RenderData::~RenderData()
{
	std::cout << "try to delete\n";
	dealloc();
}

RenderData::RenderData(RenderData&& other)
{
	width = other.width;
	height = other.height;
	data = other.data;
	other.data = nullptr;

}

__global__ void renderPassKernel(float* data, RenderConfig config)
{
	int width = config.width;
	int height = config.height;
	int ix = blockIdx.x * blockDim.x + threadIdx.x;
	int iy = blockIdx.y * blockDim.y + threadIdx.y;

	Ray ray;

	// cannot do recursion anymore ll.

	if (ix < width && iy < height)
	{
		int widx = ix + iy * width;

		float u = (ix - 0.5f * (width - 1)) / (float)(height - 1);
		float v = (float)(iy) / (float)(height - 1) - 0.5f;

		ray = config.cam.shootRay(glm::vec2(u, v));

		glm::vec3 pixel_color = glm::vec3(0);

		HitInfo currhit;
		currhit = config.scene.getHit(ray);

		if (currhit.hit)
		{
			pixel_color = glm::vec3(1, 1, 1);
		}
		else
		{

		}
		
		data[3 * widx + 0] = pixel_color.x;
		data[3 * widx + 1] = pixel_color.y;
		data[3 * widx + 2] = pixel_color.z;
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


	
	renderPassKernel <<<blocks, threads>>> (data.data, config);
	CUDA_CHECK(cudaGetLastError());
	CUDA_CHECK(cudaDeviceSynchronize());


	return data;

}