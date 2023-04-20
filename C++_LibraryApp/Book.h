/***********************************************************************
// OOP244:		Book Module
// File:		Book.h
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

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>

#include "Publication.h"


namespace sdds
{
	class Book : public Publication
	{
		char* m_authorName = nullptr;

	public:
		Book();
		~Book();
		Book(const Book& right);
		Book& operator=(const Book& right);
		char type() const;
		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& istr);
		void set(int member_id);
		operator bool() const;
	};
}

#endif // !SDDS_BOOK_H
