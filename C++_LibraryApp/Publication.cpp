/***********************************************************************
// OOP244:		Publication Module
// File:		Publication.cpp
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
#include <cstring>
#include <iomanip>
#include <string>

#include "Publication.h"
#include "Streamable.h"
#include "Lib.h"

using namespace std;

namespace sdds
{
	Publication::Publication()
	{
		m_title = nullptr;
		resetDate();
		m_shelfId[0] = '\0';
		m_membership = 0;
		setRef(-1);
	}

	Publication::~Publication()
	{
		delete[] m_title;
		m_title = nullptr;
	}

	Publication& Publication::operator=(const Publication& source)
	{
		int n;
		if (this != &source)
		{
			if (source.m_title != nullptr)
			{
				n = strlen(source.m_title) + 1;
				delete[] m_title;
				m_title = nullptr;	
				m_title = new char[n];
				strcpy(m_title, source.m_title);
			}

			strcpy(m_shelfId, source.m_shelfId);
			m_membership = source.m_membership;
			m_libRef = source.m_libRef;
			m_date = source.m_date;
		}
		return *this;
	}

	Publication::Publication(const Publication& source)
	{
		int n;
		
		if (source.m_title != nullptr)
		{
			n = strlen(source.m_title) + 1;
			m_title = nullptr;
			m_title = new char[n];
			strcpy(m_title, source.m_title);
		}
		else
		{
			m_title = nullptr;
		}
		strcpy(m_shelfId, source.m_shelfId);
		m_membership = source.m_membership;
		m_libRef = source.m_libRef;
		m_date = source.m_date;
	}

	bool Publication::isEmpty() const
	{
		bool empty = false;
		if (m_title == nullptr || m_shelfId == nullptr || strlen(m_title) == 0 || strlen(m_shelfId) == 0)
		{
			empty = true;
		}
		return empty;
	}

	void Publication::setEmpty()
	{
		if (m_title != nullptr)
		{
			delete[] m_title;	
		}
		m_title = nullptr;
		resetDate();
		m_shelfId[0] = '\0';
		m_membership = 0;
		setRef(-1);
	}

	void Publication::set(int member_id)
	{
		if (member_id > 0)
		{
			m_membership = member_id;
		}
		else
		{
			m_membership = 0;
		}
	}

	void Publication::setRef(int value)
	{
		m_libRef = value;
	}

	void Publication::resetDate()
	{
		m_date.setToToday();
	}

	char Publication::type() const
	{
		return 'P';
	}

	bool Publication::onLoan() const
	{
		bool loaned = false;

		if (m_membership > 0)
		{
			loaned = true;
		}
		return loaned;
	}

	Date Publication::checkoutDate() const
	{
		return m_date;
	}

	bool Publication::operator==(const char* title) const
	{
		char* sTitle;
		bool found = false;

		sTitle = strstr(m_title, title);
		if (sTitle != nullptr)
		{
			found = true;
		}
		return found;
	}

	Publication::operator const char* () const
	{
		return m_title;
	}

	int Publication::getRef() const
	{
		return m_libRef;
	}

	bool Publication::conIO(ios& io) const
	{
		bool consoleUse = false;

		if (&io == &cout || &io == &cin)
		{
			consoleUse = true;
		}

		return consoleUse;
	}

	ostream& Publication::write(ostream& os) const
	{
		int i;

		if (!isEmpty())
		{
			if (conIO(os))
			{
				os << "| " << m_shelfId << " | ";
				os.setf(ios::left);
				if (strlen(m_title) < SDDS_TITLE_WIDTH)
				{
					os << setw(SDDS_TITLE_WIDTH) << setfill('.') << m_title << setfill(' ') << " | ";
				}
				else
				{
					for (i = 0; i < SDDS_TITLE_WIDTH; i++)
					{
						os << m_title[i];
					}
					os << " | ";
				}

				if (m_membership > 0)
				{
					os << m_membership;
				}
				else
				{
					os << " N/A ";
				}
				os << " | " << m_date << " |";
				if (type() == 'P')
				{
					os << endl;
				}
			}
			else
			{
				os << type() << '\t' << m_libRef << '\t' << m_shelfId << '\t' << m_title << '\t' << m_membership << '\t' << m_date;
				if (type() == 'P')
				{
					os << endl;
				}
			}
		}
		return os;
	}

	istream& Publication::read(istream& istr)
	{
		string str;
		string shelfNum;
		long int memberNum = 0;
		int libRef = 0;
		Date date;

		setEmpty();
		if (conIO(istr))
		{
			cout << "Shelf No: ";
			istr >> shelfNum;
			if (shelfNum.length() != SDDS_SHELF_ID_LEN)
			{
				istr.setstate(ios_base::failbit);
			}
			cout << "Title: ";
			cin.ignore(2000, '\n');
			getline(istr, str, '\n');
			cout << "Date: ";
			istr >> date;
			if (!date.validate())
			{
				istr.setstate(ios_base::failbit);
			}
		}
		else
		{
			istr >> libRef;
			istr.ignore();
			istr >> shelfNum;
			istr.ignore();
			getline(istr, str, '\t');
			istr >> memberNum;
			istr.ignore();
			istr >> date;
			if (!date.validate())
			{
				istr.setstate(ios_base::failbit);
			}
		}

		if (istr.good())
		{
			strcpy(m_shelfId, shelfNum.c_str());
			m_title = new char[str.length() + 1];
			strcpy(m_title, str.c_str());
			m_membership = memberNum;
			m_libRef = libRef;
			m_date.m_year = date.m_year;
			m_date.m_mon = date.m_mon;
			m_date.m_day = date.m_day;
			m_date.m_ErrorCode = date.m_ErrorCode;
			m_date.m_CUR_YEAR = date.m_CUR_YEAR;
		}
		return istr;
	}

	Publication::operator bool() const
	{
		return !isEmpty();
	}
}