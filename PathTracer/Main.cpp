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
	testSphere.mat.emissionStrength = 20.0f;

	Plane floorPlane{};
	floorPlane.position = glm::vec3(0, 1.01, 0);
	floorPlane.normal = glm::vec3(0, -1, 0);
	floorPlane.mat.baseColor = glm::vec3(1, 1, 1);
	floorPlane.mat.emissionColor = glm::vec3(0, 0, 0);

	
	scene.objects.push_back(&testSphere);
	scene.objects.push_back(&floorPlane);



	Renderer::config.scene.emplace(&scene);
	
	Renderer::RenderOutput render1 = Renderer::render();
	Exporter::RenderToPPM(render1, std::string("C:\\Users\\aryan\\SaffronWare\\Noise-Filtering-Path-Tracing\\PathTracer\image.ppm"));


	return 0;
}
