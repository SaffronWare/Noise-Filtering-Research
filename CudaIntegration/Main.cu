#include "config.h"
#include <cmath>
#include <iostream>
#include "Render.cuh"
#include "Export.h"



int main()
{
	RenderConfig config;
	config.width = 100;
	config.height = 100;
	config.cam = Camera();
	config.scene;
	std::vector<Sphere> spheres;
	Sphere test_sphere = Sphere{};
	test_sphere.position = glm::vec3(0, 0, 2.0f);
	test_sphere.radius = 1.0f;
	spheres.push_back(test_sphere);
	config.scene.Load(spheres, std::vector<Plane>(), std::vector<Rect>());

	RenderData data = render(config);
	

	Exporter::RenderToPPM(data, "C:\\Users\\aryan\\SaffronWare\\Noise-Filtering-Path-Tracing\\Analysis\\test.ppm");

}