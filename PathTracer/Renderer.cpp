#include "Renderer.h"

Renderer::RenderConfig Renderer::config = Renderer::RenderConfig{};

HitInfo Renderer::getHit(Ray ray)
{
	HitInfo bestHit{};
	bestHit.hit = false;

	HitInfo currHit;
	for (Object*& pObj : Renderer::config.scene.value()->objects)
	{
		currHit = pObj->getHit(ray);
		if (currHit.hit && currHit.dist > Renderer::config.hit_tolerance)
		{
			if (!bestHit.hit || currHit.dist < bestHit.dist)
			{
				bestHit = currHit;
			}
		}
	}

	return  bestHit;
}

glm::vec3 Renderer::getIncomingLight(Ray negIncomingRay, unsigned int stepNum)
{
	if (stepNum >= Renderer::config.max_steps)
	{
		return glm::vec3(0);
	}

	HitInfo hit = Renderer::getHit(negIncomingRay);

	if (!hit.hit)
	{
		return glm::vec3(0);
	}

	if (glm::dot(hit.n, negIncomingRay.direction) > 0)
	{
		hit.n *= -1.0f;
	}

	glm::vec3 OutgoingRadiance = glm::vec3(0);

	for (int i = 0; i < Renderer::config.num_samples_per_trace; i++)
	{

		glm::vec3 reflected_dir = Utils::randomOnHemisphere(hit.n);
		glm::vec3 reflected_pos = hit.p + Renderer::config.hit_tolerance * hit.n;

		OutgoingRadiance += hit.mat.BRDF(reflected_dir, -negIncomingRay.direction, hit.n) 
			* Renderer::getIncomingLight(Ray{ reflected_pos, reflected_dir }, stepNum + 1) * glm::dot(reflected_dir, hit.n);
	}

	return OutgoingRadiance / (float)Renderer::config.num_samples_per_trace + hit.mat.emissionColor * hit.mat.emissionStrength;
}

glm::vec3 Renderer::colorAtUV(glm::vec2 uv)
{
	Ray ray = Renderer::config.scene.value()->camera.shootRay(uv);
	return Renderer::getIncomingLight(ray, 0u);
}

Renderer::RenderOutput Renderer::render()
{

	Renderer::RenderOutput output{};

	if (!Renderer::config.scene.has_value())
	{
		std::cerr << "MISSING SCENE SPECIFICATION IN RENDER CONFIG! FAILED TO RENDER\n";
		return output;
	}

	output.resolution_x = Renderer::config.resolution_x;
	output.resolution_y = Renderer::config.resolution_y;
	output.data = std::make_unique<float[]>(output.resolution_x * output.resolution_y * 3);

	int output_index = 0;

	glm::vec2 uv;
	float off = 1.0f / (static_cast<float>(Renderer::config.resolution_y));
	uv.x = -0.5f * off * static_cast<float>(Renderer::config.resolution_x);
	uv.y = -0.5f;


//#pragma omp parallel for collapse(2)
	for (int j = 0; j < Renderer::config.resolution_y; j++)
	{
		for (int i = 0; i < Renderer::config.resolution_x; i++)
		{
			glm::vec3 incomingLight = glm::vec3();
			for (int k = 0; k < Renderer::config.num_samples_per_pixel; k++)
			{
				incomingLight += Renderer::colorAtUV(uv);
			}

			incomingLight = glm::clamp(incomingLight / (float)Renderer::config.num_samples_per_pixel, 0.0f, 1.0f);

			output.data[output_index] = incomingLight.x;
			output.data[output_index + 1] = incomingLight.y;
			output.data[output_index + 2] = incomingLight.z;
			output_index += 3;

			uv.x += off;
		}
		uv.y += off;
		uv.x = -0.5f * off * static_cast<float>(Renderer::config.resolution_x);
	}

	return output;
}

