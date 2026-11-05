#include "Analysis.h"

float Analysis::ComputeSSE(const Renderer::RenderOutput& render, const Renderer::RenderOutput& groundTruth)
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

Renderer::RenderOutput Analysis::sampleConvergence(unsigned int max_iter, unsigned int sample_step, std::string path)
{
	std::ofstream outFile(path);

	if (outFile.is_open())
	{
		Renderer::config.num_samples_per_pixel = sample_step;
		Renderer::RenderOutput curr;
		Renderer::RenderOutput prev = Renderer::render();
		float SSE = 0.0f;
		outFile << "-----RENDER ANALYSIS-----\n";
		outFile << "SPP SSE\n";
		std::cout << "----ANALYSIS BEGUN---\n";

		std::vector<Renderer::RenderOutput*> pastRenders = {};

		for (int i = 1; i < max_iter; i++)
		{

			std::cout << "----------------------\n PROGRESS " << 100.0f * i / (float)max_iter << "%" << "\n";
			outFile << (i +1) * sample_step << " ";
			curr = Renderer::cumulativeRender(prev, i);
			std::cout << "COMPUTED RENDER\n";
			SSE = Analysis::ComputeSSE(curr, prev);
			std::cout << "COMPUTED SSE: " << SSE << "\n";

			Renderer::RenderOutput* toRecord = new Renderer::RenderOutput();
			toRecord->data = std::move(prev.data);
			toRecord->resolution_x = prev.resolution_x;
			toRecord->resolution_y = prev.resolution_y;

			pastRenders.push_back(toRecord);
			prev.data = std::move(curr.data);
		
			outFile << SSE << std::endl;

			if (SSE < 10e-8f)
			{
				outFile << "RENDER CONVERGED\n";
				break;
			}
		}
		outFile << "DONE STEPS\n";

		unsigned int i = 1;
		for (Renderer::RenderOutput* &output : pastRenders)
		{
			outFile << sample_step * i << " " << Analysis::ComputeSSE(*output, prev) << "\n";
			delete output;
			output = nullptr;
			i += 1;
		}
		
		return prev;

	}
	else
	{
		std::cerr << "Cant open ts\n!";
		// nun for now
	}
}