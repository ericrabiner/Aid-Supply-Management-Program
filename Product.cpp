/*
Name: Eric Rabiner
Student number: 038806063
Email: erabiner@myseneca.ca
Assignment: MS4
Section: J
Date: March 22, 2019
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "Product.h"
#include "ErrorState.h"

using namespace std;
namespace ama {
	void Product::message(const char* pText) {
		_state.message(pText);
	}

	bool Product::isClear() const {
		return (_state ? false : true);
	}

	void Product::getName(const char* name) {
		if (name != nullptr) {
			_name = new char[strlen(name) + 1];
			int namelen = strlen(name) + 1;
			for (int i = 0; i < (signed)namelen; i++) {
				_name[i] = name[i];
			}
		}
		else {
			_name = nullptr;
		}
	}

	const char* Product::getErrorMessage() const {
		return _state.message();
	}

	const char* Product::name() const {
		return _name;
	}

	void Product::getShallowConstr(const char* sku, const char* unit, double price, int needed, int onhand, bool taxable) {
		strcpy(_sku, sku);
		strcpy(_unit, unit);
		_price = price;
		_needed = needed;
		_onhand = onhand;
		_taxable = taxable;
	}

	Product::Product(char type) : _type(type) {
		getShallowConstr("\0", "\0", 0, 0, 0, false);
		getName(nullptr);
	}
	
	Product::Product(const char* sku, const char* name, const char* unit, double price, int needed, int onhand, bool taxable) : Product('N') {
		getName(name);
		getShallowConstr(sku, unit, price, needed, onhand, taxable);
	}

	Product::Product(const Product& src) : Product('N') {
		getName(nullptr);
		*this = src;
	}

	Product::~Product() {
		if (_name != nullptr) {
			delete[] _name;
			_name = nullptr;
		}
	}

	Product& Product::operator=(const Product& src) {
		if (this != &src) {
			delete[] _name;
			getShallowConstr(src._sku, src._unit, src._price, src._needed, src._onhand, src._taxable);
			getName(src._name);
		}
		return *this;
	}

	int Product::operator+=(int cnt) {
		if (cnt > 0) {
			_onhand += cnt;
		}
		return _onhand;
	}

	bool Product::operator==(const char* sku) const {
		return (strcmp(_sku, sku) == 0);
	}

	bool Product::operator>(const char* sku) const {
		return (strcmp(_sku, sku) > 0);
	}

	bool Product::operator>(const iProduct& src) const {
		return (strcmp(_name, src.name()) > 0);
	}

	int Product::qtyAvailable() const {
		return _onhand;
	}

	int Product::qtyNeeded() const {
		return _needed;
	}

	double Product::total_cost() const {
		if (_taxable) {
			return _onhand * ((_price * tax_rate) + _price);
		}
		else {
			return _onhand * _price;
		}
	}

	bool Product::isEmpty() const {
		return (strcmp(_sku, "\0") == 0 && _name == nullptr && strcmp(_unit, "\0") == 0 && _price == 0 && _needed == 0 && _onhand == 0 && _taxable == false);
	}

	istream& Product::read(istream& in, bool interractive) {
		
		if (!interractive) {
			char comma;
			char temp_name[max_length_name];
			in.getline(_sku, max_length_sku, ',');

			in.getline(temp_name, max_length_name, ',');
			const char* temp_name_other = temp_name;
			getName(temp_name_other);

			in.getline(_unit, max_length_unit, ',');
			in >> _price >> comma >> _taxable >> comma >> _onhand >> comma >> _needed;
		}
		
		else if (interractive) {
			char temp_sku[max_length_sku + 1], temp_name[max_length_name + 1], temp_unit[max_length_unit + 1], ctemp_taxable;
			int temp_onhand, temp_needed;
			double temp_price;
			bool temp_taxable;
		
			cout.setf(ios::right);
			cout.width(max_length_label);
			cout << "Sku: ";
			in.getline(temp_sku, max_length_sku, '\n');
			if (in.fail()) {
				in.setstate(ios::failbit);
			}
			
			if (!in.fail()) {
				cout.width(max_length_label);
				cout << "Name (no spaces): ";
				in.getline(temp_name, max_length_name, '\n');
				if (in.fail()) {
					in.setstate(ios::failbit);
				}
			}

			if (!in.fail()) {
				cout.width(max_length_label);
				cout << "Unit: ";
				in.getline(temp_unit, max_length_unit, '\n');
				if (in.fail()) {
					in.setstate(ios::failbit);
				}
			}

			if (!in.fail()) {
				cout.width(max_length_label);
				cout << "Taxed? (y/n): ";
				in >> ctemp_taxable;

				if (ctemp_taxable == 'y' || ctemp_taxable == 'Y') {
					temp_taxable = true;
				}
				else if (ctemp_taxable == 'n' || ctemp_taxable == 'N') {
					temp_taxable = false;
				}
				else {
					in.setstate(ios::failbit);
					_state.message("Only (Y)es or (N)o are acceptable!");
				}
			}

			if (!in.fail()) {
				cout.width(max_length_label);
				cout << "Price: ";
				in >> temp_price;
				if (in.fail()) {
					in.setstate(ios::failbit);
					_state.message("Invalid Price Entry!");
				}
			}

			if (!in.fail()) {
				cout.width(max_length_label);
				cout << "Quantity on hand: ";
				in >> temp_onhand;
				if (in.fail()) {
					in.setstate(ios::failbit);
					_state.message("Invalid Quantity Available Entry!");
				}
			}

			if (!in.fail()) {
				cout.width(max_length_label);
				cout << "Quantity needed: ";
				in >> temp_needed;
				if (in.fail()) {
					in.setstate(ios::failbit);
					_state.message("Invalid Quantity Needed Entry!");
				}
			}
			
			if (!in.fail()) {
				Product temp = Product(temp_sku, temp_name, temp_unit, temp_price, temp_needed, temp_onhand, temp_taxable);
				*this = temp;
			}
		}
		return in;
	}

	ostream& Product::write(ostream& out, int writeMode) const {
		if (_state) {
			out << _state.message();
		}
		
		if (!isEmpty()) {
			if (writeMode == write_condensed) {
				out << _type << "," << _sku << "," << _name << "," << _unit << "," << _price << "," << _taxable << "," << _onhand << "," << _needed;
			}

			else if (writeMode == write_table) {
				out << " ";
				out.width(max_length_sku);
				out.setf(ios::right);
				out << _sku << " | ";
				out.unsetf(ios::right);
				out.setf(ios::left);
				if (strlen(_name) > 16) {
					char* temp_name = new char[17];
					for (int i = 0; i < 13; i++) {
						temp_name[i] = _name[i];
					}
					for (int i = 13; i < 16; i++) {
						temp_name[i] = '.';
					}
					temp_name[16] = '\0';
					out << temp_name << " | ";
					delete[] temp_name;
				}
				else {
					out.width(16);
					out << _name << " | ";
				}
			
				out.width(10);
				out << _unit << " | ";
				out.width(7);
				out.unsetf(ios::left);
				out.setf(ios::fixed);
				out.precision(2);
				out << _price << " | ";
				if (_taxable) {
					out << "yes | ";
				}
				else {
					out << " no | ";
				}
				out.width(6);
				out << _onhand << " " << "| ";
				out.width(6);
				out << _needed << " " << "|";
			}
			else if (writeMode == write_human){
				out.width(max_length_label);
				out.setf(ios::right);
				out << "Sku: " << _sku << endl;
				out.width(max_length_label);
				out << "Name: " << _name << endl;
				out.width(max_length_label);
				out << "Price: ";
				out.setf(ios::fixed);
				out.precision(2);
				out << _price << endl;
				out.width(max_length_label);
				out << "Price after Tax: ";
				out.precision(2);
				if (_taxable) {
					out << (_price * tax_rate) + _price << endl;
				}
				else {
					out << _price << endl;
				}
				out.width(max_length_label);
				out.setf(ios::right);
				out << "Quantity Available: " << _onhand << " " << _unit << endl;
				out.width(max_length_label);
				out.setf(ios::right);
				out << "Quantity Needed: " << _needed << " " << _unit;
			}
		}
		return out;
	}
}