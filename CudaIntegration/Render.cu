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

__global__ void renderPassKernel(float* data, RenderConfig config, uint32_t seed)
{
	int width = config.width;
	int height = config.height;
	int ix = blockIdx.x * blockDim.x + threadIdx.x;
	int iy = blockIdx.y * blockDim.y + threadIdx.y;

	uint32_t state = 7712985 * seed + 9174512 * ix + 1259230 * iy;

	Ray ray;

	// cannot do recursion anymore ll.

	if (ix < width && iy < height)
	{
		int widx = ix + iy * width;

		float u = (ix - 0.5f * (width - 1)) / (float)(height - 1);
		float v = (float)(iy) / (float)(height - 1) - 0.5f;

		ray = config.cam.shootRay(glm::vec2(u, v));
		Ray init = ray;

		glm::vec3 pixel_color = glm::vec3(0);

		HitInfo currhit;
		
		for (int j = 0; j < 1000; j++)
		{
			glm::vec3 current_ray_tint = glm::vec3(1);
			for (int i = 0; i < MAX_TRACE_STEPS; i++)
			{
				currhit = config.scene.getHit(ray);

				if (!currhit.hit)
				{
					break;
				}


				glm::vec3 new_dir = randomHemisphere(state, currhit.n);


				pixel_color += currhit.mat.emissionColor * currhit.mat.emissionStrength * current_ray_tint; // with recursion, pixelcolor = l0 + c0 * (l1 + c1 * (l2 + c2  l3 +

				current_ray_tint *= currhit.mat.BRDF(new_dir, -ray.direction, currhit.n) * glm::dot(new_dir, currhit.n) * (2.0f * MPI);

				ray.direction = new_dir;
				ray.position = currhit.p + currhit.n * 0.00001f;

			}
			ray = init;
		}
		pixel_color /= 100.0f;
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


	
	renderPassKernel <<<blocks, threads>>> (data.data, config, rand());
	CUDA_CHECK(cudaGetLastError());
	CUDA_CHECK(cudaDeviceSynchronize());


	return data;

}