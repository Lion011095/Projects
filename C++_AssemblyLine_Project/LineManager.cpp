
#include <fstream>
#include <algorithm>

#include "LineManager.h"
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		ifstream fin(file);
		string line{};
		string handles{};
		string nextStationItem{};
		

		if (fin.is_open())
		{
			while (!fin.eof())
			{
				getline(fin, line, '\n');
				auto delimPos = line.find('|');
				if (delimPos != string::npos)
				{
					handles = line.substr(0, delimPos);
					nextStationItem = line.substr(delimPos + 1);
				}
				else
				{
					handles = line;
					nextStationItem = "";
				}
				auto station = find_if(stations.begin(), stations.end(), [&](Workstation* station) {return station->getItemName() == handles; });
				m_activeLine.push_back(*station);

				// defining the next station pointer
				if (nextStationItem.length() > 0)
				{
					auto nextStation = find_if(stations.begin(), stations.end(), [&](Workstation* station) {return station->getItemName() == nextStationItem; });
					m_activeLine.back()->setNextStation(*nextStation);
				}
			}


			// setting the pointer to the fisrt station
			auto findFirstStation = [&](Workstation* station) 
			{ 
				string stationItem = station->getItemName();
				auto compareStations = [&](Workstation* currentStation) 
				{ 
					Workstation* next = currentStation->getNextStation();
					if (next != nullptr)
					{
						return stationItem == next->getItemName();
					}
					return false;
				};
				return any_of(m_activeLine.begin(), m_activeLine.end(), compareStations);
			};
			auto firstStation = find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) { return (findFirstStation(station) == false); });
			m_firstStation = *firstStation;
				
			// updating the total number of orders
			m_cntCustomerOrder = g_pending.size();
		}
		else
		{
			throw std::invalid_argument("File cannot be opened.");
		}
		fin.close();
	}

	void LineManager::reorderStations() 
	{
		vector<Workstation*> temp;
		bool pushed = false;
		temp.push_back(m_firstStation);
		for (size_t i = 0; i < temp.size() && temp.size() != m_activeLine.size(); ++i)
		{
			for (size_t j = 0; j < m_activeLine.size() && pushed == false; ++j)
			{
				if (temp[i]->getItemName() == m_activeLine[j]->getItemName())
				{
					temp.push_back(m_activeLine[j]->getNextStation());
					pushed = true;
				}
			}
			pushed = false;
		}
		m_activeLine.clear();
		m_activeLine = temp;
	}

	bool LineManager::run(std::ostream& os)
	{
		bool noOrders = false;
		static int itr = 0;
		if (m_cntCustomerOrder != 0)
		{
			++itr;
			os << "Line Manager Iteration: " << itr << endl;
			if (g_pending.size() != 0)
			{
				*m_firstStation += move(g_pending.front());
				g_pending.pop_front();
			}
			auto executeFill = [&](Workstation* station) { station->fill(os); };
			for_each(m_activeLine.begin(), m_activeLine.end(), executeFill);
			auto moveOrder = [](Workstation* station) { station->attemptToMoveOrder(); };
			for_each(m_activeLine.begin(), m_activeLine.end(), moveOrder);
			if (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder)
			{
				m_cntCustomerOrder = 0;
			}
		}
		else
		{
			noOrders = true;
		}

		return noOrders;
	}

	void LineManager::display(std::ostream& os) const
	{
		auto displayStation = [&](Workstation* station) { station->display(os); };
		for_each(m_activeLine.begin(), m_activeLine.end(), displayStation);
	}
}