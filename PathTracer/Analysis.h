#pragma once

#include <string>
#include <ostream>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Renderer.h"



namespace Analysis
{
	float ComputeSSE(const Renderer::RenderOutput& render, const Renderer::RenderOutput& groundTruth);

	Renderer::RenderOutput sampleConvergence(unsigned int max_iter = 1000, unsigned int sample_step = 1, std::string path = "");
}