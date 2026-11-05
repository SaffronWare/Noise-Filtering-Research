#include <glm/glm.hpp>
#include <iostream>




#include "Renderer.h"
#include "Export.h"
#include "Analysis.h"
#include "Setup.h"

int main()
{
	Setup::Setup();
	/*Renderer::RenderOutput render = Renderer::render();*/
	
	Renderer::RenderOutput converged = Analysis::sampleConvergence(30, 1, "C:\\Users\\aryan\\SaffronWare\\Noise-Filtering-Path-Tracing\\Analysis\\analysis.txt");
	Exporter::RenderToPPM(converged, std::string("C:\\Users\\aryan\\SaffronWare\\Noise-Filtering-Path-Tracing\\Analysis\\image.ppm"));

	

	return 0;
}
