#pragma once
#include <string>
#include <regex>
#include <iostream>
class Pathname
{
public: static Pathname local_path;    // switch to Pathname 
public: static Pathname system_path;
private: std::string data;
public: Pathname(const std::string name); 
public:  std::string get_value(); 
public: static void set_system_path(const std::string& value); 
public: static void set_local_path(const std::string& value); 
};