/*
Name: Eric Rabiner
Student number: 038806063
Email: erabiner@myseneca.ca
Assignment: MS5
Section: J
Date: March 30, 2019
*/

#ifndef sict_Sort_H
#define sict_Sort_H

using namespace std;
namespace sict {

	// Bubble Sort
	template <typename T>
	void sort(T** products, int n) {

		int i, j;
		T* temp;

		for (i = n - 1; i > 0; i--) {
			for (j = 0; j < i; j++) {
				if (*products[j] > *products[j + 1]) {
					temp = products[j];
					products[j] = products[j + 1];
					products[j + 1] = temp;
				}
			}
		}
	}
}
#endif