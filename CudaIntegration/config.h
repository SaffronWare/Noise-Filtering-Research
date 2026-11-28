#pragma once

#define GLM_FORCE_CUDA
#include <iostream>
#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <glm/glm.hpp>

#ifndef __CUDACC__
    #define __device__
    #define __host__
    #define __global__
    #define __shared__
    #define __constant__
    #define __managed__
#endif

#define DEBUG

#ifdef DEBUG
#define CUDA_CHECK(expr_to_check) do {            \
    cudaError_t result  = expr_to_check;          \
    if(result != cudaSuccess)                     \
    {                                             \
        fprintf(stderr,                           \
                "CUDA Runtime Error: %s:%i:%d = %s\n", \
                __FILE__,                         \
                __LINE__,                         \
                result,\
                cudaGetErrorString(result));      \
    }                                             \
} while(0)
#else 
#define CUDA_CHECK
#endif