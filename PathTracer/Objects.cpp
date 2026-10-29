#pragma once

#include "Objects.h"

HitInfo Sphere::getHit(Ray ray)
{

	glm::vec3 diff = (ray.position - position);
	float a = 1.0f;
	float b = 2.0f * glm::dot(diff, ray.direction);
	float c = glm::dot(diff, diff) -  radius * radius;

	float d = b * b - 4 * a * c;

	float t = -1;


	if (d == 0)
	{
		t = -b / (2 * a);


	}
	else if (d >= 0)
	{
		// Since a > 1, we are guaranteed, that the negative root gives smallest oslutin.
		if (-b > sqrt(d))
		{
			t = (-b - sqrt(d)) / (2 * a);
		}
		else if (-b > -sqrt(d))
		{
			t = (-b + sqrt(d)) / (2 * a);
		}
	}

	if (t <= 0.0f)
	{
		return HitInfo{ glm::vec3(), glm::vec3(), Material{}, -1, 1 };
	}
	else
	{
		return HitInfo{ ray.pointAt(t), glm::normalize(ray.pointAt(t) - position), mat, t, true };
	}
}



glm::vec3 Material::BRDF(glm::vec3 lightDir, glm::vec3 irrDir, glm::vec3 n)
{
	glm::vec3 h = glm::normalize(lightDir + irrDir);

	float FD90 = 0.5f + 2 * roughness * glm::abs(glm::dot(irrDir, n));

	float FDin = (1 + (FD90 - 1) * glm::pow(1 - glm::dot(irrDir, n), 5.0f));
	float FDout = (1 + (FD90 - 1) * glm::pow(1 - glm::dot(lightDir, n), 5.0f));

	glm::vec3 BaseDiffuse = FDin * FDout * glm::abs(glm::dot(irrDir, n)) * baseColor / std::acosf(-1.0f);
	
	return BaseDiffuse;
}
