/*
Name: Eric Rabiner
Student number: 038806063
Email: erabiner@myseneca.ca
Assignment: MS4
Section: J
Date: March 22, 2019
*/

#ifndef sict_Product_H
#define sict_Product_H
#include <iostream>
#include "iProduct.h"
#include "ErrorState.h"

using namespace std;
namespace ama {

	class Product : public iProduct {
		const char _type;
		char _sku[max_length_sku + 1];
		char _unit[max_length_unit + 1];
		char* _name;
		int _onhand;
		int _needed;
		double _price;
		bool _taxable;
		ErrorState _state;
		void getName(const char*);
		void getShallowConstr(const char*, const char*, double, int, int, bool);
		const char* name() const;
	protected:
		void message(const char*);
		bool isClear() const;
		const char* getErrorMessage() const;
	public:
		Product(char type = 'N');
		Product(const char*, const char*, const char*, double price = 0, int needed = 0, int onhand = 0, bool taxable = false);
		Product(const Product&);
		~Product();
		Product& operator=(const Product&);
		int operator+=(int);
		bool operator==(const char*) const;
		bool operator>(const char*) const;
		bool operator>(const iProduct&) const;
		int qtyAvailable() const;
		int qtyNeeded() const;
		double total_cost() const;
		bool isEmpty() const;
		istream& read(istream&, bool);
		ostream& write(ostream&, int) const;
	};
}

#endif