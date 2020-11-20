#include "Processor.h"
#include "Defines.h"

#include "Limiter.h"
void Processor::process(Filename in_name, Filename out_name) {
	Defines defines; 
	Lines in;
	in.read_lines(in_name);
	
	std::list<std::string> & in_data = in.get_data();
	std::string first_match;
	std::string second_match; 
	Limiter limiter; 
	// Include 
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
	limiter.report("Includes ");
	// Get the #defines
	for (auto s = in_data.begin(); s != in_data.end();) {
		Line l(*s);
		if (l.parse(first_match, second_match) == LineType::DEFINE) {
			defines.insert(first_match, second_match);
			s = in_data.erase(s);
		}
		else
			s++;
	}
	// Now do the replacements 
	std::string matches = defines.get_terms_with_bars(); 
	for (auto s = in_data.begin(); s != in_data.end(); s++) {
		Line l(*s);
			l.replace(defines, matches);
	}
	
	in.write_lines(out_name);

}

