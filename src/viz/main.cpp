#include <iostream>
#include <exception>

#include <boost/filesystem.hpp>

#include "HeatmapManager.h"


int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: dota2viz <path>" << std::endl;
		return 1;
	}

	////////////////////////////////////////////////////////////
	// Heatmap stuff 
	////////////////////////////////////////////////////////////
	HeatmapManager hmm;
	//hmm.ReadData();
	hmm.CreateHeatmap(argv[1], 10000);
	//hmm.CreateImage();
	////////////////////////////////////////////////////////////
	// Heatmap not stuff
	////////////////////////////////////////////////////////////

	return 0;
}
