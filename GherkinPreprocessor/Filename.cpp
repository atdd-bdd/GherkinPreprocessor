#include "Filename.h"
#include <string>
#include <regex>
#include <iostream>
#include "Pathname.h"

std::string Filename::get_directory(const std::string & filename) {
	std::cmatch m;
	std::regex include("(.*)[\\/>]", std::regex::icase | std::regex::ECMAScript);
	bool match = std::regex_search(filename.c_str(), m, include);
	std::string path = ""; 
	if (match) {
		path = m[1];
	}
	return path; 
}

bool Filename::isCSV() {
	std::cmatch m;
	std::regex csv(".csv$", std::regex::icase | std::regex::ECMAScript);
	bool match = std::regex_search(data.c_str(), m, csv);
	return match;
}
Filename::Filename(std::string name) {
	data = name;
	std::cmatch m;
	std::regex include("([\"<])\\s*(.*)\\s*[\">]", std::regex::icase | std::regex::ECMAScript);
	bool match = std::regex_search(data.c_str(), m, include);
	if (match) {
		if (m[1] == "\"")
			path = PATH::LOCAL;
		else
			path = PATH::SYSTEM;
		data = m[2];
	}
}
std::string Filename::get_value() {
	std::string filename = data;
	std::string to_add = "";
	if (path == PATH::LOCAL) 
		to_add = Pathname::local_path.get_value();
	if (path == PATH::SYSTEM)
		to_add = Pathname::system_path.get_value();
	std::string total_path = to_add + filename;

	return total_path;
}

