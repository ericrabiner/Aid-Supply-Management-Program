/*
Name: Eric Rabiner
Student number: 038806063
Email: erabiner@myseneca.ca
Assignment: MS5
Section: J
Date: March 23, 2019
*/

#ifndef sict_Perishable_H
#define sict_Perishable_H
#include <iostream>
#include "Product.h"
#include "Date.h"

using namespace std;
namespace ama {

	class Perishable : public Product {
		Date _date;
	public:
		Perishable();
		virtual ~Perishable() = default;
		ostream& write(ostream&, int) const override;
		istream& read(istream&, bool) override; 

		//Perishable& operator=(const Perishable&);
	};
}

#endif