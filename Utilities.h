/*
Name: Eric Rabiner
Student number: 038806063
Email: erabiner@myseneca.ca
Assignment: MS4
Section: J
Date: March 22, 2019
*/

#ifndef sict_Utilities_H
#define sict_Utilities_H
#include <iostream>
#include "Product.h"
#include "Perishable.h"

using namespace std;
namespace ama {
	double& operator+=(double&, const iProduct&);
	ostream& operator<<(ostream&, const iProduct&);
	istream& operator>>(istream&, iProduct&);
	iProduct* createInstance(char);
}

#endif