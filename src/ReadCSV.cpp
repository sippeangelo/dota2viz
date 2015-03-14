#include "ReadCSV.h"
#include <fstream>



std::vector<Data>  ReadCSV::read(std::string path)
{
	Data data;
	std::vector<Data> datalist;
	std::ifstream file(path);
	std::string s_data;
	while (file.good())
	{
		getline(file, s_data, ';');
		data.x = std::atof(s_data.c_str());

		
		getline(file, s_data, '\n');
		data.y = std::atof(s_data.c_str());

		//std::cout << data.x << ":" << data.y << std::endl;

		datalist.push_back(data);
	}

	return datalist;

}