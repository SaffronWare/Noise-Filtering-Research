#pragma once

#include <glm/glm.hpp>

#include "Ray.h"

struct HitInfo
{	glm::vec3 p;
	glm::vec3 n;

	Material mat;
	
	float dist;
	bool hit;
};

struct Material
{
	glm::vec3 albedo;
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