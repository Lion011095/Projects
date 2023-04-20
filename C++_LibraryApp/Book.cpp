/***********************************************************************
// OOP244:		Book Module
// File:		Book.cpp
// Version:		1.0
// Date:		26/11/2021
// Author:		Lion Yakubov
// Description: Final Project Milestone 4
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
// Lion Yakubov	   26/11/2021	   Development
/////////////////////////////////////////////////////////////////
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
***********************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

#include "Book.h"
#include "Lib.h"

using namespace std;

namespace sdds
{
	Book::Book() : Publication() {};

	Book::~Book()
	{
		delete[] m_authorName;
		m_authorName = nullptr;
	}

	Book& Book::operator=(const Book& right)
	{
		int n;
		if (this != &right)
		{
			if (right.m_authorName != nullptr)
			{
				Publication::operator=(right);
				n = strlen(right.m_authorName) + 1;
				delete[] m_authorName;
				m_authorName = nullptr;
				m_authorName = new char[n];
				strcpy(m_authorName, right.m_authorName);
			}
		}
		return *this;
	}

	Book::Book(const Book& right) : Publication(right)
	{
		operator=(right);
	}

	char Book::type() const
	{
		return 'B';
	}

	ostream& Book::write(ostream& os) const
	{
		int i;

		Publication::write(os);
		if (conIO(os))
		{
			os << " ";
			if (strlen(m_authorName) < SDDS_AUTHOR_WIDTH)
			{
				os << setw(SDDS_AUTHOR_WIDTH) << m_authorName;
			}
			else
			{
				for (i = 0; i < SDDS_AUTHOR_WIDTH; i++)
				{
					os << m_authorName[i];
				}
			}
			os << " |" << endl;
		}
		else
		{
			os << '\t' << m_authorName << endl;
		}
		return os;
	}

	istream& Book::read(istream& istr)
	{
		char temp[SDDS_MAX_AUTHOR_NAME] = { '\0' };

		Publication::read(istr);
		delete[] m_authorName;
		m_authorName = nullptr;
		if (conIO(istr))
		{
			istr.ignore();
			cout << "Author: ";
			istr.get(temp, SDDS_MAX_AUTHOR_NAME, '\n');
		}
		else
		{
			istr.ignore();
			istr.get(temp, SDDS_MAX_AUTHOR_NAME, '\n');
		}

		if (!istr.fail())
		{
			m_authorName = new char[strlen(temp) + 1];
			strcpy(m_authorName, temp);
		}

		return istr;
	}

	void Book::set(int member_id)
	{
		Publication::set(member_id);
		resetDate();
	}

	Book::operator bool() const
	{
		return m_authorName && m_authorName[0] && Publication::operator bool();
	}
}
