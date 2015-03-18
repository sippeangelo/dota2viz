#include <random>
#include <vector>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <heatmap.h>
#include <examples/lodepng.h>
#include <alice/defs.hpp>

#include "ReadCSV.h"

class HeatmapManager
{
public:
	void CreateHeatmap(std::string path, int timestep = -1);
	void CreateImage(int counter, boost::filesystem::path out_red, boost::filesystem::path out_blue);
private:
	std::vector<Data> data;
	heatmap_stamp_t* stamp;
};