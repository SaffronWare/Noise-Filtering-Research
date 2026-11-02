#pragma once

#include "Renderer.h"

namespace Analysis
{
	float ComputeSSE(Renderer::RenderOutput render, Renderer::RenderOutput groundTruth);
}