
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cmath>
#include <iostream>


__global__ void vecAdd(float* A, float* B, float* C, int length)
{
	int index = blockIdx.x * blockDim.x + threadIdx.x;

	if (index < length)
	{
		C[index] = A[index] + B[index];
	}
}

int main()
{
	int length = 4;

	float* A = nullptr;
	float* B = nullptr;
	float* C = nullptr;

	cudaMallocManaged(&A, length * sizeof(float));
	cudaMallocManaged(&B, length * sizeof(float));
	cudaMallocManaged(&C, length * sizeof(float));
	A[0] = 1;
	A[1] = 2;
	A[2] = 3;
	A[3] = 4;
	B[0] = 4;
	B[1] = 3;
	B[2] = 2;
	B[3] = 1;
	


	int threads = 256;
	int blocks = (length + threads - 1) / threads;
	vecAdd<<<blocks, 256 >>>(A, B, C, length);

	cudaDeviceSynchronize();

	std::cout << "Launch: "
		<< cudaGetErrorString(cudaGetLastError()) << "\n";

	std::cout << "Sync: "
		<< cudaGetErrorString(cudaDeviceSynchronize()) << "\n";

	std::cout << C[0] << " " << C[1] << " " << C[2] << " " << C[3] << "\n";



	cudaFree(A);
	cudaFree(B);
	cudaFree(C);

}