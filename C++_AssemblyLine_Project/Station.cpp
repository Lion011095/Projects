
#include <iostream>
#include <string>
#include <iomanip>

#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;
	 
	Station::Station(const string& str)
	{
		size_t beggining = 0;
		bool isMore = true;
		Utilities itemDetails;

		++id_generator;
		m_stationID = id_generator;
		m_itemName = itemDetails.extractToken(str, beggining, isMore);
		m_serialNum = stoi(itemDetails.extractToken(str, beggining, isMore));
		m_itemsInStock = stoi(itemDetails.extractToken(str, beggining, isMore));
		if (Station::m_widthField < itemDetails.getFieldWidth())
		{
			Station::m_widthField = itemDetails.getFieldWidth();
		}
		m_description = itemDetails.extractToken(str, beggining, isMore);
	}

	const string& Station::getItemName() const
	{
		return m_itemName;
	}

	size_t Station::getNextSerialNumber()
	{
		size_t nextSerial = m_serialNum;
		m_serialNum++;
		return nextSerial;
	}

	size_t Station::getQuantity() const
	{
		return m_itemsInStock;
	}

	void Station::updateQuantity()
	{
		if (m_itemsInStock > 0)
		{
			m_itemsInStock--;
		}
	}

	void Station::display(ostream& os, bool full) const
	{

		os << setw(3) << setfill('0') << m_stationID << " | " << setfill(' ');
		os.setf(ios::left);
		os << setw(Station::m_widthField + 1) << m_itemName << " | ";
		os.unsetf(ios::left);
		os << setw(6) << setfill('0') << m_serialNum << " | " << setfill(' ');

		if(full)
		{
			os << setw(4) << m_itemsInStock << " | ";
			os << m_description;
		}
		os << '\n';
	}
}