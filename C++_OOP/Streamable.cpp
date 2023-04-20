/***********************************************************************
// OOP244:		Streamable Module
// File:		Streamable.cpp
// Version:		1.0
// Date:		17/11/2021
// Author:		Lion Yakubov
// Description: Final Project Milestone 3
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
// Lion Yakubov	   17/11/2021	   Development
/////////////////////////////////////////////////////////////////
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
***********************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "Streamable.h"

using namespace std;

namespace sdds
{
	ostream& operator<<(ostream& os, const Streamable& CO)
	{
		if (CO)
		{
			CO.write(os);
		}
		return os;
	}

	istream& operator>>(istream& in, Streamable& CO)
	{
		CO.read(in);
		return in;
	}
}