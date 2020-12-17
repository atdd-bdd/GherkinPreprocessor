#include "Helper.h"
#include "Log.h"
#include "Date.h"
#include "Pathname.h"
#include "Filename.h"
#include "Pathname.h"
#include "Processor.h"
void Helper::create_file(Filename name, std::string string_array[], const int& array_size)
{
	Lines to_insert_lines(string_array, array_size);
	to_insert_lines.write_lines(name);
}
void Helper::print_file(Filename name)
{
	Lines to_read_lines;
	to_read_lines.read_lines(name);
	std::cout << "File out: " << name.get_value() << "-----------------\n";
	to_read_lines.print_lines(std::cout);
	std::cout << "-------------------------------------------------\n";

}
bool Helper::compare_to_file(Filename name, Lines to_compare)
{
	Lines to_read_lines;
	to_read_lines.read_lines(name);
	std::list<std::string>& in_data = to_read_lines.get_data();
	std::list<std::string>& other_data = to_compare.get_data();
	CHECK(in_data.size() == other_data.size());
	bool ret = in_data.size() == other_data.size();
	if (ret)
	{
		auto one = in_data.begin();
		auto two = other_data.begin();
		for (; one != in_data.end() && two !=other_data.end(); one++, two++) {
			CHECK(*one == *two);
			ret |= (*one == *two);
		}
	}
	if (!ret)
	{
		std::cerr << "File contents mismatch " << name.get_value() << "\n";
		std::cerr << "Should be : \n";
		to_compare.print_lines(std::cerr);
		std::cerr << "Actual : \n";
		to_read_lines.print_lines(std::cerr);
	}
	return ret;
}
bool Helper::compare_line_to_file(Filename name, std::string to_compare)
{
	Lines to_read_lines;
	to_read_lines.read_lines(name);
	std::list<std::string>& in_data = to_read_lines.get_data();

	bool ret = false;
	for (auto one = in_data.begin(); one != in_data.end(); one++) {
		bool local = (*one == to_compare);
		ret |= local;
	}

	if (!ret)
	{
		std::cerr << "Looking for " << to_compare.c_str() << "\n";
		to_read_lines.print_lines(std::cout);
	}
	CHECK(ret);
	return ret;
}

void Helper::run_test(

	std::string original_name, std::string original_data[], int original_data_size,
	std::string updated_name, std::string updated_data[], int updated_data_size) {
	Log::clear();
	create_file(Filename(original_name), original_data, original_data_size);
	Processor p;
	p.process(Filename(original_name), Filename(updated_name));

	// print_file(Filename(updated_name));
	Lines updated_lines(updated_data, updated_data_size);


	compare_to_file(Filename(updated_name), updated_lines);
}


void Helper::run_test_with_error(
	std::string original_name, std::string original_data[], int original_data_size, std::string log_line) {
	Log::clear();
	Filename tempfile("temp.txt");
	create_file(Filename(original_name), original_data, original_data_size);
	Processor p;
	p.process(Filename(original_name), tempfile);
	bool ret = Log::contains(log_line);
	if (!ret)
	{
		std::cout << "Log file \n";
		Log::print();
		std::cout << "Line \n"; 
		std::cout << log_line << "\n"; 
	}
	CHECK(ret);
}

