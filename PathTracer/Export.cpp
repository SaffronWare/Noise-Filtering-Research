#include "Export.h"

void Exporter::RenderToPPM(Renderer::RenderOutput& render, std::string path)
{
	std::ofstream outFile(path);

	if (outFile.is_open())
	{
		outFile << "P3\n";
		outFile << "#Render Name: " << render.title << "\n";
		outFile << "#Render Desc: " << render.description << "\n";
		outFile << render.resolution_x << " " << render.resolution_y << "\n";
		outFile << "255\n";

		unsigned int pixel_start_index = 0u;
		for (unsigned int j = 0; j < render.resolution_y; j++)
		{
			for (unsigned int i = 0; i < render.resolution_x; i++)
			{
				outFile << static_cast<int>(255 * render.data[pixel_start_index]);
				outFile << " " << static_cast<int>(255 * render.data[pixel_start_index + 1]);
				outFile << " " << static_cast<int>(255 * render.data[pixel_start_index + 2]);
				outFile << " ";

				pixel_start_index += 3;
			}
			outFile << "\n";
		}
	}
	else
	{
		std::cerr << "Failed to export render: " << render.title << std::endl;
	}
}