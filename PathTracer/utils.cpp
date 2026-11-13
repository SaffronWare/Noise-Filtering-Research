#include "utils.h"	

#include <random>

namespace Utils
{
	glm::vec3 randomOnHemisphere(glm::vec3 n)
	{
		thread_local std::mt19937 generator(std::random_device{}());
		thread_local std::normal_distribution<float> gauss(0.0f, 1.0f);



		glm::vec3 v = glm::normalize(glm::vec3(gauss(generator), gauss(generator),gauss(generator)));
		if (glm::dot(v, n) > 0)
		{
			return v;
		}
		return -v;
	}

	float valCheck(float v, std::string name, float defv)
	{
		if (std::isnan(v) || std::isinf(v))
		{
#ifdef VALCHECKS
			std::cerr << "-------------------\n";
			std::cerr << "NOVAL AT " << name << std::endl;
			std::cerr << v << std::endl;
			std::cerr << "-------------------\n";
#endif
			
			return defv;
		}
		return v;
	}

	glm::vec3 valCheck(glm::vec3 v, std::string name, glm::vec3 defv)
	{
		if (glm::any(glm::isinf(v)) || glm::any(glm::isnan(v)))
		{
#ifdef VALCHECKS
			std::cerr << "--------------------\n";
			std::cerr << "NOVAL AT " << name << std::endl;
			std::cerr << v.x << std::endl;
			std::cerr << v.y << std::endl;
			std::cerr << v.z << std::endl;
			std::cerr << "-------------------\n";
#endif
			return defv;
		}
		return v;
	}
}