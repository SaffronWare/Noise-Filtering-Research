#include "CudaRand.cuh"

__device__ uint32_t PCG(uint32_t& state)
{
    state = state * 747796405u + 2891336453u;
    uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}

__device__ float random(uint32_t& state)
{
    uint32_t ruint32_t = PCG(state);
    return (ruint32_t >> 8u) / (float(1 << 24u));
}

__device__ glm::vec3 randomHemisphere(uint32_t& state, glm::vec3 n)
{
    float z = random(state);
    float theta = 2.0f * MPI * random(state);

    float r =  std::sqrtf(1 - z * z);
    glm::vec3 rand = glm::vec3(r * std::cosf(theta), std::sinf(theta) * r, z);
    if (glm::dot(rand, n) < 0.0f)
    {
        return -rand;
    }
    return rand;
}