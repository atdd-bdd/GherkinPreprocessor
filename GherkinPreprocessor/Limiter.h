#pragma once
#include "Log.h"
class Limiter
{
private: int count; 
private: int MAX_LIMIT = 50; 
public: Limiter() {
	count = 0; 
}
public: bool increment_and_test_for_limit() {
	count++;
	if (count > MAX_LIMIT)
		return true;
	return false; 
}
public: void report(std::string message) {
	if (count > MAX_LIMIT)
		Log::write(LogType::SEVERE, message + " limit exceeded"); 
}
};

