#include <fstream>

#include "ReadCSV.h"




std::vector<Data>  ReadCSV::read(std::string path)
{
	

	Data data;
	std::vector<Data> datalist;
	
	boost::filesystem::path dir(path);

	if (!boost::filesystem::is_directory(dir)) {
		std::cerr << "Path is not a directory" << std::endl;
		//return 1;
	}

	for (boost::filesystem::directory_iterator it(dir), end; it != end; it++) {
		auto path = it->path();

		if (path.extension() != ".csv") {
			std::cout << "Skipping " << path << ": Not a csv file" << std::endl;
			continue;
		}

		std::ifstream file(path.c_str());
		std::string s_data;

		while (file.good())
		{
			//std::cout << "Reading CSV " << path << std::endl;
			getline(file, s_data, ';');
			data.x = std::atof(s_data.c_str());

			getline(file, s_data, ';');
			data.y = std::atof(s_data.c_str());

			getline(file, s_data, ';');
			data.team = std::atof(s_data.c_str());

			getline(file, s_data, '\n');
			data.time = std::atof(s_data.c_str());

			datalist.push_back(data);
		}

		file.close();
	}

	return datalist;

}