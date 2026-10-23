#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Renderer.h"

namespace Exporter
{
	void RenderToPPM(Renderer::RenderOutput& render, std::string path);
}