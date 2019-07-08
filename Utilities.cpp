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
#include "Utilities.h"

using namespace std;
namespace ama {

	double& operator+=(double& total, const iProduct& prod) {
		return total += prod.total_cost();
	}
	ostream& operator<<(ostream& out, const iProduct& prod) {
		prod.write(out, write_human);
		return out;
	}
	istream& operator>>(istream& in, iProduct& prod) {
		prod.read(in, true);
		return in;
	}

	iProduct* createInstance(char tag) {
		if (tag == 'n' || tag == 'N') {
			iProduct* newProduct = new Product();
			return newProduct;
		}
		else if (tag == 'p' || tag == 'P') {
			iProduct* newProduct = new Perishable();
			return newProduct;
		}
		return NULL;
	}
}