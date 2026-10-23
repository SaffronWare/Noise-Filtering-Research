#pragma once

#include <vector>

#include "Objects.h"
#include "Camera.h"

struct Scene
{
	Camera camera;

	std::vector<Object*> objects;

};