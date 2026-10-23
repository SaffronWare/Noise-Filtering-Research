#include <glm/glm.hpp>
#include <iostream>

#include "Scene.h"

int main()
{
	Scene scene{};
	scene.camera.focal_length = 1.0f;
	scene.camera.position = glm::vec3(0, 0, 0);


	Sphere testSphere{};
	testSphere.radius = 1.0f;
	testSphere.position = glm::vec3(0, 0, -3);

	
	scene.objects.push_back(&testSphere);




	return 0;
}
