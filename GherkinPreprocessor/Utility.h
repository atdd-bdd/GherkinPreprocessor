#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
class Utility
{
public: static bool write_file(std::string name, std::string contents) {
		std::ofstream myfile;
		myfile.open(name);
		myfile << contents;
		myfile.close();
		return myfile.good(); 
	}
public: static std::string read_file(std::string name, std::string & contents) {
	std::ifstream myfile; 
	myfile.open(name);
	std::stringstream buffer;
	buffer << myfile.rdbuf();
	myfile.close();
	}
	  public: static std::vector<std::string> break_into_lines(std::string input)
	  {
		  std::stringstream ss(input);
		  std::string to;
		  std::vector<std::string> strings;
		  while (std::getline(ss, to, '\n')) {
			  strings.push_back(to);
		  }
	return strings;
	}
};

