/***********************************************************************
// OOP244:		Streamable Module
// File:		Streamable.h
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

#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H

#include <iostream>

namespace sdds
{
	class Streamable 
	{
	public:
		virtual std::ostream& write(std::ostream& os) const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual bool conIO(std::ios& io) const = 0;
		virtual operator bool() const = 0;
		virtual ~Streamable() {};
	};

	std::ostream& operator<<(std::ostream& os, const Streamable& CO);
	std::istream& operator>>(std::istream& in, Streamable& CO);
}



#endif // !SDDS_STREAMABLE_H


