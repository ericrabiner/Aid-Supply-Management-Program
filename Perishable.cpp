/*
Name: Eric Rabiner
Student number: 038806063
Email: erabiner@myseneca.ca
Assignment: MS5
Section: J
Date: March 23, 2019
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Perishable.h"

using namespace std;
namespace ama {

	Perishable::Perishable() : Product::Product('P') {}

	ostream& Perishable::write(ostream& out, int writeMode) const {
		Product::write(out, writeMode);
		if (isClear() && !isEmpty()) {
			if (writeMode == write_human) {
				out.width(max_length_label);
				out.setf(ios::right);
				out << endl << "Expiry Date: " << _date;
			}
			else if (writeMode == write_table) {
				out << " " << _date << " |";
			}
			else if (writeMode == write_condensed) {
				out << "," << _date;
			}
		}
		return out;
	}

	istream& Perishable::read(istream& in, bool interractive) {
		Product::read(in, interractive);
		if (interractive) {
			if (!in.fail()) {
				in.clear();
				cout.width(max_length_label);
				cout.setf(ios::right);
				cout << "Expiry date (YYYY/MM/DD): ";
				Date temp_date;
				in >> temp_date;
				if (!temp_date.isGood()) {
					in.setstate(ios::failbit);
					if (temp_date.status() == error_input) {
						message("Invalid Date Entry");
					}
					else if (temp_date.status() == error_year) {
						message("Invalid Year in Date Entry");
					}
					else if (temp_date.status() == error_mon) {
						message("Invalid Month in Date Entry");
					}
					else if (temp_date.status() == error_day) {
						message("Invalid Day in Date Entry");
					}
				}
				if (!in.fail()) {
					_date = temp_date;
				}
			}
			in.clear();
		}
		else if (!interractive) {
			char comma;
			in >> comma >> _date;
			in.ignore();
		}
		return in;
	}

	/*
	Perishable& Perishable::operator=(const Perishable& src) {
		_date = src._date;
		return *this;
	}
	*/
}