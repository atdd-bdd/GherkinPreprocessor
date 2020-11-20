#pragma once
#include <string>
#include "LocalFunctions.h"

class Calculate
{
public: static std::string execute(std::string & name, std::string&  parameter);
public: static std::string calculate(std::string & expression);
public: static Function functions[]; 
public: static int FUNCTION_SIZE; 
public: static std::string calculate_int(std::string& expression); 
public: static std::string calculate_double(std::string& expression);
};


