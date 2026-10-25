#pragma once

#include <glm/glm.hpp>

#include "Ray.h"

struct Material
{
	float roughness = 1.0f;

	glm::vec3 albedo;
	glm::vec3 emission;


	float fD(glm::vec3 omega, float FD90, glm::vec3 n);
	glm::vec3 baseDiffuse(glm::vec3 l, glm::vec3 v);

	glm::vec3 BRDF(glm::vec3 light_dir, glm::vec3 radiance_dir, glm::vec3 n);
};

struct HitInfo
{	glm::vec3 p;
	glm::vec3 n;

	Material mat;
	
	float dist;
	bool hit;
};


struct Object
{
	Material mat;
	virtual HitInfo getHit(Ray ray) = 0;
};

struct Sphere : public Object
{
	glm::vec3 position;
	float radius;

	HitInfo getHit(Ray ray) override;
};