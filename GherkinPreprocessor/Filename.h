#pragma once
#include <string>
enum class PATH {NONE, LOCAL, SYSTEM};

class Filename
{  
public: static std::string get_directory(const std::string& filename); 
private: std::string data; 
private: PATH path = PATH::NONE; 
public: bool isCSV();
public: Filename(std::string name);
public: std::string get_value();
};


