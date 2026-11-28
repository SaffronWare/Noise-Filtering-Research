#include "config.h"
#include <cmath>
#include <iostream>
#include "Render.cuh"
#include "Export.h"

#include "Setup.h"


int main()
{


	RenderConfig config = Setup();
	RenderData data = render(config);
	

	Exporter::RenderToPPM(data, "C:\\Users\\aryan\\SaffronWare\\Noise-Filtering-Path-Tracing\\Analysis\\test.ppm");

}