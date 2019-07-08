/*
Name: Eric Rabiner
Student number: 038806063
Email: erabiner@myseneca.ca
Assignment: MS4
Section: J
Date: March 22, 2019
*/

#ifndef sict_ErrorState_H
#define sict_ErrorState_H
#include <iostream>

using namespace std;
namespace ama {

	class ErrorState {
		char* msg;
		
	public:
		explicit ErrorState(const char* errorMessages = nullptr);
		~ErrorState();
		ErrorState(const ErrorState& other) = delete;
		ErrorState& operator=(const ErrorState& other) = delete;
		operator bool() const;
		ErrorState& operator=(const char*);
		void message(const char*);
		const char* message() const;
	};
	ostream& operator<<(ostream&, const ErrorState&);
}

#endif