#include "Log.h"
#include "Pathname.h"
#include <string>
#include <list>

 bool Log::terminate;
 std::list<std::string> list; 

 void Log::clear() {
	 list.clear(); 
 }
 bool Log::contains(std::string line) {
	 for (auto l = list.begin(); l != list.end(); l++)
	 {
		 if (*l == line)
			 return true; 
	 }
	 return false; 
    }
void Log::write(LogType log_type, const std::string& message) {
	list.push_back(message); 
	if (log_type == LogType::SEVERE)
		std::cerr << "Error " << message << std::endl;
	else 
		std::cerr << "Warning" << message << std::endl;
	if (log_type == LogType::SEVERE)
		terminate = true;
}
bool Log::is_terminate() {
	return terminate;
}

void Log::print() {
	for (auto l = list.begin(); l != list.end(); l++)
	{
		std::cout << *l << std::endl; 
	}
}
