#include <glm/glm.hpp>
#include <iostream>




#include "Renderer.cuh"
#include "Export.cuh"
#include "Analysis.cuh"
#include "Setup.cuh"

int main()
{
	Setup::Setup();
	/*Renderer::RenderOutput render = Renderer::render();*/
	
	Renderer::RenderOutput converged = Analysis::sampleConvergence(10, 1, "C:\\Users\\aryan\\SaffronWare\\Noise-Filtering-Path-Tracing\\Analysis\\analysis.txt");
	Exporter::RenderToPPM(converged, std::string("C:\\Users\\aryan\\SaffronWare\\Noise-Filtering-Path-Tracing\\Analysis\\image.ppm"));

	

	return 0;
}
