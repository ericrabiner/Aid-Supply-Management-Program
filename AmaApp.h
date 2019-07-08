/*
Name: Eric Rabiner
Student number: 038806063
Email: erabiner@myseneca.ca
Assignment: MS5
Section: J
Date: March 23, 2019
*/

#ifndef sict_AmaApp_H
#define sict_AmaApp_H
#include <iostream>
#include "iProduct.h"
#include "Utilities.h"
#include "Sort.h"

using namespace std;
namespace ama {
	
	class AmaApp {
		char m_filename[256];
		iProduct* m_products[100];
		int m_noOfProducts;

		AmaApp(const AmaApp&) = delete;
		AmaApp& operator=(const AmaApp&) = delete;
		void pause() const;
		int menu() const;
		void loadProductRecords();
		void saveProductRecords() const;
		void listProducts() const;
		//Optional
		
		void deleteProductRecord(iProduct* product);
		void sort();
		// 
		iProduct* find(const char*) const;
		void addQty(iProduct*);
		void addProduct(char);

	public:
		AmaApp(const char*);
		~AmaApp();
		int run();
	};
}

#endif
