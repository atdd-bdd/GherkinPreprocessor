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
	std::string to_insert_array[] = {
		"Insert Text 1",
		"Insert Text 2"
	};
	const int INSERT_SIZE = sizeof(to_insert_array) / sizeof(std::string);
	Helper::create_file(Filename("include.txt"), to_insert_array, INSERT_SIZE);

	// Create source file 
	std::string original_lines_array[] = {
		"Original Text 1",
		"#include \"include.txt\"",
		"Original Text 2"
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);

	std::string updated_lines_array[] = {
		"Original Text 1",
		"Insert Text 1",
		"Insert Text 2",
		"Original Text 2"
	};
	const int UPDATED_SIZE = sizeof(updated_lines_array) / sizeof(std::string);
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);
}

TEST_CASE("Simple insert with system file", "[include]") {
	Pathname::set_system_path(std::string("../"));
	// Given insert file 
	std::string to_insert_array[] = {
		"Insert Text 1",
		"Insert Text 2"
	};
	const int INSERT_SIZE = sizeof(to_insert_array) / sizeof(std::string);
	Helper::create_file(Filename("../elsewhere.txt"), to_insert_array, INSERT_SIZE);

	// Create source file 
	std::string original_lines_array[] = {
		"Original Text 1",
		"#include <elsewhere.txt>",
		"Original Text 2"
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);


	std::string updated_lines_array[] = {
		"Original Text 1",
		"Insert Text 1",
		"Insert Text 2",
		"Original Text 2"
	};
	const int UPDATED_SIZE = sizeof(updated_lines_array) / sizeof(std::string);

	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);
}

TEST_CASE("Recursive  insert", "[include]") {
	// Given insert file 
	std::string to_insert_array[] = {
		"#include \"include1.txt\"",
		"Insert Text 2"
	};
	const int INSERT_SIZE = sizeof(to_insert_array) / sizeof(std::string);
	Helper::create_file(Filename("include.txt"), to_insert_array, INSERT_SIZE);
	std::string to_insert_array1[] = {
		"Insert Text A",
		"Insert Text B"
	};
	const int INSERT_SIZE_A = sizeof(to_insert_array1) / sizeof(std::string);
	Helper::create_file(Filename("include1.txt"), to_insert_array1, INSERT_SIZE_A);

	// Create source file 
	std::string original_lines_array[] = {
		"Original Text 1",
		"#include \"include.txt\"",
		"Original Text 2"
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);

	std::string updated_lines_array[] = {
		"Original Text 1",
		"Insert Text A",
		"Insert Text B",
		"Insert Text 2",
		"Original Text 2"
	};
	const int UPDATED_SIZE = sizeof(updated_lines_array) / sizeof(std::string);

	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);
}
TEST_CASE("Recursive insert", "[include]") {
	// Given insert file 
	std::string to_insert_array[] = {
		"#include \"include.txt\"",
	};
	const int INSERT_SIZE = sizeof(to_insert_array) / sizeof(std::string);
	Helper::create_file(Filename("include.txt"), to_insert_array, INSERT_SIZE);

	// Create source file 
	std::string original_lines_array[] = {
		"Original Text 1",
		"#include \"include.txt\"",
		"Original Text 2"
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);


	Helper::run_test_with_error("original.feature", original_lines_array, ORIGINAL_SIZE,
		"Includes \"include.txt\" limit exceeded");

}

TEST_CASE("Simple define", "[define]") {
	std::string original_lines_array[] = {
		"#define SOMETHING 1",
		"Unchanged text",
		"Something is SOMETHING"
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);
	std::string updated_lines_array[] = {
		"Unchanged text",
		"Something is 1"
	};
	const int UPDATED_SIZE = sizeof(updated_lines_array) / sizeof(std::string);
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);
}

TEST_CASE("Redefine", "[define]") {
	std::string original_lines_array[] = {
		"#define SOMETHING 1",
		"#define SOMETHING 2",
		"Unchanged text",
		"Something is SOMETHING"
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);

	Helper::run_test_with_error("original.feature", original_lines_array, ORIGINAL_SIZE,
		"redefinition #define SOMETHING to be  2");

}

TEST_CASE("Redefine allowed ", "[define]") {
	std::string original_lines_array[] = {
		"@allow_redefines",
		"#define SOMETHING 1",
		"Unchanged text",
		"Something is SOMETHING",
		"#define SOMETHING 2",
		"Unchanged text",
		"Something is SOMETHING",
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);

	std::string updated_lines_array[] = {
		"@allow_redefines",
		"Unchanged text",
		"Something is 1",
		"Unchanged text",
		"Something is 2",
	};
	const int UPDATED_SIZE = sizeof(updated_lines_array) / sizeof(std::string);
	Lines updated_lines(updated_lines_array, UPDATED_SIZE);
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);


}


TEST_CASE("Redefine not allowed ", "[define]") {
	std::string original_lines_array[] = {
		"#define SOMETHING 1",
		"Unchanged text",
		"Something is SOMETHING",
		"#define SOMETHING 2",
		"Unchanged text",
		"Something is SOMETHING",
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);

	std::string updated_lines_array[] = {
		"Unchanged text",
		"Something is 1",
		"Unchanged text",
		"Something is 1",
	};
	const int UPDATED_SIZE = sizeof(updated_lines_array) / sizeof(std::string);
	Lines updated_lines(updated_lines_array, UPDATED_SIZE);
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);


}
 
TEST_CASE("Needs preprocessing removed ", "[define]") {
	std::string original_lines_array[] = {
		"@needs_preprocessing @other",
		"Unchanged text 1",
		"Unchanged text 2",

	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);

	std::string updated_lines_array[] = {
		" @other",
		"Unchanged text 1",
		"Unchanged text 2",
	};
	const int UPDATED_SIZE = sizeof(updated_lines_array) / sizeof(std::string);
	Lines updated_lines(updated_lines_array, UPDATED_SIZE);
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);


}


TEST_CASE("Recursive define", "[define]") {
	std::string original_lines_array[] = {
		"#define SOMETHING SOMETHING",
		"Unchanged text",
		"Something is SOMETHING"
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);
	Helper::run_test_with_error("original.feature", original_lines_array, ORIGINAL_SIZE,
		"define replacement:SOMETHING limit exceeded");

}



TEST_CASE("Mulitple defines", "[define]") {

	// Create source file 
	std::string original_lines_array[] = {
		"#define SOMETHING_ELSE 2",
		"#define SOMETHING 1",
		"#define A1 X",
		"Unchanged text",
		"Something is SOMETHING",
		"Something else is SOMETHING_ELSE",
		"Two are SOMETHING and SOMETHING_ELSE",
		"Value of a1 is A1"
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);
	std::string updated_lines_array[] = {
		"Unchanged text",
		"Something is 1",
		"Something else is 2",
		"Two are 1 and 2",
		"Value of a1 is X"
	};
	const int UPDATED_SIZE = sizeof(updated_lines_array) / sizeof(std::string);

	Lines updated_lines(updated_lines_array, UPDATED_SIZE);
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);

}
TEST_CASE("Mulitple defines within defines", "[define]") {

	// Create source file 
		std::string original_lines_array[] = {
		"#define SOMETHING_ELSE SOMETHING + 2",
		"#define SOMETHING 1",
		"#define A1 X",
		"Unchanged text",
		"Something is SOMETHING",
		"Something else is SOMETHING_ELSE",
		"Two are SOMETHING and SOMETHING_ELSE",
		"Value of a1 is A1"
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);

	std::string updated_lines_array[] = {
		"Unchanged text",
		"Something is 1",
		"Something else is 1 + 2",
		"Two are 1 and 1 + 2",
		"Value of a1 is X"
	};
	const int UPDATED_SIZE = sizeof(updated_lines_array) / sizeof(std::string);
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);

}

TEST_CASE("CSV insert", "[include]") {
	// Given insert file 
	std::string to_insert_array[] = {
		"a,b,c",
		"1,2,3",
		"4,5,6" };
	const int INSERT_SIZE = sizeof(to_insert_array) / sizeof(std::string);
	Helper::create_file(Filename("include.csv"), to_insert_array, INSERT_SIZE);

	// Create source file 
	std::string original_lines_array[] = {
		"Original Text 1",
		"#include \"include.csv\"",
		"Original Text 2"
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);

	std::string updated_lines_array[] = {
		"Original Text 1",
		"|a|b|c|",
		"|1|2|3|",
		"|4|5|6|",
		"Original Text 2"
	};
	const int UPDATED_SIZE = sizeof(updated_lines_array) / sizeof(std::string);

	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);
}

TEST_CASE("Calculated define", "[define]") {
	std::string original_lines_array[] = {
		"#define SOMETHING = 1 +2",
		"Unchanged text",
		"Something is SOMETHING"
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);
	std::string updated_lines_array[] = {
		"Unchanged text",
		"Something is 3"
	};
	const int UPDATED_SIZE = sizeof(updated_lines_array) / sizeof(std::string);
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);
}

TEST_CASE("Calculated define with error", "[define]") {
	std::string original_lines_array[] = {
		"#define SOMETHING = NOT_THERE()",
		"Something is SOMETHING"
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);

	Helper::run_test_with_error("original.feature", original_lines_array, ORIGINAL_SIZE,
		"Unknown function to calculate NOT_THERE");
}

TEST_CASE("Calculated local function define", "[define]") {
	std::string original_lines_array[] = {
		"#define TODAY = GET_TODAY()",
		"#define OFFSETED = DATE_WITH_OFFSET(\"10-JAN-2020\",3)",
		"#define TODAY_OFFSET = DATE_WITH_OFFSET(TODAY, 2)",	
		"#define DIFFERENCE = DIFFERENCE_IN_DAYS(\"10-JAN-2020\",OFFSETED)",
		"Today TODAY",
		"Today offset TODAY_OFFSET", 
		"Offseted OFFSETED",
		"Difference DIFFERENCE"
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);

	Date d;
	std::string ds = d.to_string();
	Date d1 = d.offset_by(2);
	std::string d1s = d1.to_string();
	std::string updated_lines_array[] = {
		"Today " + ds, 
		"Today offset " + d1s,
		"Offseted 13-JAN-2020",
		"Difference 3"
	};
	const int UPDATED_SIZE = sizeof(updated_lines_array) / sizeof(std::string);
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
#if 0
TEST_CASE("Lots of  define", "[define]") {
	std::string original_lines_array[] = {
"#define SOMETHING01 01",
"Unchanged text",
"Something is SOMETHING01",
"#define SOMETHING02 02",
"Unchanged text",
"Something is SOMETHING02",
"#define SOMETHING03 03",
"Unchanged text",
"Something is SOMETHING03",
"#define SOMETHING04 04",
"Unchanged text",
"Something is SOMETHING04",
"#define SOMETHING05 05",
"Unchanged text",
"Something is SOMETHING05",
"#define SOMETHING06 06",
"Unchanged text",
"Something is SOMETHING06",
"#define SOMETHING07 07",
"Unchanged text",
"Something is SOMETHING07",
"#define SOMETHING08 08",
"Unchanged text",
"Something is SOMETHING08",
"#define SOMETHING09 09",
"Unchanged text",
"Something is SOMETHING09",
"#define SOMETHING10 10",
"Unchanged text",
"Something is SOMETHING10",
"#define SOMETHING11 11",
"Unchanged text",
"Something is SOMETHING11",
"#define SOMETHING12 12",
"Unchanged text",
"Something is SOMETHING12",
"#define SOMETHING13 13",
"Unchanged text",
"Something is SOMETHING13",
"#define SOMETHING14 14",
"Unchanged text",
"Something is SOMETHING14",
"#define SOMETHING15 15",
"Unchanged text",
"Something is SOMETHING15",
"#define SOMETHING16 16",
"Unchanged text",
"Something is SOMETHING16",
"#define SOMETHING17 17",
"Unchanged text",
"Something is SOMETHING17",
"#define SOMETHING18 18",
"Unchanged text",
"Something is SOMETHING18",
"#define SOMETHING19 19",
"Unchanged text",
"Something is SOMETHING19",
"#define SOMETHING20 20",
"Unchanged text",
"Something is SOMETHING20",
	};
	const int ORIGINAL_SIZE = sizeof(original_lines_array) / sizeof(std::string);

	std::string updated_lines_array[] = {
"Unchanged text",
"Something is 01",
"Unchanged text",
"Something is 02",
"Unchanged text",
"Something is 03",
"Unchanged text",
"Something is 04",
 "Unchanged text",
"Something is 05",
"Unchanged text",
"Something is 06",
"Unchanged text",
"Something is 07",
"Unchanged text",
"Something is 08",
"Unchanged text",
"Something is 09",
"Unchanged text",
"Something is 10",
"Unchanged text",
"Something is 11",
"Unchanged text",
"Something is 12",
"Unchanged text",
"Something is 13",
"Unchanged text",
"Something is 14",
"Unchanged text",
"Something is 15",
"Unchanged text",
"Something is 16",
"Unchanged text",
"Something is 17",
"Unchanged text",
"Something is 18",
"Unchanged text",
"Something is 19",
"Unchanged text",
"Something is 20" ,
	};
	const int UPDATED_SIZE = sizeof(updated_lines_array) / sizeof(std::string);
	Helper::run_test("original.feature", original_lines_array, ORIGINAL_SIZE,
		"updated.feature", updated_lines_array, UPDATED_SIZE);
}
#endif

