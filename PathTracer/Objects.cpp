#pragma once

#include "Objects.h"

ShadingFrame Material::getFrame(glm::vec3 n)
{
	ShadingFrame out;
	out.x = glm::normalize(glm::cross(anisoBasis, n)); // anisotropic Direction
	out.y = glm::normalize(glm::cross(out.x, n));
	out.z = n;
	return out;
}

glm::vec3 ShadingFrame::toFrame(glm::vec3 v)
{
	return glm::vec3(glm::dot(v, x), glm::dot(v, y), glm::dot(v, z));
}

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
		return HitInfo{ glm::vec3(), glm::vec3(), Material{}, -1, false };
	}
	else
	{
		return HitInfo{ ray.pointAt(t), glm::normalize(ray.pointAt(t) - position), mat, t, true };
	}
}


HitInfo Plane::getHit(Ray ray)
{
	// need (dt + o - p) * n = 0
	//(d*n)t - (p-0)n = 0
	//t = (p-o)*n/(d*n)
	float dn = glm::dot(ray.direction, normal);
	if (glm::abs(dn) <= 0.00001)
	{
		return HitInfo{ glm::vec3(), glm::vec3(), Material{}, -1, false };
	}

	float t = glm::dot(position - ray.position, normal) / dn;
	if (t <= 0)
	{
		return HitInfo{ glm::vec3(), glm::vec3(), Material{}, -1, false };
	}

	return HitInfo{ ray.pointAt(t), normal, mat, t, true };
}

HitInfo Rect::getHit(Ray ray)
{
	Plane spacePlane;
	spacePlane.normal = glm::normalize(glm::cross(right ,up));
	spacePlane.position = center;
	spacePlane.mat = mat;
	HitInfo hit = spacePlane.getHit(ray);
	if (hit.hit)
	{

		float ux = glm::dot((hit.p - center), right);
		float uy = glm::dot((hit.p - center), up);
		if ((2.0f * glm::abs(ux) < dimensions.x) && (2.0f * glm::abs(uy) < dimensions.y))
		{
			return hit;
		}
		hit.hit = false;
	}
	return hit;
}




glm::vec3 Material::BRDF(glm::vec3 lightDir, glm::vec3 irrDir, glm::vec3 n)
{
	ShadingFrame frame = getFrame(n);

	glm::vec3 h = glm::normalize(lightDir + irrDir);


	// basic diffuse
	float FD90 = 0.5f + 2 * roughness * glm::pow(glm::abs(glm::dot(irrDir, h)),2.0f);

	float FDin = 1 + (FD90 - 1) * glm::pow(1 - glm::dot(irrDir, n), 5.0f);
	float FDout = 1 + (FD90 - 1) * glm::pow(1 - glm::dot(lightDir, n), 5.0f);

	glm::vec3 BaseDiffuse = FDin * FDout * glm::abs(glm::dot(irrDir, n)) * baseColor / std::acosf(-1.0f);

	// subsurface
	float FSS90 = roughness * glm::pow(glm::dot(h, irrDir), 2.0f);
	float FSSin = 1 + (FSS90 - 1) * (1 - glm::pow(glm::abs(glm::dot(lightDir, n)), 5.0f));
	float FSSout = 1 + (FSS90 - 1) * (1 - glm::pow(glm::abs(glm::dot(irrDir, n)), 5.0f));

	glm::vec3 SubsurfaceDiffuse = 1.25f * baseColor * (FSSin * FSSout * (
		1.0f /
		(glm::abs(glm::dot(n, irrDir)) + glm::abs(glm::dot(n, lightDir))) -0.5f)
		 + 0.5f) / std::acosf(-1.0f);

	glm::vec3 Diffuse = (1 - subsurface) * BaseDiffuse + subsurface * SubsurfaceDiffuse;


	// Metallic

	glm::vec3 Fm = baseColor + (1.0f - baseColor) * glm::pow(1.0f - glm::dot(irrDir, h), 5.0f);

	glm::vec3 hl = frame.toFrame(h);
	glm::vec3 irrl = frame.toFrame(irrDir);
	glm::vec3 lightl = frame.toFrame(lightDir);

	float aspect = std::sqrtf(1.0f - 0.9f * anisotropic);
	float alphax = std::fmaxf(0.0001f, roughness * roughness / aspect);
	float alphay = std::fmaxf(0.0001f, roughness * roughness * aspect);

	float Dm = glm::pow((hl.x / alphax), 2.0f) + glm::pow((hl.y / alphay), 2.0f) + glm::pow(hl.z, 2.0f);
	Dm *= Dm * alphax * alphay * std::acosf(-1.0f);
	Dm = 1.0f / Dm;

	float lambdain = 1.0f + (glm::pow(lightl.x * alphax, 2.0f) + glm::pow(lightl.y * alphay, 2.0f))/glm::pow(lightl.z, 2.0f);
	float lambdain = 0.5f * glm::sqrt(lambdain) - 0.5f;

	float lambdaout = 1.0f + (glm::pow(irrl.x * alphax, 2.0f) + glm::pow(irrl.y * alphay, 2.0f)) / glm::pow(irrl.z, 2.0f);
	float lambdaout = 0.5f * glm::sqrt(lambdain) - 0.5f;

	float Gm = 1.0f / ((1 + lambdain) * (1 + lambdaout));

	glm::vec3 Mettalic = 0.25f * Fm * Dm * Gm / glm::abs(glm::dot(n, lightDir));


	
	//return baseColor;
	return (1-mettalic) * Diffuse + mettalic * Mettalic;
}
