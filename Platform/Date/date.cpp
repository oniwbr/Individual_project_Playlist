#include "date.h"

Date::Date(int d, int m, int y) {
	if (!check_correct_date(d, m, y)) throw std::invalid_argument("Incorrect date!\n");
	_day = d;
	_month = m;
	_year = y;
}

Date::Date(const std::string& date) {
	if (date.empty()) throw std::invalid_argument("The string of date is empty!\n");
	size_t dot1 = date.find('.');
	size_t dot2 = date.find('.', dot1 + 1);

	std::string day = date.substr(0, dot1);
	std::string month = date.substr(dot1 + 1, dot2 - dot1 - 1);
	std::string year = date.substr(dot2 + 1);

	int d = std::stoi(day);
	int m = std::stoi(month);
	int y = std::stoi(year);

	if (!check_correct_date(d, m, y)) throw std::invalid_argument("Incorrect date!\n");
	_day = d;
	_month = m;
	_year = y;
}

void Date::set_day(const int d) {
	if (!check_correct_date(d, _month, _year)) throw std::invalid_argument("Incorrect number of day!\n");
	_day = d;
}

void Date::set_month(const int m) {
	if (!check_correct_date(_day, m, _year)) throw std::invalid_argument("Incorrect number of month!\n");
	_month = m;
}

void Date::set_year(const int y) {
	if (!check_correct_date(_day, _month, y)) throw std::invalid_argument("Incorrect number of year!\n");
	_year = y;
}

const int Date::get_day() const noexcept { return _day; }

const int Date::get_month() const noexcept { return _month; }

const int Date::get_year() const noexcept { return _year; }

bool Date::check_correct_date(int d, int m, int y) {
	if (y < 1) return false;
	if (m < 1 || m > 12) return false;
	if (d<1 || d > day_in_month(m, y)) return false;
	return true;
}

int Date::day_in_month(int m, int y) {
	switch (m)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11: return 30;
	case 2: 
		if ((y % 400 == 0) && (y % 100 != 0) && (y % 4 == 0)) return 29;
		else return 28;
	default:
		throw std::invalid_argument("Incorrect number of month!\n");
	}
}