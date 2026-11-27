#include "Export.h"

void Exporter::RenderToPPM(RenderData render, std::string path)
{
	std::ofstream outFile(path);

	if (outFile.is_open())
	{
		outFile << "P3\n";
		outFile << render.width << " " << render.height << "\n";
		outFile << "255\n";

		unsigned int pixel_start_index = 0u;
		for (unsigned int j = 0; j < render.width; j++)
		{
			for (unsigned int i = 0; i < render.height; i++)
			{
				outFile << static_cast<int>(255 * glm::clamp(render.data[pixel_start_index], 0.0f, 1.0f));
				outFile << " " << static_cast<int>(255 * glm::clamp(render.data[pixel_start_index + 1], 0.0f, 1.0f));
				outFile << " " << static_cast<int>(255 * glm::clamp(render.data[pixel_start_index + 2], 0.0f, 1.0f));
				outFile << " ";

				pixel_start_index += 3;
			}
			outFile << "\n";
		}
	}
	else
	{
		std::cerr << "Failed to export render!" << std::endl;
	}
}