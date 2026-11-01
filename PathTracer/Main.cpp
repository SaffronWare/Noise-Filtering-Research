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
	testSphere.mat.roughness = 0.4f;
	testSphere.mat.mettalic = 1.0f;
	testSphere.mat.specular = 1.0f;
	testSphere.mat.specularTint = 1.0f;
	//testSphere.mat.emissionStrength = 20.0f;

	Plane floorPlane{};
	floorPlane.position = glm::vec3(0, 1.01, 0);
	floorPlane.normal = glm::vec3(0, -1, 0);
	floorPlane.mat.baseColor = glm::vec3(1, 1, 1);
	floorPlane.mat.emissionColor = glm::vec3(0, 0, 0);

	Plane ceilPlane{};
	ceilPlane.position = glm::vec3(0, -2.01, 0);
	ceilPlane.normal = glm::vec3(0, -1, 0);
	ceilPlane.mat.baseColor = glm::vec3(1);

	Plane leftPlane{};
	leftPlane.position = glm::vec3(-4, 0, 0);
	leftPlane.normal = glm::vec3(1, 0, 0);
	leftPlane.mat.baseColor = glm::vec3(1.0, 0.2, 0.1);

	Plane rightPlane{};
	rightPlane.position = glm::vec3(4, 0, 0);
	rightPlane.normal = glm::vec3(1, 0, 0);
	rightPlane.mat.baseColor = glm::vec3(0.2, 1.0, 0.3);

	Plane frontPlane{};
	frontPlane.position = glm::vec3(0, 0, -8);
	frontPlane.normal = glm::vec3(0, 0, 1);
	frontPlane.mat.baseColor = glm::vec3(1);

	Plane backPlane{};
	backPlane.position = glm::vec3(0, 0, 2);
	backPlane.normal = glm::vec3(0, 0, 1);
	backPlane.mat.baseColor = glm::vec3(1);

	Rect lightRect{};
	lightRect.center = glm::vec3(0, -2.0, -3);
	lightRect.right = glm::vec3(1, 0, 0);
	lightRect.up = glm::vec3(0, 0, 1);
	lightRect.dimensions = glm::vec2(4, 4);
	
	lightRect.mat.emissionColor = glm::vec3(1, 1, 1);
	lightRect.mat.emissionStrength = 30.0f;
	lightRect.mat.baseColor = glm::vec3(1,0,0);
	lightRect.mat.roughness = 1.0f;

	
	scene.objects.push_back(&testSphere);
	scene.objects.push_back(&floorPlane);
	scene.objects.push_back(&ceilPlane);
	scene.objects.push_back(&leftPlane);
	scene.objects.push_back(&rightPlane);
	scene.objects.push_back(&frontPlane);
	scene.objects.push_back(&backPlane);
	scene.objects.push_back(&lightRect);


	Renderer::config.scene.emplace(&scene);
	
	Renderer::RenderOutput render1 = Renderer::render();
	Exporter::RenderToPPM(render1, std::string("C:\\Users\\aryan\\SaffronWare\\Noise-Filtering-Path-Tracing\\PathTracer\image.ppm"));


	return 0;
}
