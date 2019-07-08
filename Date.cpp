/*
Name: Eric Rabiner
Student number: 038806063
Email: erabiner@myseneca.ca
Assignment: MS1
Section: J
Date: March 4, 2019
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Date.h"

using namespace std;
namespace ama {

	void Date::status(int newStatus) {
		d_status = newStatus;
	}

	int Date::mdays(int year, int mon) const { 
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13; 
		month--; 
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)); 
	}

	Date::Date() {
		year = 0;
		month = 0;
		day = 0;
		status(no_error);
	}

	Date::Date(int y, int m, int d) {
		bool done = false;
		int check = 1;
		while (!done) {
			// Check if the year is valid
			if (check == 1) {
				if (y >= min_year && y <= max_year) {
					year = y;
					status(no_error);
					check = 2;
				}
				else {
					*this = Date();
					status(error_year);
					done = true;
				}
			}
			// Check if the month is valid
			else if (check == 2) {
				if (m >= 1 && m <= 12) {
					month = m;
					status(no_error);
					check = 3;
				}
				else {
					*this = Date();
					status(error_mon);
					done = true;
				}
			}
			// Check if the day is valid
			else if (check == 3) {
				if (d >= 1 && d <= mdays(y, m)) {
					day = d;
					status(no_error);
					check = 0;
				}
				else {
					*this = Date();
					status(error_day);
					done = true;
				}
			}
			else {
				done = true;
			}
		}
	}

	int Date::status() const {
		return d_status;
	}

	void Date::clearError() {
		status(no_error);
	}

	bool Date::isGood() const {
		return ((status() == no_error && year > 0 && month > 0 && day > 0) ? true : false);
	}

	Date& Date::operator+=(int src_days) {
		if (isGood()) {
			if (day + src_days > mdays(year, month) || (day + src_days) < 0) {
				status(error_invalid_operation);
			}
			else {
				day += src_days;
			}
		}
		else {
			status(error_invalid_operation);
		}

		return *this;
	}

	Date& Date::operator++() {
		if (isGood()) {
			if (day + 1 > mdays(year, month)) {
				status(error_invalid_operation);
			}
			else {
				day++;
			}
		}
		else {
			status(error_invalid_operation);
		}
		return *this;
	}

	Date Date::operator++(int) {
		Date d = *this;
		++(*this);
		return d;
	}

	Date Date::operator+(int src_days) const {
		Date d = *this;
		if (isGood()) {
			if (d.day + src_days > d.mdays(year, month) || (d.day + src_days) < 0) {
				d.status(error_invalid_operation);
			}
			else {
				d.day += src_days;
			}
		}
		else {
			d.status(error_invalid_operation);
		}
		return d;
	}

	bool Date::operator==(const Date& rhs) const {
		return (this->year == rhs.year && this->month == rhs.month && this->day == rhs.day);
	}

	bool Date::operator!=(const Date& rhs) const {
		return !(*this == rhs);
	}

	bool Date::operator<(const Date& rhs) const {
		if (this->year < rhs.year) {
			return true;
		}
		else if (this->month < rhs.month) {
			return true;
		}
		else if (this->day < rhs.day) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Date::operator>(const Date& rhs) const {
		if (this->year > rhs.year) {
			return true;
		}
		else if (this->month > rhs.month) {
			return true;
		}
		else if (this->day > rhs.day) {
			return true;
		}
		else {
			return false;
		}	
	}

	bool Date::operator<=(const Date& rhs) const {
		return (*this < rhs || *this == rhs);
	}

	bool Date::operator>=(const Date& rhs) const {
		return (*this > rhs || *this == rhs);
	}

	istream& Date::read(istream& is) {

		// YYYY?MM?DD
		clearError();
		char character;
		is >> year >> character >> month >> character >> day;

		if (is.fail()) {
			*this = Date();
			is.setstate(ios::failbit);
			status(error_input);
		}
		else if (min_year > year || max_year < year) {
			*this = Date();
			is.setstate(ios::failbit);
			status(error_year);
		}
		else if (1 > month || 12 < month) {
			*this = Date();
			is.setstate(ios::failbit);
			status(error_mon);
		}
		else if (1 > day || mdays(year, month) < day) {
			*this = Date();
			is.setstate(ios::failbit);
			status(error_day);
		}

		return is;
	}
	ostream& Date::write(ostream& os) const {

		// YYYY/MM/DD
		os.width(4);
		os.fill('0');
		os << year;
		os << "/";
		os.setf(ios::right);
		os.width(2);
		os << month;
		os << "/";
		os.width(2);
		os << day;
		os.fill(' ');
		return os;
	}
	
	istream& operator>>(istream& is, Date& d) {
		d.read(is);
		return is;
	}

	ostream& operator<<(ostream& os, const Date& d) {
		d.write(os);
		return os;
	}
}


