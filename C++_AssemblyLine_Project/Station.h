
#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>
#include <string>

namespace sdds
{
	class Station
	{
		size_t m_stationID = 0;
		std::string m_itemName{};			// the name of the item handled by the station
		std::string m_description{};		// the description of the station
		std::size_t m_serialNum = 0;		// the next serial number to be assigned to an item at this station
		std::size_t m_itemsInStock = 0;
		static std::size_t m_widthField;
		static std::size_t id_generator;
	public:
		Station() = default;
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SDDS_STATION_H
