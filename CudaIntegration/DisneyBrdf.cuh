#pragma once
#include "Scene.cuh"

constexpr float PI = 3.1415926f;
constexpr float alphamin = 0.0001f;
constexpr float clearcoat_eta = 1.5f;


struct DisneyBrdf
{
	Material mat;
	ShadingFrame frame;
	glm::vec3 in;
	glm::vec3 out;
	glm::vec3 n;
	glm::vec3 h;

	glm::vec3 hl;
	glm::vec3 inl;
	glm::vec3 outl;


	float FD90;
	float FSS90;


	glm::vec3 Ctint;
	glm::vec3 C0;
	glm::vec3 KS;
	float aspect;
	float alphax;
	float alphay;
	glm::vec3 Fm;
	float Gm;
	float Dm;

	float alphac;
	float Gc;
	float Dc;
	float Fc;

	__device__ float FD(glm::vec3 dir);
	__device__ float FSS(glm::vec3 dir);

	__device__ float G(glm::vec3 fdir);
	__device__ float Lambda(glm::vec3 fdir);

	__device__ float R0(float ior);


	__device__ float LambdaC(glm::vec3 fdir);
	__device__ float GC(glm::vec3 fdir);

	__device__ glm::vec3 BaseDiffuse();
	__device__ glm::vec3 SubsurfaceDiffuse();
	__device__ glm::vec3 Diffuse();
	__device__ glm::vec3 Metallic();
	__device__ glm::vec3 Clearcoat();

	__device__ glm::vec3 EvaluateBrdf(glm::vec3 inDir, glm::vec3 outDir, glm::vec3 normal);

};