#pragma once

#include <glm/glm.hpp>
#include <iostream>

#include "Ray.h"


struct ShadingFrame
{
	glm::vec3 x;
	glm::vec3 y;
};

struct Material
{
	float roughness = 1.0f;
	float emissionStrength = 0.0f;

	glm::vec3 emissionColor;
	glm::vec3 baseColor;
	glm::vec3 anisoBais = glm::vec3(1, 0, 0);

	glm::vec3 BRDF(glm::vec3 light_dir, glm::vec3 radiance_dir, glm::vec3 n);

	virtual ShadingFrame getFrame(HitInfo hit);
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

struct Plane : public Object
{
	glm::vec3 position;
	glm::vec3 normal;

	HitInfo getHit(Ray ray) override;
};


struct Rect : public Object
{
	glm::vec3 center;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec2 dimensions;


	HitInfo getHit(Ray ray) override;
};