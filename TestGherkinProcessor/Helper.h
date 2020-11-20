#pragma once
#include "catch2/catch.hpp"
#include "Filename.h"
#include "Lines.h"
class Helper {
public: static void create_file(Filename name, std::string string_array[], const int& array_size);
public: static void print_file(Filename name);
public: static bool compare_to_file(Filename name, Lines to_compare);
public: static bool compare_line_to_file(Filename name, std::string to_compare);
public: static void run_test(
	std::string original_name, std::string original_data[], int original_data_size,
	std::string updated_name, std::string updated_data[], int updated_data_size);
public: static void run_test_with_error(
	std::string original_name, std::string original_data[], int original_data_size, std::string log_line);
};

