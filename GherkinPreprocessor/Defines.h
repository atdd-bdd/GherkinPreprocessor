#pragma once
#include <map>
#include <string>


class Defines
{
private: std::map<std::string, std::string> data;
public: std::string get_terms_with_bars();
	  void replace_in_a_define(std::map<std::string, std::string>::iterator& s, std::string& result);
std::string make_search_with_bars();
public: void insert(std::string& term, std::string& definition);
public: bool find(const std::string& term, std::string& definition);
};

