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
#include "ErrorState.h"

using namespace std;
namespace ama {
	
	ErrorState::ErrorState(const char* errorMessage) {
		message(errorMessage);
	}

	ErrorState::~ErrorState() {
		if (msg != nullptr) {
			delete[] msg;
			msg = nullptr;
		}
	}

	ErrorState::operator bool() const {
		return (message() != nullptr ? true : false);
	}

	ErrorState& ErrorState::operator=(const char* pText) {
		message(pText);
		return *this;
	}

	void ErrorState::message(const char* pText) {
		if (pText == nullptr || strcmp(pText, "") == 0) {
			msg = nullptr;
		}
		else if (pText != nullptr) {
			int length_msg = strlen(pText);
			msg = new char[length_msg + 1];
			strcpy(msg, pText);
		}
	}

	const char* ErrorState::message() const {
		return msg;
	}

	ostream& operator<<(ostream& os, const ErrorState& es) {
		if (es) {
			os << es.message();
		}
		return os;
	}
}