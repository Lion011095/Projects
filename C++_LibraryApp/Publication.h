/***********************************************************************
// OOP244:		Publication Module
// File:		Publication.h
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
#ifndef SDDS_PUBLICATION_H
#define SDDS_PUBLICATION_H

#include <iostream>

#include "Date.h"
#include "Streamable.h"

namespace sdds
{
	class Publication : public Streamable
	{
		friend class Date;

		char* m_title;
		char m_shelfId[5];
		long int m_membership;
		int m_libRef;
		Date m_date;

	public:
		Publication();
		~Publication();
		Publication& operator=(const Publication& right);
		Publication(const Publication& right);
		void setEmpty();								// sets the cuttent object to a safe empty state.
		bool isEmpty() const;							// checks if the current object is empty.
		virtual void set(int member_id);				// sets the member_id to a 5 digit number or a 0.
		void setRef(int value);							// sets the libRef to the incomming value.
		void resetDate();								// resets the date to the current date.
		virtual char type() const;						// sets the type of the Publication.
		bool onLoan() const;							// checks if the publication is loaned or available.
		Date checkoutDate() const;						// returns the date of the object.
		bool operator==(const char* title) const;		// sreachs for a substring in a title.
		operator const char* () const;					// returns the title of the object.
		int getRef() const;								// returns the libRaf of the object.
		bool conIO(std::ios& io) const;					// checking if streaming from/to a file or the keyboard/screen.
		std::ostream& write(std::ostream& os) const;    // writes the output to the screen or a file.
		std::istream& read(std::istream& istr);			// read the input from a keyboard or a file.
		operator bool() const;
	};
}
#endif // !SDDS_PUBLICATION_H

