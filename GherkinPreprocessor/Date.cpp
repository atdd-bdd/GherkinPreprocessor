#include "Date.h"
Date::Date(int month, int day, int year) {
	this->month = month;
	this->day = day;
	this->year = year;
	validate();
}
int Date::days_between(Date& other) {
	int this_jdn = this->to_JDN();
	int other_jdn = other.to_JDN();
	int difference = this_jdn - other_jdn;
	return difference;
}
 Date Date::offset_by(int days) {
	int this_jdn = this->to_JDN();
	int other_jdn = this_jdn + days;
	Date d;
	d.from_jdn(other_jdn);
	return d;
}
std::string Date::to_string() {
	std::string result;
	result = std::to_string(day) + "-" + months[month - 1] + "-" + std::to_string(year);
	return result;
}
bool Date::validate()
{
	int month_old = month;
	int year_old = year;
	int day_old = day;
	bool valid = true;
	if (month < 1) {
		month = 1;
		valid = false;
	}
	if (month > 12) {
		month = 12;
		valid = false;
	}
	if (day < 1) {
		day = 1;
		valid = false;
	}
	if (day > 31) {
		day = 31;
		valid = false;
	}
	if (!valid) {
		Log::write(LogType::SEVERE, "Invalid date m " + std::to_string(month_old)
			+ " day " + std::to_string(day_old) + " year " + std::to_string(year_old));
	}
	return valid;
}
 Date::Date(std::string in) {
	std::cmatch m;
	std::regex parm("(\\d+)-(\\w+)-(\\d+)", std::regex::ECMAScript);
	bool match = std::regex_search(in.c_str(), m, parm);
	if (match) {
		std::string temp = m[1];
		day = std::atoi(temp.c_str());
		temp = m[3];
		year = std::atoi(temp.c_str());
		temp = m[2];
		month = 0;
		for (int i = 0; i < 12; i++)
		{
			if (temp == months[i])
			{
				month = i + 1;
				break;
			}
		}
		validate();
	}
}
 Date::Date() {

	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);

	year = 1900 + ltm.tm_year;
	month = 1 + ltm.tm_mon;
	day = ltm.tm_mday;
}
 unsigned int Date::to_JDN() {
	int a = (14 - month) / 12;
	int m = month + 12 * a - 3;
	int y = year + 4800 - a;
	int jdn = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
	return jdn;
}
 void Date::from_jdn(unsigned int jdn) {
	int a = jdn + 32044;
	int b = (4 * a + 3) / 146097;
	int c = a - (146097 * b) / 4;
	int d = (4 * c + 3) / 1461;
	int e = c - (1461 * d) / 4;
	int m = (5 * e + 2) / 153;
	day = e - (153 * m + 2) / 5 + 1;
	month = m + 3 - 12 * (m / 10);
	year = 100 * b + d - 4800 + m / 10;

}

