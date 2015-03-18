#include <iostream>
#include <exception>

#include <boost/filesystem.hpp>

#include "HeatmapManager.h"


int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Usage: dota2viz <path> [team/heat (team)] [stampsize (16)] [timestep (-1)]" << std::endl;
		return 1;
	}

	////////////////////////////////////////////////////////////
	// Heatmap stuff 
	////////////////////////////////////////////////////////////
	HeatmapManager hmm;
	//hmm.ReadData();
	if (argc == 2) {
		hmm.CreateHeatmap(argv[1], "heat", 16, -1);
	} else if (argc == 3) {
		hmm.CreateHeatmap(argv[1], argv[2], 16, -1);
	} else if (argc == 4) {
		hmm.CreateHeatmap(argv[1], argv[2], std::atoi(argv[3]), -1);
	} else if (argc == 5) {
		hmm.CreateHeatmap(argv[1], argv[2], std::atoi(argv[3]), std::atoi(argv[4]));
	}
	//hmm.CreateImage();
	////////////////////////////////////////////////////////////
	// Heatmap not stuff
	////////////////////////////////////////////////////////////

	return 0;
}
