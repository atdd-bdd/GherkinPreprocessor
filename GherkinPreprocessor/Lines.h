#pragma once
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>

class Lines
{
private:  std::list<std::string> data; 
public: std::list<std::string> & get_data() {
	return data; 
}
public: Lines() {

}
public: void print_lines(const std::ostream & out) {
	for (auto& it : data) {
		out << it << "*" << "\n"; 
	}
}
public: Lines(const std::string array[], const int size) {
	for (int i = 0; i < size; i++)
	{
		data.push_back(array[i]);
	}
}

public: bool write_lines(const std::string name){
	std::ofstream myfile;
	myfile.open(name);
	for (auto& it : data) {
		myfile << it << "\n"; 
	}
	myfile.close();
	return myfile.good();
}

public: bool read_lines(const std::string name) {
	std::ifstream myfile;
	myfile.open(name);
	std::string line;
	while (std::getline(myfile, line)) {
		data.push_back(line); 
	}
	myfile.close();
	return myfile.good();
}

};

