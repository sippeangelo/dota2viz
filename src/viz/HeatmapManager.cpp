#include <tuple>
#include <sstream>

#include "HeatmapManager.h"
#include <colorschemes/Blues.h>
#include <colorschemes/Reds.h>
#include <colorschemes/Spectral.h>

//Dota 2 map size
//http://www.reddit.com/r/DotA2/comments/1vaklc/how_big_is_the_dota2_map_really/
static const size_t w = 1024, h = 1024, scale = 1; //Viktor's example using Dota 2 blocks

// Create the heatmap object with the given dimensions (in pixel).
heatmap_t* hm = heatmap_new(w, h);
heatmap_t* hm2 = heatmap_new(w, h);




//Reads data from the CSV file
// void HeatmapManager::ReadData(std::string path)
// {
// 	ReadCSV reader;
// 	//data = reader.read(path);
// }


// Add the data points to the heatmap
void HeatmapManager::CreateHeatmap(std::string path, std::string colorscheme, int stampSize, int timestep /*= -1*/)
{
	//int npoints = data.size();

	stamp = heatmap_stamp_gen(stampSize);

// 	std::random_device rd;
// 		std::mt19937 prng(rd());
// 		std::normal_distribution<float> x_distr(0.5f*w, 0.5f / 3.0f*w), y_distr(0.5f*h, 0.25f*h);
// 	
// 		for (int i = 0; i < (npoints); ++i)
// 		{
// 			if (i < npoints)
// 			{
// 				//return (8576.0 + x) * 0.0314 + -12.2943, (8192.0 - y) * 0.0314 + -0.2884
// 			
// 	
	// 		int x = (8192 + x1) * ((float)w / 16384.f);
	//int y = (8192 - y1) * ((float)h / 16384.f);
// 				
// 	
// 			}
// 			else
// 			{
// 					heatmap_add_point(hm, x_distr(prng), y_distr(prng));
// 			}
// 		}

	boost::filesystem::path dir(path);

	if (!boost::filesystem::is_directory(dir)) {
		std::cerr << "Path is not a directory" << std::endl;
		//return 1;
	}

	boost::filesystem::path out_red = dir;
	boost::filesystem::path out_blue = dir;


	std::stringstream ss;
	ss << colorscheme << "_" << stampSize << "_" << timestep;
	out_red /= "red_" + ss.str();
	out_blue /= "blue_" + ss.str();

	boost::filesystem::create_directory(out_red);
	boost::filesystem::create_directory(out_blue);

	std::vector<std::shared_ptr<std::ifstream>> files;

	for (boost::filesystem::directory_iterator it(dir), end; it != end; it++) {
		auto path = it->path();

		if (path.extension() != ".csv") {
			std::cout << "Skipping " << path << ": Not a csv file" << std::endl;
			continue;
		}

		files.push_back(std::make_shared<std::ifstream>(path.c_str()));
	}
	
	int frameIndex = 0;
	int counter = 0;
	while (files.size() > 0) {
		auto it = files.begin();
		while (it != files.end()) {
			auto file = *it;

			std::string s_data;

			getline(*file, s_data, ';');
			int x1 = std::atof(s_data.c_str());

			getline(*file, s_data, ';');
			int y1 = std::atof(s_data.c_str());

			int x = (8192 + x1) * ((float)w / 16384.f);
			int y = (8192 - y1) * ((float)h / 16384.f);

			getline(*file, s_data, ';');
			int team = std::atof(s_data.c_str());

			getline(*file, s_data, '\n');
			double time = std::atof(s_data.c_str());

			//create heightmap
			if (team == 2) //radiant
				//heatmap_add_point(hm, x, y);
				heatmap_add_point_with_stamp(hm, x, y, stamp);
			else if (team == 3)
				//heatmap_add_point(hm2, x, y);
				heatmap_add_point_with_stamp(hm2, x, y, stamp);

			if (!file->good()) {
				file->close();
				it = files.erase(it);
			} else {
				it++;
			}
		}

		if (timestep > -1) {
			if (counter % timestep == 0) {
				CreateImage(frameIndex, colorscheme, out_red, out_blue);
				frameIndex++;
			}
		}

		counter++;
	}

	if (timestep == -1) {
		CreateImage(counter, colorscheme, out_red, out_blue);
	}

	//for (boost::filesystem::directory_iterator it(dir), end; it != end; it++) {
	//	auto path = it->path();

	//	if (path.extension() != ".csv") {
	//		std::cout << "Skipping " << path << ": Not a csv file" << std::endl;
	//		continue;
	//	}

	//	std::ifstream file(path.c_str());
	//	std::string s_data;

	//	int counter = 0;
	//	while (file.good())
	//	{
	//		counter++;
	//		//std::cout << "Reading CSV " << path << std::endl;
	//		getline(file, s_data, ';');
	//		int x1 = std::atof(s_data.c_str());

	//		getline(file, s_data, ';');
	//		int y1 = std::atof(s_data.c_str());

	//		int x = (8192 + x1) * ((float)w / 16384.f);
	//		int y = (8192 - y1) * ((float)h / 16384.f);

	//		getline(file, s_data, ';');
	//		int team = std::atof(s_data.c_str());

	//		getline(file, s_data, '\n');
	//		double time = std::atof(s_data.c_str());

	//		//create heightmap
	//		if (team == 2) //radiant
	//			//heatmap_add_point(hm, x, y);
	//			heatmap_add_point_with_stamp(hm, x, y, stamp);
	//		else if (team == 3)
	//			//heatmap_add_point(hm2, x, y);
	//			heatmap_add_point_with_stamp(hm2, x, y, stamp);

	//		if (counter % 10 == 0)
	//		{
	//			CreateImage(counter);
	//		}
	//	}
	//	file.close();
	//}



	heatmap_free(hm);
	heatmap_free(hm2);


	heatmap_stamp_free(stamp);
}

// This creates an image out of the heatmap.
// `image` now contains the image data in 32-bit RGBA.
void HeatmapManager::CreateImage(int counter, std::string colorscheme, boost::filesystem::path out_red, boost::filesystem::path out_blue)
{
	int scale2 = 10;
	std::vector<unsigned char> image((w*scale2)*(h * scale2) * 4);
	std::vector<unsigned char> image2((w * scale2)*(h*scale2) * 4);
		
	//heatmap_render_default_to(hm, &image[0]);
	if (colorscheme == "team") {
		heatmap_render_to(hm, heatmap_cs_Blues_soft, &image[0]);
		heatmap_render_to(hm2, heatmap_cs_Reds_soft, &image2[0]);
	} else {
		heatmap_render_to(hm, heatmap_cs_Spectral_soft, &image[0]);
		heatmap_render_to(hm2, heatmap_cs_Spectral_soft, &image2[0]);
	}
	



	// Now that we've got a finished heatmap picture, we don't need the map anymore.
// 	heatmap_free(hm);
// 	heatmap_free(hm2);

	// Finally, we use the fantastic lodepng library to save it as an image.

	{
		std::stringstream ss;
		ss << "heatmap" << counter << ".png";
		out_blue /= ss.str();
		if (unsigned error = lodepng::encode(out_blue.string(), image, w, h)) {
			std::cerr << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		}
	}

	{
		std::stringstream ss;
		ss << "heatmap" << counter << ".png";
		out_red /= ss.str();
		if (unsigned error = lodepng::encode(out_red.string(), image2, w, h)) {
			std::cerr << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;

		}
	}


// 	std::ifstream f("heatmap.png");
// 	if (f.good())
// 		std::cout << "Heatmap.png created.\n";
// 	else
// 		std::cout << "Heatmap.png not created\n";

	//system("START heatmap.png");
	//system("PAUSE");
}
