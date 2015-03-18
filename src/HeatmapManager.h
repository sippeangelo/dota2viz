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
	void CreateHeatmap(std::string path);
	void CreateImage(int counter);
private:
	std::vector<Data> data;
	heatmap_stamp_t* stamp;
};