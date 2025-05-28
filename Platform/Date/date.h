// Copyright 2025 Kanukova Margarita

#ifndef DATE_H
#define DATE_H
#include<string>
#include <iostream>
class Date {
	int _year;
	int _month;
	int _day;
public:
	Date(int, int, int);
	Date(const std::string&);

	void set_day(const int);
	void set_month(const int);
	void set_year(const int);

	const int get_day() const noexcept;
	const int get_month() const noexcept;
	const int get_year() const noexcept;

private:
	bool check_correct_date(int, int, int);
	int day_in_month(int, int);
};

#endif  // PLATFORM_DATE_DATE_H_
