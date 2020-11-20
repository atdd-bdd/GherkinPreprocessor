#pragma once
#include <string>
#include <ostream>
class Line
{
private: std::string & data; 
public: Line(const std::string& line) {
	data = line; 
}
public: void print(const ostream & out)
{
	out << data << "*" << "\n"; 
}

};

