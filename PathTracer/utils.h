#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

#include <stdexcept>
#include <iostream>
#include <string>

#define VALCHECKS

#ifdef VALCHECKS
	#define valCheck(...) Utils::_valCheck(__VA_ARGS__)
#else VALCHECKS
	#define valCheck(v, ...) (v) 
#endif 


namespace Utils
{	
	glm::vec3 randomOnHemisphere(glm::vec3 n);

	float _valCheck(float v, std::string name, float defv = 0);
	glm::vec3 _valCheck(glm::vec3 v, std::string name, glm::vec3 defv = glm::vec3(0.0f));
}