#include "Defines.h"
#include "Log.h"
#include "Line.h"
#include "atmsp.h"
void Defines::insert(std::string& term, std::string& definition) {
	auto s = data.find(term);
	if (s == data.end())
		data.insert(std::make_pair(term, definition));
	else
		Log::write(LogType::WARNING, "Attempted redefinition #define " + term + " to be  " + definition);
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
std::string Defines::get_terms_with_bars() {
	std::string result = "";

	for (auto s = data.begin(); s != data.end(); s++) {
		result += s->first + "|";
	}
	result = result.substr(0, result.size() - 1);
	// Do the substitutions already
	for (auto s = data.begin(); s != data.end(); s++) {
		Line l(s->second); 
		
		l.replace(*this, result);
		// TBD do the check for = and expression calculation here 
		l.calculate(); 
	}

	return result;
}

