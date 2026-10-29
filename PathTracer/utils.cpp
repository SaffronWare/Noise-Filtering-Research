#include "utils.h"	

#include <random>

namespace Utils
{
	glm::vec3 randomOnHemisphere(glm::vec3 n)
	{
		glm::vec3 v = glm::sphericalRand(1.0f);
		if (glm::dot(v, n) > 0)
		{
			return v;
		}
		return -v;
	}
}