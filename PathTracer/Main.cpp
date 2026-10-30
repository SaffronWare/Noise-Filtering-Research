#include <glm/glm.hpp>
#include <iostream>

#include "Renderer.h"
#include "Export.h"

int main()
{
	Scene scene{};
	scene.camera.focal_length = 1.0f;
	scene.camera.position = glm::vec3(0, 0, 0);


	Sphere testSphere{};
	testSphere.radius = 1.0f;
	testSphere.position = glm::vec3(0, 0, -3);
	testSphere.mat.baseColor = glm::vec3(1, 0, 0);
	testSphere.mat.emissionColor = glm::vec3(1, 0, 0);
	//testSphere.mat.emissionStrength = 20.0f;

	Plane floorPlane{};
	floorPlane.position = glm::vec3(0, 1.01, 0);
	floorPlane.normal = glm::vec3(0, -1, 0);
	floorPlane.mat.baseColor = glm::vec3(1, 1, 1);
	floorPlane.mat.emissionColor = glm::vec3(0, 0, 0);

	Rect lightRect{};
	lightRect.center = glm::vec3(0, -2.0, -3);
	lightRect.right = glm::vec3(1, 0, 0);
	lightRect.up = glm::vec3(0, 0, 1);
	lightRect.dimensions = glm::vec2(4, 4);
	
	lightRect.mat.emissionColor = glm::vec3(1, 1, 1);
	lightRect.mat.emissionStrength = 100.0f;
	lightRect.mat.baseColor = glm::vec3(1,0,0);
	lightRect.mat.roughness = 1.0f;

	
	scene.objects.push_back(&testSphere);
	scene.objects.push_back(&floorPlane);
	scene.objects.push_back(&lightRect);


	Renderer::config.scene.emplace(&scene);
	
	Renderer::RenderOutput render1 = Renderer::render();
	Exporter::RenderToPPM(render1, std::string("C:\\Users\\aryan\\SaffronWare\\Noise-Filtering-Path-Tracing\\PathTracer\image.ppm"));


	return 0;
}
