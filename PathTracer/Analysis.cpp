#include "Analysis.h"

float Analysis::ComputeSSE(Renderer::RenderOutput render, Renderer::RenderOutput groundTruth)
{
	float SSE =  0.0f;
	for (int i = 0; i < render.resolution_x * render.resolution_y; i++)
	{
		float er = (groundTruth.data[3 * i + 0] - render.data[3 * i + 0]);

		float gr = (groundTruth.data[3 * i + 1] - render.data[3 * i + 1]);

		float br = (groundTruth.data[3 * i + 2] - render.data[3 * i + 2]);

		SSE += er * er + gr * gr + br * br;

	}

	return SSE / 3.0f / (float)(render.resolution_x * render.resolution_y);
}