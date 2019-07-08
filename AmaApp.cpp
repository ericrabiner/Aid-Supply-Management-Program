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
#include <fstream>
#include <cstring>
#include <string>
#include "AmaApp.h"

using namespace std;
namespace ama {

	
	AmaApp::AmaApp(const char* file) {
		// copy filename to m_filename
		strcpy(m_filename, file);

		// set all m_product elements to null
		if (m_noOfProducts > 0) {
			for (int i = 0; i < m_noOfProducts; i++) {
				m_products[i] = NULL;
			}
		}

		// set m_noOfProducts to zero
		m_noOfProducts = 0;
		// load the records from the file
		loadProductRecords();
	}

	AmaApp::~AmaApp() {
		for (int i = 0; i < m_noOfProducts; i++) {
			m_products[i] = NULL;
		}
	}

	void AmaApp::pause() const {
		cout << "Press Enter to continue...";
		while (getchar() != '\n');
		cout << endl;
	}

	int AmaApp::menu() const {
		int option;
		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "--------------------------------------" << endl;
		cout << "1- List products" << endl;
		cout << "2- Search product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to product quantity" << endl;
		cout << "6- Delete product" << endl;
		cout << "7- Sort products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";
		cin >> option;
		
		if (!(option >= 0 && option <= 7) || cin.fail()) {
			option = -1;
			if (cin.fail()) {
				while (getchar() != '\n');
			}
		}
		while (getchar() != '\n');
		cin.clear();
		return option;
	}

	void AmaApp::loadProductRecords() {
		// Delete all products from the array (if any)
		if (m_products != NULL) {
			for (int i = 0; i < m_noOfProducts; i++) {
				m_products[i] = NULL;
			}
		}
		// Set reading index to zero
		int i = 0;
		//Open the file for reading(use ios::in)
		ifstream in;
	
		in.open(m_filename);
		//if the file is open, then
		if (in.is_open()) {
			//until reading fails loop
			while (!in.eof()) {
				//read one char character to identify type of Product (the tag)
				char type;
				in.get(type);
				//call the ama::createInstance(tag) to create an instance
				iProduct* product = createInstance(type);
				//if createInstance(tag) returns not null
				if (product != NULL) {
					//store the product in the array at the read index
					m_products[i] = product;
					//skip the comma from the file
					char comma;
					in.get(comma);
					//read the product from the file (non-interractive mode)
					m_products[i]->read(in, false);
					
					//increment the read index
					i++;
				}
			}
			//continue the loop
		}
		//set number of products to readIndex
		m_noOfProducts = i;
		//close the datafile
		in.close();
	}

	void AmaApp::saveProductRecords() const {
		ofstream file;
		file.open(m_filename);
		if (file.is_open()) {
			for (int i = 0; i < m_noOfProducts; i++) {
				m_products[i]->write(file, write_condensed);
				if (i != m_noOfProducts - 1) {
					file << endl;
				}
			}
		}
		file.close();
	}

	void AmaApp::listProducts() const {
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |" << endl;
		cout << "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << endl;

		double total = 0;
		for (int i = 0; i < m_noOfProducts; i++) {
			cout << "|";
			cout.width(4);
			cout << i + 1 << " ";
			
			cout.setf(ios::right);
			cout << "|";
			m_products[i]->write(cout, write_table);
			
			cout << endl;
			total += *m_products[i];
		}

		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                      Total cost of support ($): | ";
		cout.width(10);
		cout.setf(ios::right);
		cout.precision(2);
		cout << total << " |" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl << endl;
	}

	iProduct* AmaApp::find(const char* sku) const {
		for (int i = 0; i < m_noOfProducts; i++) {
			if (*m_products[i] == sku) {
				return m_products[i];
			}
		}
		return NULL;
	}

	void AmaApp::addQty(iProduct* product) {
		cout << endl;
		product->write(cout, write_human);
		cout << endl << endl << endl << "Please enter the number of purchased items: ";
		int input_qty;
		cin >> input_qty;
		if (cin.fail()) {
			cout << "Invalid quantity value!" << endl << endl;
		}
		else if (input_qty <= (product->qtyNeeded() - product->qtyAvailable())) {
			*product += input_qty;
			cout << endl << "Updated!" << endl << endl;
			saveProductRecords();
		}
		else {
			int qty_needed = product->qtyNeeded() - product->qtyAvailable();
			int qty_extra = input_qty - qty_needed;
			cout << "Too many items; only " << qty_needed << " is needed. Please return the extra " << qty_extra << " items." << endl;
			cout << endl << "Updated!" << endl << endl;
			*product += qty_needed;
			saveProductRecords();
		}
		cin.clear();
		cin.ignore();
	}

	void AmaApp::addProduct(char tag) {
		iProduct* product = createInstance(tag);	
		if (product != NULL) {
			product->read(cin, write_human);
			if (!product->isClear()) {
				cout << endl << product->getErrorMessage() << endl << endl;
				cin.clear();
				while (getchar() != '\n');
			}
			else {
				m_products[m_noOfProducts] = product;
				m_noOfProducts++;
				saveProductRecords();
				cout << endl << "Success!" << endl << endl;
			}
		}
	}
	
	void AmaApp::deleteProductRecord(iProduct* product) {
		ofstream file;
		file.open(m_filename);
		if (file.is_open()) {
			for (int i = 0; i < m_noOfProducts; i++) {
				if (!(product == m_products[i])) {
					m_products[i]->write(file, write_condensed);
					if (i != m_noOfProducts - 1) {
						file << endl;
					}
				}
			}
		}
		file.close();
	}
	
	void AmaApp::sort() {
		sict::sort(m_products, m_noOfProducts);
		saveProductRecords();
	}

	int AmaApp::run() {
		
		int option;
		char sku[max_length_sku + 1];

		do {
			option = menu();
			switch (option) {
				iProduct* temp;
			case 1:
				listProducts();
				pause();
				break;

			case 2:
				cout << "Please enter the product SKU: ";
				cin >> sku;
				cin.ignore();
				temp = find(sku);
				if (temp == NULL) {
					cout << endl << "No such product!" << endl;	
				}
				else {
					cout << endl;
					temp->write(cout, write_human) << endl << endl;
				}
				pause();
				break;

			case 3:
				addProduct('N');
				loadProductRecords();
				break;

			case 4:
				addProduct('P');
				loadProductRecords();
				break;

			case 5:
				cout << "Please enter the product SKU: ";
				cin >> sku;
				temp = find(sku);
				if (temp == NULL) {
					cout << endl << "No such product!" << endl << endl;
				}
				else {
					addQty(temp);
				}
				break;

			case 6:
				
				cout << "Please enter the product SKU: ";
				cin >> sku;
				temp = find(sku);
				if (temp == NULL) {
					cout << endl << "No such product!" << endl;
				}
				else {
					deleteProductRecord(temp);
					loadProductRecords();
					cout << endl << "Deleted!" << endl;
				}
				break;

			case 7:
				sort();
				loadProductRecords();
				cout << "Sorted!" << endl << endl;
				break;

			case 0:
				cout << "Goodbye!" << endl;
				break;
				
			default:
				cout << "~~~Invalid selection, try again!~~~" << endl;
				pause();
				break;
			}
		} while (option != 0);
		
		return 0;
	}
}

