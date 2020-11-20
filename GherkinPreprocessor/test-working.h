#pragma once

#include "Processor.h"
#include <string>
#include "Lines.h"
// #include "catch2/catch.hpp"
class Test
{
public: static void simple_insert() {
	// Given insert file 
	const int INSERT_SIZE = 2;
	std::string to_insert_array[INSERT_SIZE] = {
		"Insert Text 1",
		"Insert Text 2"
	};
	create_file(Filename("include.txt"), to_insert_array, INSERT_SIZE);
	// Create source file 
	const int ORIGINAL_SIZE = 3; 
	std::string original_lines_array[ORIGINAL_SIZE] = {
		"Original Text 1",
		"#include \"include.txt\"",
		"Original Text 2"
	};
	create_file(Filename("original.feature"), original_lines_array, ORIGINAL_SIZE);

	// When process 
	Processor p; 
	p.process(Filename("original.feature"), Filename("updated.feature"));

	// Then 
	print_file(Filename("updated.feature")); 
	

	}
	  static void create_file(Filename name, std::string string_array[], const int& array_size)
	  {
		  Lines to_insert_lines(string_array, array_size);
		  to_insert_lines.write_lines(name);
		  }
	  static void print_file(Filename name)
	  {
		  Lines to_read_lines;
		  to_read_lines.read_lines(name);
		  std::cout << "File out: " << name.get_value() << "-----------------\n";
		  to_read_lines.print_lines(std::cout);
		  std::cout << "-------------------------------------------------\n";
	  }

};

