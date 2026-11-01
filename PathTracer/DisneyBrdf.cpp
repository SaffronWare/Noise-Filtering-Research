#include "DisneyBrdf.h"

using namespace glm;

glm::vec3 DisneyBrdf::EvaluateBrdf(glm::vec3 inDir, glm::vec3 outDir, glm::vec3 normal)
{
	in = inDir;
	out = outDir;

	frame = mat.getFrame(normal);
	n = frame.z;
	h = normalize(inDir + outDir);

	hl = frame.toFrame(h);
	inl = frame.toFrame(in);
	outl = frame.toFrame(out);

	Ctint = mat.baseColor / dot(vec3(0.3, 0.6, 0.1), mat.baseColor);

	return (1 - mat.mettalic) * Diffuse() +  Metallic() + 0.25f * mat.clearcoat * Clearcoat();
	
}

float DisneyBrdf::FD(glm::vec3 dir)
{
	return 1.0f + (FD90 - 1.0f) * (pow(1.0f - dot(dir, n), 5.0f));
}

glm::vec3 DisneyBrdf::BaseDiffuse()
{
	FD90 = 0.5f + 2 * mat.roughness * pow(dot(out, h), 2.0f);
	return mat.baseColor * FD(in) * FD(out) / PI;
}

float DisneyBrdf::FSS(glm::vec3 dir)
{
	return 1.0f + (FSS90 - 1.0f) * (pow(1.0f - dot(dir, n), 5.0f));
}

glm::vec3 DisneyBrdf::SubsurfaceDiffuse()
{
	FSS90 = mat.roughness * pow(dot(h, out), 2.0f);
	return 1.25f * mat.baseColor * (FSS(in) * FSS(out) *
		(1.0f /
			(dot(n, in) + dot(n, out))
			- 0.5f)
		+ 0.5f)/ PI;
}

glm::vec3 DisneyBrdf::Diffuse()
{
	return (1 - mat.subsurface) * BaseDiffuse() + mat.subsurface * SubsurfaceDiffuse();
}

float DisneyBrdf::Lambda(glm::vec3 fdir)
{
	return 0.5f * sqrt(1.0f + (pow(fdir.x*alphax, 2.0f) + pow(fdir.y*alphay, 2.0f)) / pow(fdir.z, 2.0f)) - 0.5f;
}

float DisneyBrdf::G(glm::vec3 fdir)
{
	return 1.0f / (1.0f + Lambda(fdir));
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
	return 0.25f * Fm * Dm * Gm / dot(n, in) / dot(n,out);
}

float DisneyBrdf::R0(float ior)
{
	return pow((ior - 1.0f) / (ior + 1.0f), 2.0f);
}

float DisneyBrdf::LambdaC(glm::vec3 fdir)
{
	return 0.5f * std::sqrtf(1.0f + (std::powf(0.25f * fdir.x, 2.0f) + std::powf(0.25f * fdir.y, 2.0f)) / (fdir.z * fdir.z)) - 0.5f;
}

float DisneyBrdf::GC(glm::vec3 fdir)
{
	return 1.0f / (1.0f + LambdaC(fdir));
}

glm::vec3 DisneyBrdf::Clearcoat()
{
	alphac = (1.0f - mat.clearcoatGloss) * 0.1f + mat.clearcoatGloss * 0.001f;

	Fc = R0(clearcoat_eta) + (1.0f - R0(clearcoat_eta)) * pow(1 - dot(h, out), 5.0f);
	Dc = (alphac * alphac - 1.0f) / (
		PI * std::logf(alphac * alphac) * (1.0f + (alphac * alphac - 1.0f) * hl.z * hl.z)
		);
	Gc = GC(in) * GC(out);
	return glm::vec3(1.0f) * 4.0f * Fc * Dc * Gc / (dot(n, in) * dot(n, out));
}







