#include <glm/glm.hpp>
#include <iostream>

#include "Renderer.h"

int main()
{
	Scene scene{};
	scene.camera.focal_length = 1.0f;
	scene.camera.position = glm::vec3(0, 0, 0);


	Sphere testSphere{};
	testSphere.radius = 1.0f;
	testSphere.position = glm::vec3(0, 0, -3);

	
	scene.objects.push_back(&testSphere);

	Renderer::config.scene.emplace(&scene);
	
	Renderer::render();

	return 0;
}
