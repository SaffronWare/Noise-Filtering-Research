#pragma once

#include "Objects.h"

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

	glm::vec3 inDir;
	glm::vec3 outDir;

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

	float FD(glm::vec3 dir);
	float FSS(glm::vec3 dir);

	float G(glm::vec3 fdir);
	float Lambda(glm::vec3 fdir);

	float R0(float ior);




	glm::vec3 BaseDiffuse();
	glm::vec3 SubsurfaceDiffuse();
	glm::vec3 Diffuse();
	glm::vec3 Metallic();

	glm::vec3 EvaluateBrdf(glm::vec3 inDir, glm::vec3 outDir, glm::vec3 normal);
	
};