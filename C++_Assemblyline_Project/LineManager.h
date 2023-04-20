// Name:				Lion Yakubov
// Seneca Student ID:   129517207
// Seneca email:		lyakubov@myseneca.ca
// Date of completion:  10/04/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <string>
#include <vector>

#include "Workstation.h"

namespace sdds
{
	class LineManager
	{
		std::vector<Workstation*> m_activeLine{};	// the collection of workstations for the current assembly line.
		std::size_t m_cntCustomerOrder = 0;			// the total number of CustomerOrder objects
		Workstation* m_firstStation = nullptr;		// points to the first active station on the current line
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif // !SDDS_LINEMANAGER_H
