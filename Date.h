/*
Name: Eric Rabiner
Student number: 038806063
Email: erabiner@myseneca.ca
Assignment: MS1
Section: J
Date: March 4, 2019
*/

#ifndef sict_Date_H
#define sict_Date_H
#include <iostream>

using namespace std;
namespace ama {
	const int min_year = 2019;
	const int max_year = 2028;
	const int no_error = 0;
	const int error_year = 1;
	const int error_mon = 2;
	const int error_day = 3;
	const int error_invalid_operation = 4;
	const int error_input = 5;

	class Date {
		int year;
		int month;
		int day;
		int d_status;
		void status(int newStatus);
		int mdays(int year, int month) const;

	public:
		Date();
		Date(int y, int m, int d);
		int status() const;
		void clearError();
		bool isGood() const;
		Date& operator+=(int src_days);
		Date& operator++();
		Date operator++(int);
		Date operator+(int src_days) const;
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		istream& read(istream&);
		ostream& write(ostream&) const;
	};

	istream& operator>>(istream&, Date&);
	ostream& operator<<(ostream&, const Date&);
}

#endif