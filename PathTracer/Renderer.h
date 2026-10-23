#pragma once
#include <memory>
#include <string>
#include <optional>

#include "Scene.h"


namespace Renderer
{
	struct RenderConfig
	{
		std::optional<Scene*> scene;

		unsigned int resolution_x = 1920u;
		unsigned int resolution_y = 1080u;

		float hit_tolerance = 0.001f;

		unsigned int max_steps = 1u;
		unsigned int num_samples_per_pixel = 1u;
		unsigned int num_samples_per_trace = 1u;
	};

	struct RenderOutput
	{
		unsigned int resolution_x;
		unsigned int resolution_y;
		std::unique_ptr<float[]> data;

		std::string title;
		std::string description;

	};

	extern RenderConfig config;

	HitInfo getHit(Ray ray);

	glm::vec3 getIncomingLight(Ray negIncomingRay, unsigned int stepNum);
	glm::vec3 colorAtUV(glm::vec2 uv);

	RenderOutput render();

}