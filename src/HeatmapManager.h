#include <random>
#include <vector>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <heatmap.h>
#include <examples/lodepng.h>

#include "ReadCSV.h"

class HeatmapManager
{
public:
	void ReadData(std::string path);
	void CreateHeatmap();
	void CreateImage();
private:
	std::vector<Data> data;
};