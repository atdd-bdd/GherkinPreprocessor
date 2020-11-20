#include "Test.h"
#pragma once

#include "Processor.h"
#include <string>
#include "Lines.h"
#include "catch2/catch.hpp"
#include "Log.h"
#include "Filename.h"
#include "Date.h"
#include "Pathname.h"
#include "Helper.h"

TEST_CASE("Simple insert", "[include]") {
	// Given insert file 
	const int INSERT_SIZE = 2;
	std::string to_insert_array[INSERT_SIZE] = {
		"Insert Text 1",
		"Insert Text 2"
	};
	Helper::create_file(Filename("include.txt"), to_insert_array, INSERT_SIZE);

	// Create source file 
	const int ORIGINAL_SIZE = 3;
	std::string original_lines_array[ORIGINAL_SIZE] = {
		"Original Text 1",
		"#include \"include.txt\"",
		"Original Text 2"
	};

	const int UPDATED_SIZE = 4;
	std::string updated_lines_array[UPDATED_SIZE] = {
		"Original Text 1",
		"Insert Text 1",
		"Insert Text 2",
		"Original Text 2"
	};

	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);
}

TEST_CASE("Simple insert with system file", "[include]") {
	Pathname::set_system_path(std::string("../"));
	// Given insert file 
	const int INSERT_SIZE = 2;
	std::string to_insert_array[INSERT_SIZE] = {
		"Insert Text 1",
		"Insert Text 2"
	};
	Helper::create_file(Filename("../elsewhere.txt"), to_insert_array, INSERT_SIZE);

	// Create source file 
	const int ORIGINAL_SIZE = 3;
	std::string original_lines_array[ORIGINAL_SIZE] = {
		"Original Text 1",
		"#include <elsewhere.txt>",
		"Original Text 2"
	};

	const int UPDATED_SIZE = 4;
	std::string updated_lines_array[UPDATED_SIZE] = {
		"Original Text 1",
		"Insert Text 1",
		"Insert Text 2",
		"Original Text 2"
	};

	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);
}

TEST_CASE("Recursive  insert", "[include]") {
	// Given insert file 
	const int INSERT_SIZE = 2;
	std::string to_insert_array[INSERT_SIZE] = {
		"#include \"include1.txt\"",
		"Insert Text 2"
	};
	Helper::create_file(Filename("include.txt"), to_insert_array, INSERT_SIZE);
	const int INSERT_SIZE_A = 2;
	std::string to_insert_array1[INSERT_SIZE_A] = {
		"Insert Text A",
		"Insert Text B"
	};
	Helper::create_file(Filename("include1.txt"), to_insert_array1, INSERT_SIZE_A);

	// Create source file 
	const int ORIGINAL_SIZE = 3;
	std::string original_lines_array[ORIGINAL_SIZE] = {
		"Original Text 1",
		"#include \"include.txt\"",
		"Original Text 2"
	};

	const int UPDATED_SIZE = 5;
	std::string updated_lines_array[UPDATED_SIZE] = {
		"Original Text 1",
		"Insert Text A",
		"Insert Text B",
		"Insert Text 2",
		"Original Text 2"
	};

	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);
}
TEST_CASE("Recursive insert", "[include]") {
	// Given insert file 
	const int INSERT_SIZE = 2;
	std::string to_insert_array[INSERT_SIZE] = {
		"#include \"include.txt\"",
	};
	Helper::create_file(Filename("include.txt"), to_insert_array, INSERT_SIZE);

	// Create source file 
	const int ORIGINAL_SIZE = 3;
	std::string original_lines_array[ORIGINAL_SIZE] = {
		"Original Text 1",
		"#include \"include.txt\"",
		"Original Text 2"
	};


	Helper::run_test_with_error("original.feature", original_lines_array, ORIGINAL_SIZE,
		"Includes  limit exceeded");

}

TEST_CASE("Simple define", "[define]") {
	const int ORIGINAL_SIZE = 3;
	std::string original_lines_array[ORIGINAL_SIZE] = {
		"#define SOMETHING 1",
		"Unchanged text",
		"Something is SOMETHING"
	};
	const int UPDATED_SIZE = 2;
	std::string updated_lines_array[UPDATED_SIZE] = {
		"Unchanged text",
		"Something is 1"
	};
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);
}

TEST_CASE("Redefine", "[define]") {
	const int ORIGINAL_SIZE = 4;
	std::string original_lines_array[ORIGINAL_SIZE] = {
		"#define SOMETHING 1",
		"#define SOMETHING 2",
		"Unchanged text",
		"Something is SOMETHING"
	};

	Helper::run_test_with_error("original.feature", original_lines_array, ORIGINAL_SIZE,
		"Attempted redefinition #define SOMETHING to be  2");

}


TEST_CASE("Recursive define", "[define]") {
	const int ORIGINAL_SIZE = 3;
	std::string original_lines_array[ORIGINAL_SIZE] = {
		"#define SOMETHING SOMETHING",
		"Unchanged text",
		"Something is SOMETHING"
	};

	Helper::run_test_with_error("original.feature", original_lines_array, ORIGINAL_SIZE,
		"define replacement limit exceeded");

}



TEST_CASE("Mulitple defines", "[define]") {

	// Create source file 
	const int ORIGINAL_SIZE = 8;
	std::string original_lines_array[ORIGINAL_SIZE] = {
		"#define SOMETHING_ELSE 2",
		"#define SOMETHING 1",
		"#define A1 X",
		"Unchanged text",
		"Something is SOMETHING",
		"Something else is SOMETHING_ELSE",
		"Two are SOMETHING and SOMETHING_ELSE",
		"Value of a1 is A1"
	};
	const int UPDATED_SIZE = 5;
	std::string updated_lines_array[UPDATED_SIZE] = {
		"Unchanged text",
		"Something is 1",
		"Something else is 2",
		"Two are 1 and 2",
		"Value of a1 is X"
	};
	Lines updated_lines(updated_lines_array, UPDATED_SIZE);
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);

}
TEST_CASE("Mulitple defines within defines", "[define]") {

	// Create source file 
	const int ORIGINAL_SIZE = 8;
	std::string original_lines_array[ORIGINAL_SIZE] = {
		"#define SOMETHING_ELSE SOMETHING + 2",
		"#define SOMETHING 1",
		"#define A1 X",
		"Unchanged text",
		"Something is SOMETHING",
		"Something else is SOMETHING_ELSE",
		"Two are SOMETHING and SOMETHING_ELSE",
		"Value of a1 is A1"
	};
	const int UPDATED_SIZE = 5;
	std::string updated_lines_array[UPDATED_SIZE] = {
		"Unchanged text",
		"Something is 1",
		"Something else is 1 + 2",
		"Two are 1 and 1 + 2",
		"Value of a1 is X"
	};
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);

}

TEST_CASE("CSV insert", "[include]") {
	// Given insert file 
	const int INSERT_SIZE = 3;
	std::string to_insert_array[INSERT_SIZE] = {
		"a,b,c",
		"1,2,3",
		"4,5,6" };
	Helper::create_file(Filename("include.csv"), to_insert_array, INSERT_SIZE);

	// Create source file 
	const int ORIGINAL_SIZE = 3;
	std::string original_lines_array[ORIGINAL_SIZE] = {
		"Original Text 1",
		"#include \"include.csv\"",
		"Original Text 2"
	};
	const int UPDATED_SIZE = 5;
	std::string updated_lines_array[UPDATED_SIZE] = {
		"Original Text 1",
		"|a|b|c|",
		"|1|2|3|",
		"|4|5|6|",
		"Original Text 2"
	};
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);
}

TEST_CASE("Calculated define", "[define]") {
	const int ORIGINAL_SIZE = 3;
	std::string original_lines_array[ORIGINAL_SIZE] = {
		"#define SOMETHING = 1 +2",
		"Unchanged text",
		"Something is SOMETHING"
	};
	const int UPDATED_SIZE = 2;
	std::string updated_lines_array[UPDATED_SIZE] = {
		"Unchanged text",
		"Something is 3"
	};
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);
}

TEST_CASE("Calculated define with error", "[define]") {
	const int ORIGINAL_SIZE = 3;
	std::string original_lines_array[ORIGINAL_SIZE] = {
		"#define SOMETHING = NOT_THERE()",
		"Something is SOMETHING"
	};

	Helper::run_test_with_error("original.feature", original_lines_array, ORIGINAL_SIZE,
		"Unknown function to calculate NOT_THERE");
}

TEST_CASE("Calculated local function define", "[define]") {
	const int ORIGINAL_SIZE = 6;
	std::string original_lines_array[ORIGINAL_SIZE] = {
		"#define SOMETHING = GET_TODAY()",
		"#define ELSE = DATE_WITH_OFFSET(\"10-JAN-2020\",3)",
		"#define SOMETHING_ELSE = DATE_WITH_OFFSET(SOMETHING, 2)",
		"Else is ELSE",
		"Something is SOMETHING",
		"Something else is SOMETHING_ELSE"
	};
	Date d;
	std::string ds = d.to_string();
	Date d1 = d.offset_by(2);
	std::string d1s = d1.to_string();
	const int UPDATED_SIZE = 3;
	std::string updated_lines_array[UPDATED_SIZE] = {
		"Else is 13-JAN-2020",
		"Something is " + ds,
		"Something else is " + d1s
	};
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);
}
TEST_CASE("Filename", "[define]") {
	Pathname::set_system_path("xxx/yyy");
	Filename f2("<Two>");
	CHECK("xxx/yyy/Two" == f2.get_value());
	std::string path = Filename::get_directory("abc\\def.x");
	CHECK("abc" == path); 
	std::string path1 = Filename::get_directory("abc/def.x");
	CHECK("abc" == path1);

	Pathname p1("abc");
	CHECK("abc/" == p1.get_value());
	Pathname p2("def/");
	CHECK("def/" == p2.get_value());
	Pathname p3("");
	CHECK("" == p3.get_value());
	Pathname p4(".");
	CHECK("./" == p4.get_value());
}
TEST_CASE("Dates", "[define]") {
	Date d;
	Date d1(12, 1, 2020);
	Date d2("2-JAN-2020");
	std::string ds = d.to_string();
	std::string ds1 = d1.to_string();
	std::string ds2 = d2.to_string();
	CHECK(std::string("1-DEC-2020") == ds1);
	CHECK(std::string("2-JAN-2020") == ds2);
	Date d4(7, 4, 1776);
	Date d5(12, 31, 2000);
	Date d6(2, 8, 2007);
	Date d7(2, 9, 2007);

	int jdn4 = d4.to_JDN();
	int jdn5 = d5.to_JDN();
	int jdn6 = d6.to_JDN();
	int jdn7 = d7.to_JDN();
	CHECK(2369916 == jdn4);
	CHECK(2451910 == jdn5);
	CHECK(2454140 == jdn6);
	CHECK(2454141 == jdn7);
	Date d8;
	d8.from_jdn(jdn4);
	Date d9;
	d9.from_jdn(jdn5);
	Date d10;
	d10.from_jdn(jdn6);
	Date d11;
	d11.from_jdn(jdn7);
	std::string ds8 = d8.to_string();
	std::string ds9 = d9.to_string();
	std::string ds10 = d10.to_string();
	std::string ds11 = d11.to_string();
	CHECK(std::string("4-JUL-1776") == ds8);
	CHECK(std::string("31-DEC-2000") == ds9);
	CHECK(std::string("8-FEB-2007") == ds10);
	CHECK(std::string("9-FEB-2007") == ds11);
	int diff1 = d11.days_between(d10);
	Date d12 = d11.offset_by(3);
	CHECK(diff1 == 1);
	std::string ds12 = d12.to_string();
	CHECK(std::string("12-FEB-2007") == ds12);

}



