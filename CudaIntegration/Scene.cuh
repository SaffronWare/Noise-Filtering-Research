#pragma once
#include <vector>
#include "config.h"
#include "Ray.cuh"

#define MAX_HIT_DIST 100

struct HitInfo;

struct ShadingFrame
{
	glm::vec3 x;
	glm::vec3 y;
	glm::vec3 z;

	__device__ glm::vec3 toFrame(glm::vec3 v);
};

struct Material
{
	float roughness = 1.0f;
	float emissionStrength = 0.0f;
	float subsurface = 0.0f;
	float anisotropic = 0.0f;
	float mettalic = 0.0f;
	float specular = 0.0f;
	float specularTint = 1.0f;
	float clearcoatGloss = 0.0f;
	float clearcoat = 0.0f;


	glm::vec3 emissionColor = glm::vec3(1.0f);
	glm::vec3 baseColor = glm::vec3(1.0f);
	glm::vec3 anisoBasis = glm::vec3(1, 0, 0);

	__device__ glm::vec3 BRDF(glm::vec3 light_dir, glm::vec3 radiance_dir, glm::vec3 n);

	__device__ ShadingFrame getFrame(glm::vec3 n);
};

struct Sphere
{
	Material mat;
	glm::vec3 position;
	float radius;

	__device__ HitInfo getHit(Ray ray);
};

struct Plane
{
	Material mat;
	glm::vec3 position;
	glm::vec3 normal;

	__device__ HitInfo getHit(Ray ray);
};

struct Rect
{
	Material mat;
	glm::vec3 center;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 dimensions;

	__device__ HitInfo getHit(Ray ray);
};

struct HitInfo
{
	glm::vec3 p;
	glm::vec3 n;

	Material mat;

	float dist;
	bool hit;
};

struct Scene
{
	Sphere* sspheres = nullptr;
	Plane* splanes = nullptr;
	Rect* srects = nullptr;
	int n_spheres = 0;
	int n_planes = 0;
	int n_rects = 0;

	__host__ void Load(std::vector<Sphere> spheres, std::vector<Plane> planes, std::vector<Rect> rects);
	__host__ void unLoad();

	__device__ HitInfo getHit(Ray ray);

	Scene() = default;
	~Scene();
	Scene(Scene&& other);
	Scene(const Scene& other) = delete;
	Scene& operator=(const Scene& other) = delete;
};