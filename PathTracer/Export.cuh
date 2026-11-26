#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "Renderer.cuh"

namespace Exporter
{
	void RenderToPPM(Renderer::RenderOutput& render, std::string path);
}