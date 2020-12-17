#include "Defines.h"
#include "Log.h"
#include "Line.h"
#include "atmsp.h"
bool Defines::redefines_allowed = false; 
void Defines::insert(std::string& term, std::string& definition) {
	auto s = data.find(term);
	if (s == data.end()) {
		auto n = data.insert(std::make_pair(term, definition));
		std::string result = make_search_with_bars();
		// Do the substitutions already
		replace_in_a_define(n.first, result);
		}
	else
	{
		std::string previous = s->second;
		if (previous != definition)
			Log::write(LogType::WARNING, "redefinition #define " + term + " to be  " + definition);
		if (redefines_allowed) {
			data.erase(s);
			auto n = data.insert(std::make_pair(term, definition));
			std::string result = make_search_with_bars();
			// Do the substitutions already
			replace_in_a_define(n.first, result);
			}

	}
}

bool Defines::find(const std::string& term, std::string& definition)
{
	auto s = data.find(term);
	if (s != data.end())
	{
		definition = s->second;
		return true;
	}
	return false;
}
void Defines::replace_in_all_defines() {
	// used if want to do forward references in #defines 

	std::string result = make_search_with_bars();
	// Do the substitutions already
	for (auto s = data.begin(); s != data.end(); s++) {
		replace_in_a_define(s, result);
	}

	return;
}

void Defines::replace_in_a_define(std::map<std::string, std::string>::iterator& s, std::string& result)
{
	Line l(s->second);

	l.replace(*this, result);
	// TBD do the check for = and expression calculation here 
	l.calculate();
}

std::string Defines::make_search_with_bars()
{
	std::string result = "";
	for (auto s = data.begin(); s != data.end(); s++) {
		result += s->first + "|";
	}
	result = result.substr(0, result.size() - 1);
	return result;
}

