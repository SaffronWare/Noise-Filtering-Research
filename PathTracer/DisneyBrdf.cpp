#include "DisneyBrdf.h"

using namespace glm;

glm::vec3 DisneyBrdf::EvaluateBrdf(glm::vec3 inDir, glm::vec3 outDir, glm::vec3 normal)
{
	in = inDir;
	out = outDir;

	frame = mat.getFrame(normal);
	n = frame.z;
	h = normalize(inDir + outDir);

	hl = valCheck(frame.toFrame(h), "H FRAME BRDF");
	inl = valCheck(frame.toFrame(in), "IN FRAME BRDF");
	outl = valCheck(frame.toFrame(out), "OUT FRAME BRDF");

	if (dot(n, in) <= 0.0001f || dot(n, out) <= 0.0001f)
	{
		return glm::vec3(0.0f);
	}

	Ctint = mat.baseColor / dot(vec3(0.3, 0.6, 0.1), mat.baseColor);

	return valCheck((1 - mat.mettalic) * Diffuse() +  Metallic() + 0.25f * mat.clearcoat * Clearcoat(), "BRDF RETURN STEP");
	
}

float DisneyBrdf::FD(glm::vec3 dir)
{
	 return valCheck(1.0f + (FD90 - 1.0f) * (pow(1.0f - dot(dir, n), 5.0f)), "FD BRDF STEP");
}

glm::vec3 DisneyBrdf::BaseDiffuse()
{
	FD90 = 0.5f + 2 * mat.roughness * pow(dot(out, h), 2.0f);
	return valCheck(mat.baseColor * FD(in) * FD(out) / PI, "BASE DIFFUSE BRDF STEP");
}

float DisneyBrdf::FSS(glm::vec3 dir)
{
	return valCheck(1.0f + (FSS90 - 1.0f) * (pow(1.0f - dot(dir, n), 5.0f)), "FSS BRDF STEP");
}

glm::vec3 DisneyBrdf::SubsurfaceDiffuse()
{
	FSS90 = mat.roughness * pow(dot(h, out), 2.0f);
	return valCheck(1.25f * mat.baseColor * (FSS(in) * FSS(out) *
		(1.0f /
			(dot(n, in) + dot(n, out))
			- 0.5f)
		+ 0.5f)/ PI, "SUBSURFACE DIFFUSE BRDF STEP");
}

glm::vec3 DisneyBrdf::Diffuse()
{
	return valCheck((1 - mat.subsurface) * BaseDiffuse() + mat.subsurface * SubsurfaceDiffuse(),
		"DIFFUSE STEP");
}

float DisneyBrdf::Lambda(glm::vec3 fdir)
{
	return valCheck(0.5f * sqrt(1.0f + (pow(fdir.x*alphax, 2.0f) + pow(fdir.y*alphay, 2.0f)) / pow(fdir.z, 2.0f)) - 0.5f,
		"LAMBDA BRDF STEP", INFINITY);
}

float DisneyBrdf::G(glm::vec3 fdir)
{
	return valCheck(1.0f / (1.0f + Lambda(fdir)), "G");
}

glm::vec3 DisneyBrdf::Metallic()
{
	aspect = sqrt(1.0f - 0.9f * mat.anisotropic);
	alphax = std::fmaxf(alphamin, mat.roughness * mat.roughness / aspect);
	alphay = std::fmaxf(alphamin, mat.roughness * mat.roughness * aspect);


	KS = (1.0f - mat.specularTint) + mat.specularTint * Ctint;
	C0 = mat.specular * R0(clearcoat_eta) * (1 - mat.mettalic) * KS + mat.mettalic * mat.baseColor;
	Fm = C0 + (1.0f - C0)*(pow(1.0f - dot(h, out), 5.0f));
	Dm = 1.0f / (
		PI * alphax * alphay * pow((pow(hl.x / alphax, 2.0f) + pow(hl.y / alphay, 2.0f) + pow(hl.z, 2.0f)),2.0f)
		);
	Gm = G(inl) * G(outl);
	return valCheck(0.25f * Fm * Dm * Gm / dot(n, in) / dot(n,out), "METALLIC BRDF STEP");


}

float DisneyBrdf::R0(float ior)
{
	return valCheck(pow((ior - 1.0f) / (ior + 1.0f), 2.0f), "R0 STEP");
}

float DisneyBrdf::LambdaC(glm::vec3 fdir)
{
	return valCheck(0.5f * std::sqrtf(1.0f + (std::powf(0.25f * fdir.x, 2.0f) + std::powf(0.25f * fdir.y, 2.0f)) / (fdir.z * fdir.z)) - 0.5f,
		"LAMBDA C DIFFUSE STEP");
}

float DisneyBrdf::GC(glm::vec3 fdir)
{
	return valCheck(1.0f / (1.0f + LambdaC(fdir)), "GC BRDF STEP");
}

glm::vec3 DisneyBrdf::Clearcoat()
{
	alphac = (1.0f - mat.clearcoatGloss) * 0.1f + mat.clearcoatGloss * 0.001f;

	Fc = R0(clearcoat_eta) + (1.0f - R0(clearcoat_eta)) * pow(1 - dot(h, out), 5.0f);
	Dc = (alphac * alphac - 1.0f) / (
		PI * std::logf(alphac * alphac) * (1.0f + (alphac * alphac - 1.0f) * hl.z * hl.z)
		);
	Gc = GC(inl) * GC(outl);
	return valCheck(glm::vec3(1.0f) * 4.0f * Fc * Dc * Gc / (dot(n, in) * dot(n, out)), 
		"CLEARCOAT BRDF STEP");
}







