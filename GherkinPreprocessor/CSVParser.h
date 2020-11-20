#pragma once
#include <vector>
#include <string>
#include <istream>
class CSVParser
{
public:	static std::vector<std::string> readCSVRow(const std::string& row);
public: static std::vector<std::vector<std::string>> readCSV(std::istream& in); 
};

