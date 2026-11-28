#include "Scene.cuh"

Scene::~Scene()
{
	if (owner)
	{
		unLoad();
	}
}
Scene::Scene(const Scene& other)
{

	sspheres = other.sspheres;
	splanes = other.splanes;
	srects = other.srects;

	n_spheres = other.n_spheres;
	n_planes = other.n_planes;
	n_rects = other.n_rects;

	owner = false;
}

Scene& Scene::operator=(const Scene& other)
{
	*this = other;
	this->owner = false;
	return *this;
}

Scene::Scene(Scene&& other)
{
	sspheres = other.sspheres;
	splanes = other.splanes;
	srects = other.srects;

	n_spheres = other.n_spheres;
	n_planes = other.n_planes;
	n_rects = other.n_rects;

	other.sspheres = nullptr;
	other.splanes = nullptr;
	other.srects = nullptr;

	other.n_spheres = 0;
	other.n_planes = 0;
	other.n_rects = 0;

}

void Scene::Load(const std::vector<Sphere>& spheres,  const std::vector<Plane>& planes, const std::vector<Rect>& rects)
{
	CUDA_CHECK(cudaMallocManaged(&sspheres, sizeof(Sphere) * spheres.size()));
	CUDA_CHECK(cudaMallocManaged(&splanes, sizeof(Plane) * planes.size()));
	CUDA_CHECK(cudaMallocManaged(&splanes, sizeof(Plane) * planes.size()));

	n_spheres = spheres.size();
	n_planes = planes.size();
	n_rects = rects.size();
	

	memcpy(sspheres, spheres.data(), n_spheres * sizeof(Sphere));
	memcpy(splanes, planes.data(), n_planes * sizeof(Plane));
	memcpy(srects, rects.data(), n_rects * sizeof(Rect));
}

void Scene::unLoad()
{
	if (sspheres != nullptr)
	{
		CUDA_CHECK(cudaFree(sspheres));
	}
	if (splanes != nullptr)
	{
		CUDA_CHECK(cudaFree(splanes));
	}
	if (srects != nullptr)
	{
		CUDA_CHECK(cudaFree(srects));
	}

	
	sspheres = nullptr;
	splanes = nullptr;
	srects = nullptr;

	n_spheres = 0;
	n_planes = 0;
	n_rects = 0;
	
}

__device__ HitInfo Scene::getHit(Ray ray) const
{
	HitInfo hit{};
	hit.hit = false;
	HitInfo currhit{};
	hit.hit = false;
	for (int i =0; i < n_spheres; i ++ )
	{
		Sphere& sphere = sspheres[i];
		currhit = sphere.getHit(ray);
		if (currhit.hit && (!(hit.hit) || (currhit.dist < hit.dist)))
		{
			hit = currhit;
		}
	}
	for (int i = 0; i < n_planes; i++)
	{
		Plane& plane = splanes[i];
		currhit = plane.getHit(ray);
		if (currhit.hit && (!(hit.hit) || (currhit.dist < hit.dist)))
		{
			hit = currhit;
		}
	}
	for (int i = 0; i < n_rects; i++)
	{
		Rect& rect = srects[i];
		currhit = rect.getHit(ray);
		if (currhit.hit && (!(hit.hit) || (currhit.dist < hit.dist)))
		{
			hit = currhit;
		}
	}

	return hit;
}


__device__ HitInfo Sphere::getHit(Ray ray) 
{

	glm::vec3 diff = (ray.position - position);
	float a = 1.0f;
	float b = 2.0f * glm::dot(diff, ray.direction);
	float c = glm::dot(diff, diff) - radius * radius;

	float d = b * b - 4 * a * c;

	float t = -1;


	if (d == 0)
	{
		t = -b / (2 * a);


	}
	else if (d >= 0)
	{
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

__device__ HitInfo Plane::getHit(Ray ray)
{

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

__device__ HitInfo Rect::getHit(Ray ray)
{
	Plane spacePlane;
	spacePlane.normal = glm::normalize(glm::cross(right, up));
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

__device__ glm::vec3 ShadingFrame::toFrame(glm::vec3 v)
{
	return glm::vec3(glm::dot(v, x), glm::dot(v, y), glm::dot(v, z));
}

__device__ ShadingFrame Material::getFrame(glm::vec3 n)
{
	ShadingFrame out;
	if (glm::length(glm::cross(anisoBasis, n)) <= 0.0001f)
	{
		if (glm::length(glm::cross(n, glm::vec3(0, 0, 1))) <= 0.001f)
		{
			out.x = glm::cross(n, glm::vec3(1, 0, 0));
		}
		else
		{
			out.x = glm::cross(n, glm::vec3(0, 0, 1));
		}
	}
	else {
		out.x = glm::cross(anisoBasis, n); // anisotropic Direction
	}
	out.x = glm::normalize(out.x);
	out.y = glm::normalize(glm::cross(out.x, n));
	out.z = n;
	return out;
}

__device__ glm::vec3 Material::BRDF(glm::vec3 i, glm::vec3 o, glm::vec3 n)
{
	return 0.5f * baseColor / std::acosf(-1.0f);
}