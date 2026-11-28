#pragma once

#include "config.h"

__device__ uint32_t PCG(uint32_t& state);

__device__ float random(uint32_t& state);

__device__ glm::vec3 randomHemisphere(uint32_t& state, glm::vec3 normal);