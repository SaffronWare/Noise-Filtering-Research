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
			if (!bestHit.hit || currHit.hit < bestHit.hit)
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
		return glm::vec3(1, 1, 1);
	}

	HitInfo hit = Renderer::getHit(negIncomingRay);

	if (!hit.hit)
	{
		return glm::vec3(1, 1, 1);
	}

	if (glm::dot(hit.n, negIncomingRay.direction) > 0)
	{
		hit.n *= -1.0f;
	}

	glm::vec3 OutgoingRadiance = hit.mat.emissionColor;

	for (int i = 0; i < Renderer::config.num_samples_per_trace; i++)
	{

		glm::vec3 reflected_dir = Utils::randomOnHemisphere(hit.n);
		glm::vec3 reflected_pos = negIncomingRay.position + Renderer::config.hit_tolerance * hit.n;

		OutgoingRadiance += hit.mat.BRDF(reflected_dir, -negIncomingRay.direction, hit.n) 
			* Renderer::getIncomingLight(Ray{ reflected_pos, reflected_dir }, stepNum + 1) * glm::dot(reflected_dir, hit.n);
	}

	return OutgoingRadiance / (float)Renderer::config.num_samples_per_trace;
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

	for (int j = 0; j < Renderer::config.resolution_y; j++)
	{
		for (int i = 0; i < Renderer::config.resolution_x; i++)
		{
			glm::vec3 IncomingLight = glm::clamp(Renderer::colorAtUV(uv), 0.0f, 1.0f);

			output.data[output_index] = IncomingLight.x;
			output.data[output_index + 1] = IncomingLight.y;
			output.data[output_index + 2] = IncomingLight.z;
			output_index += 3;

			uv.x += off;
		}
		uv.y += off;
		uv.x = -0.5f * off * static_cast<float>(Renderer::config.resolution_x);
	}

	return output;
}

