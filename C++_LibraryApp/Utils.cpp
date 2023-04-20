/***********************************************************************
// OOP244:		Utils Module
// File:		Utils.cpp
// Version:		1.0
// Date:		03/11/2021
// Author:		Lion Yakubov
// Description: Final Project Milestone 1
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
// Lion Yakubov	   03/11/2021	   Development
/////////////////////////////////////////////////////////////////
***********************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "Utils.h"

using namespace std;

namespace sdds 
{
	unsigned int checkSelection(unsigned int numOfItems)
	{
		unsigned int selection = 0;

		cin >> selection;
		while (selection > numOfItems || selection < 0 || cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Selection, try again: ";
			cin >> selection;
		}

		return selection;
	}
}