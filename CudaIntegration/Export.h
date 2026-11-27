#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <glm/glm.hpp>

#include "Render.cuh"

namespace Exporter
{
	void RenderToPPM(RenderData rd, std::string path);
};