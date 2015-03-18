#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include <boost/filesystem.hpp>

struct Data
{
	double x;
	double y;
	double team;
	double time;
};

class ReadCSV
{
public: 
	std::vector<Data>  read(std::string path);
};