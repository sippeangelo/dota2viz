#include <iostream>
#include <string>
#include <vector>

struct Data
{
	double x;
	double y;
};

class ReadCSV
{
public: 
	std::vector<Data>  read(std::string path);
};