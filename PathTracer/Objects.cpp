#pragma once

#include "Objects.h"
#include "DisneyBrdf.h"

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
	DisneyBrdf brdf{};
	brdf.mat = *this;
	return brdf.EvaluateBrdf(lightDir, irrDir, n);
}
