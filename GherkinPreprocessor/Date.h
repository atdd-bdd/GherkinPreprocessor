#pragma once
#include <ctime>
#include <string>
#include <iostream>
#include <regex>
#include "Log.h"

class Date
{
private: int month = 1;
private: int day = 1;
private: int year = 1;
private: const std::string months[12] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN","JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };
public: Date(int month, int day, int year);
public: int days_between(Date& other);
public: Date offset_by(int days);
public:std::string to_string();
private: bool validate();
public: Date(std::string in);
public: Date();
public: unsigned int to_JDN();
public: void from_jdn(unsigned int jdn);
};

