#include "Line.h"
#include "Limiter.h"
#include "atmsp.h"
#include "Calculate.h"
LineType Line::parse(std::string& first_match, std::string& second_match) {
	std::cmatch m;

	first_match = "";
	second_match = "";
	std::regex include("^\\s*#include\\s+(.*)$", std::regex::icase | std::regex::ECMAScript);
	bool match = std::regex_search(data.c_str(), m, include);
	if (match) {
		for (unsigned int i = 0; i < m.size(); i++) {
			if (i == 1)
				first_match = m[i];
			if (i == 2)
				second_match = m[i];
		}
		return LineType::INCLUDE;
	}

	std::regex define("^\\s*#define\\s+(\\w*)\\s+(.*)$", std::regex::icase | std::regex::ECMAScript);
    match = std::regex_search(data.c_str(), m, define);
	if (match) {
		for (unsigned int i = 0; i < m.size(); i++) {
			if (i == 1)
				first_match = m[i];
			if (i == 2)
				second_match = m[i];
			
		}
		return LineType::DEFINE;
	}
	return LineType::REGULAR;

}
void Line::replace( Defines& defines, std::string & matching) {
	std::cmatch m;
	if (matching.empty())
		return; 
	std::string pattern = "\\b(" + matching + ")\\b";
	std::regex definelist(pattern.c_str(), std::regex::ECMAScript);
	bool match = true;
	Limiter limiter; 
	std::string term; 
	while (match) {
		match = std::regex_search(data.c_str(), m, definelist);
		if (match) {
			term = m[1];
			std::string pattern = "(\\b)(" + term + ")(\\b)";
			std::regex_search(data.c_str(), m, std::regex(pattern));
			std::string replacement;
			defines.find(term, replacement);
			std::string replacement_format = "$01" + replacement + "$03"; 
			data = std::regex_replace(data.c_str(), std::regex(pattern, std::regex::ECMAScript), replacement_format);
		}
		if (limiter.increment_and_test_for_limit()) break; 
	}
	limiter.report("define replacement:" + term);
}
void Line::calculate(){
	std::cmatch m;
	std::regex equal("\\s*=(.*)", std::regex::ECMAScript);
	bool match = std::regex_search(data.c_str(), m, equal);
	if (match) {
		std::string term = m[1];
		std::regex function("^\\s*(\\w+)\\((.*)\\)\\s*$", std::regex::ECMAScript);
		bool match = std::regex_search(term.c_str(), m, function);
		if (match) {
			std::string function_name = m[1];
			std::string parameter_list = m[2];
			data = Calculate::execute(function_name, parameter_list);
			return;
			}		
		if (!term.empty())
			data = Calculate::calculate(term); 
		}
	}
