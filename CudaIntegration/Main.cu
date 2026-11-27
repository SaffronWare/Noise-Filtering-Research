#include "config.h"
#include <cmath>
#include <iostream>
#include "Render.cuh"
#include "Export.h"



int main()
{
	RenderConfig config;
	config.width = 100;
	config.height = 100;
	config.cam = Camera();
	RenderData data = render(config);
	

	Exporter::RenderToPPM(data, "test.ppm");

}