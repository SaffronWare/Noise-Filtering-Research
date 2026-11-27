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