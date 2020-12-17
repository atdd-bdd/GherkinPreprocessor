#include "Processor.h"
#include "Defines.h"

#include "Limiter.h"
#include "Defines.h"
void Processor::process(Filename in_name, Filename out_name) {
	Defines defines; 
	Lines in;
	in.read_lines(in_name);
	
	std::list<std::string> & in_data = in.get_data();
	std::string first_match;
	std::string second_match; 
	Limiter limiter; 
	// Check for the two flags on the first line
	// Include 
	if (in_data.begin() != in_data.end())
	{
		std::string x = *in_data.begin();
		std::string NEEDS_PREPROCESSING = "@needs_preprocessing";
		std::string ALLOW_REDFINES = "@allow_redefines";
		size_t pos = x.find(NEEDS_PREPROCESSING); 
		int size = NEEDS_PREPROCESSING.length();
		if (pos != std::string::npos)
		{
			std::string new_line = x.replace(pos, size, "");
			*in_data.begin() = new_line; 
		}
		Defines::redefines_allowed = false;
		if (x.find(ALLOW_REDFINES)!= std::string::npos)
			Defines::redefines_allowed = true;
	}
	for (auto s = in_data.begin(); s != in_data.end(); ) {
		
		Line l(*s);
		if (l.parse(first_match, second_match) == LineType::INCLUDE) {
			Filename insert(first_match); 
			Lines to_insert; 
			to_insert.read_lines(insert); 
			std::list<std::string>& insert_data = to_insert.get_data();
			auto s_new = in_data.insert(s, insert_data.begin(), insert_data.end());
			in_data.erase(s);
			s = s_new; 
			if (limiter.increment_and_test_for_limit()) break; 
		}
		else
			s++;
	}
	limiter.report("Includes " + first_match);
	// Get the #defines
		for (auto s = in_data.begin(); s != in_data.end();) {
		Line l(*s);
		if (l.parse(first_match, second_match) == LineType::DEFINE) {
			defines.insert(first_match, second_match);
			s = in_data.erase(s);
		}
		else
		{
			std::string matches = defines.make_search_with_bars();
			Line l(*s);
			l.replace(defines, matches);
			s++;
		}
	}

	in.write_lines(out_name);

}

