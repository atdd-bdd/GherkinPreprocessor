#pragma once
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include "Filename.h"
#include "CSVParser.h"
#include "Log.h"
class Lines
{
private:  std::list<std::string> data; 
public: std::list<std::string>& get_data();
public: Lines();
public: void print_lines(std::ostream& out);
public: Lines(const std::string array[], const int size);
public: bool write_lines(Filename name);
public: bool read_lines(Filename name);
};

