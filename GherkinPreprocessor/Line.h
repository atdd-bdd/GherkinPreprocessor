#pragma once
#include "Defines.h"
#include "LineType.h"
#include <string>
#include <ostream>
#include <regex>
#include <iostream>


class Line
{

public: void replace(Defines& defines, std::string & matching);
private: std::string & data;
public: void calculate();
public: Line( std::string & line) : data(line) {

}
public: LineType parse(std::string& first_match, std::string& second_match);
public: void print(std::ostream & out)
{
	out << data << "*" << "\n";
}


};

