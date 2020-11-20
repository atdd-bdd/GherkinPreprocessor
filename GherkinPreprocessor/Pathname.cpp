#include "Pathname.h"

Pathname Pathname::local_path("");   // switch to Pathname 
Pathname Pathname::system_path(""); 

Pathname::Pathname(std::string name) {
	data = name;
	if (name.size() == 0)
		return;
	std::cmatch m;
	std::regex include("[\\/]$", std::regex::icase | std::regex::ECMAScript);
	bool match = std::regex_search(data.c_str(), m, include);
	if (!match)
		data += "/";

}
 std::string Pathname::get_value() {
	return data;
}
 void Pathname::set_system_path(const std::string& value) {
	 system_path = value; 
}
 void Pathname::set_local_path(const std::string& value) {
	 local_path = value;
}