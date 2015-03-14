#include "HeatmapManager.h"
#include <colorschemes/Blues.h>
#include <colorschemes/Reds.h>


//Dota 2 map size
//http://www.reddit.com/r/DotA2/comments/1vaklc/how_big_is_the_dota2_map_really/
static const size_t w = 220, h = 221, scale = 2; //Viktor's example using Dota 2 blocks

// Create the heatmap object with the given dimensions (in pixel).
heatmap_t* hm = heatmap_new(w, h);
heatmap_t* hm2 = heatmap_new(w, h);




//Reads data from the CSV file
void HeatmapManager::ReadData(std::string path)
{
	ReadCSV reader;
	data = reader.read(path);
}



// Add the data points to the heatmap
void HeatmapManager::CreateHeatmap()
{
	int npoints = data.size();
	for (unsigned i = 0; i < npoints/2; ++i) 
		heatmap_add_point(hm, data[i].x, data[i].y);

	for (unsigned i = npoints/2; i < npoints; ++i)
		heatmap_add_point(hm2, data[i].x, data[i].y);
}

// This creates an image out of the heatmap.
// `image` now contains the image data in 32-bit RGBA.
void HeatmapManager::CreateImage()
{
	std::vector<unsigned char> image(w*h * 4);
	std::vector<unsigned char> image2(w*h * 4);

	
	//heatmap_render_default_to(hm, &image[0]);
	heatmap_render_to(hm, heatmap_cs_Blues_discrete, &image[0]);
	heatmap_render_to(hm2, heatmap_cs_Reds_discrete, &image2[0]);


	// Now that we've got a finished heatmap picture, we don't need the map anymore.
	heatmap_free(hm);
	heatmap_free(hm2);

	// Finally, we use the fantastic lodepng library to save it as an image.
	if (unsigned error = lodepng::encode("heatmap.png", image, w, h)) {
		std::cerr << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		//return 1;
	}
	if (unsigned error = lodepng::encode("heatmap2.png", image2, w, h)) {
		std::cerr << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		//return 1;
	}

	std::ifstream f("heatmap.png");
	if (f.good())
		std::cout << "Heatmap.png created.\n";
	else
		std::cout << "Heatmap.png not created\n";

	system("START heatmap.png");
	//system("PAUSE");
}
