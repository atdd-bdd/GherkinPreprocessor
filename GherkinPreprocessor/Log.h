#pragma once
#include <iostream>
#include <string>
#include <fstream>
enum class LogType {WARNING, SEVERE};
class Log
{
private: static std::ofstream log; 
private: static bool terminate;
public: static std::string LOG_FILENAME; // "log.txt"
public: Log() {}
public: static void clear();
public: static void write(LogType log_type, const std::string& message);
public: static bool is_terminate();
public: static void print(); 
public: static bool contains(std::string line); 
};

