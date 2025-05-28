// Copyright 2025 Kanukova Margarita

<<<<<<< HEAD
#ifndef DATE_H
#define DATE_H
#include<string>
#include <iostream>
class Date {
	int _year;
	int _month;
	int _day;
public:
	Date(int,int,int);
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
=======
#ifndef PLATFORM_DATE_DATE_H_
#define PLATFORM_DATE_DATE_H_

class Date {
    int _year;
    int _month;
    int _day;
>>>>>>> 5b0996b27230fded92803b14194277f607c7b82e
};

#endif  // PLATFORM_DATE_DATE_H_
