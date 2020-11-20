#pragma once
#include "Utility.h"
#include "Processor.h"
#include <string>
#include "Lines.h"
class Test
{
public: static void simple_insert() {
	const int INSERT_SIZE = 2;
	std::string to_insert_array[INSERT_SIZE] = {
		"Insert Text 1",
		"Insert Text 2"
	};
	Lines to_insert_lines(to_insert_array, INSERT_SIZE);
	to_insert_lines.print_lines(std::cout); 
	to_insert_lines.write_lines("include.txt"); 
	Lines test_lines; 
	test_lines.read_lines("include.txt"); 
	test_lines.print_lines(std::cout); 
	Lines file_lines; 
	file_lines.read_lines("notepad.txt");
	file_lines.print_lines(std::cout); 

#if 0
	std::string original = "Text before\n#include \"include.txt\"\nText after"; 
	Utility::write_file("include.txt", to_insert); 
	Processor p; 
	std::string result = p.process(original);
#endif 
	}
};

