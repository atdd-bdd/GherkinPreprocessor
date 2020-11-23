#include "Date.h"
#include "Calculate.h"
std::string date_with_offset(std::string parameters[]) {
	Date d1(parameters[0]);
	int offset = atoi(parameters[1].c_str());
	Date d2 = d1.offset_by(offset);
	return d2.to_string();
}
std::string today_with_offset(std::string parameters[])
{
	Date d;
	int offset = atoi(parameters[0].c_str());
	Date d2 = d.offset_by(offset);
	return d2.to_string();
}

std::string today(std::string parameters[])
{
	Date d;
	return d.to_string();
}
std::string offset_between_two_dates(std::string parameters[]) {
	Date d1(parameters[0]);
	Date d2(parameters[1]); 
	int offset = d2.days_between(d1);
	return std::to_string(offset); 
}

Function Calculate::functions[] = {
		{"GET_TODAY", today},
		{"DATE_WITH_OFFSET", date_with_offset},
		{"TODAY_OFFSET_BY", today_with_offset},
	    {"DIFFERENCE_IN_DAYS",offset_between_two_dates },
};


int Calculate::FUNCTION_SIZE = sizeof(functions) / sizeof(Function);
