#include "Log.h"
#include "Pathname.h"
#include <string>
#include <list>
std::ofstream Log::log;
 bool Log::terminate;
 std::list<std::string> list; 
 std::string Log::LOG_FILENAME = Pathname::local_path.get_value() + "log.txt";
 void Log::clear() {
	 LOG_FILENAME = Pathname::local_path.get_value() + "log.txt";
	 if (log.is_open())
		 log.close();
	 log.open(LOG_FILENAME, std::ofstream::trunc);
	 if (!log.good())
	 {
		 std::cerr << "Unable to open log file " + LOG_FILENAME;
		 exit(1);
	 }
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
	LOG_FILENAME = Pathname::local_path.get_value() + "log.txt";
	if (!log.is_open())
	{
		log.open(LOG_FILENAME, std::ofstream::trunc);
		if (!log.good())
		{
			std::cerr << "Unable to open log file " + LOG_FILENAME;
			exit(1);
		}
	}
	log.write(message.c_str(), message.size());
	log.write("\n", 1);
	log.flush();
	list.push_back(message); 
	if (log_type == LogType::SEVERE)
		terminate = true;
}
bool Log::is_terminate() {
	return terminate;
}

void Log::print() {
	LOG_FILENAME = Pathname::local_path.get_value() + "log.txt";
	if (log.is_open())
	{
		log.close();
	}
	std::ifstream myfile;
	myfile.open(LOG_FILENAME);
	std::string line;
	while (std::getline(myfile, line)) {
		std::cout << line << "\n"; 
	}
	myfile.close();

	
}