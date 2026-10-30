#pragma once

#include "Objects.h"

virtual ShadingFrame Material::getFrame(HitInfo info)
{
	ShadingFrame out;
	out.x = glm::cross(anisoBasis, info.n); // anisotropic Direction
	out.y = glm::cross(out.x, info.n);
	return out;
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
	glm::vec3 h = glm::normalize(lightDir + irrDir);

	float FD90 = 0.5f + 2 * roughness * glm::pow(glm::abs(glm::dot(irrDir, h)),2.0f);

	float FDin = (1 + (FD90 - 1) * glm::pow(1 - glm::dot(irrDir, n), 5.0f));
	float FDout = (1 + (FD90 - 1) * glm::pow(1 - glm::dot(lightDir, n), 5.0f));

	glm::vec3 BaseDiffuse = FDin * FDout * glm::abs(glm::dot(irrDir, n)) * baseColor / std::acosf(-1.0f);

	glm::vec3 Fm = baseColor + (1.0f - baseColor) * glm::pow(1.0f - glm::dot(irrDir, h), 5.0f);


	
	//return baseColor;
	return BaseDiffuse;
}
