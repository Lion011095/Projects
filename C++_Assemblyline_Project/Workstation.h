// Name:				Lion Yakubov
// Seneca Student ID:   129517207
// Seneca email:		lyakubov@myseneca.ca
// Date of completion:  10/04/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <string>
#include <deque>

#include "CustomerOrder.h"
#include "Station.h"

namespace sdds
{
	extern std::deque<CustomerOrder> g_pending;		// holds the orders to be placed onto the assembly line at the first station.
	extern std::deque<CustomerOrder> g_completed;	// holds the orders that have been removed from the last station and have been completely filled.
	extern std::deque<CustomerOrder> g_incomplete;	// holds the orders that have been removed from the last station and could not be filled completely.
	

	class Workstation : public Station
	{
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation = nullptr;
	public:
		Workstation() = default;
		Workstation(const std::string& str) : Station(str) {};
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
		~Workstation() = default;
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;
	};
}

#endif // !SDDS_WORKSTATION_H