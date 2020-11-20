#include "Calculate.h"
#include "atmsp.h"
#include <regex>
#include <iostream>
#include "Log.h"
#include "LocalFunctions.h"


std::string Calculate::execute(std::string & name, std::string & parameter) {

	
	std::string parameters[5] = {
		"", "", "", "", "" };
	std::cmatch m;
	std::regex parm("\\s*([^,]*)?\\s*,?\\s*([^,]*)?\\s*,?\\s*([^,]*)?,?", std::regex::ECMAScript );
	bool match = std::regex_search(parameter.c_str(), m, parm);
	if (match) {
		for (unsigned int j = 1; j < m.size(); j++) {
			parameters[j - 1] = m[j];
		}

	}
	for (int i = 0; i < FUNCTION_SIZE; i++) {
		
		if (functions[i].name == name) {
			std::string result = (*functions[i].function)(parameters);
			return result;
		}
	}
	Log::write(LogType::SEVERE, "Unknown function to calculate " + name); 
	return "Not Found"; 
	}

	std::string Calculate::calculate(std::string & expression) {

		std::cmatch m; 
		std::regex parm("\\.", std::regex::ECMAScript);
		bool match = std::regex_search(expression.c_str(), m, parm);
		if (match) {
			return calculate_double(expression);
			
		}
		else {
			return calculate_int(expression);

		}

	}
