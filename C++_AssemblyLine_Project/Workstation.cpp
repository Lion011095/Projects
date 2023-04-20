
#include <string>
#include <deque>

#include "Workstation.h"
#include "Station.h"

using namespace std;

namespace sdds
{
	deque<CustomerOrder> g_pending{};
	deque<CustomerOrder> g_completed{};
	deque<CustomerOrder> g_incomplete{};

	void Workstation::fill(ostream& os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(dynamic_cast<Station&>(*this), os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		bool isMoved = false;
		if ((!m_orders.empty() && m_orders.front().isItemFilled(this->getItemName())) || (this->getQuantity() == 0 && !m_orders.empty()))
		{
			if (m_pNextStation != nullptr)
			{
				m_pNextStation->m_orders.push_back(move(m_orders.front()));
				isMoved = true;
				m_orders.pop_front();
			}
			else
			{
				if (m_orders.front().isOrderFilled())
				{
					g_completed.push_back(move(m_orders.front()));
					m_orders.pop_front();
				}
				else
				{
					g_incomplete.push_back(move(m_orders.front()));
					m_orders.pop_front();
				}
			}
		}
		return isMoved;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(ostream& os) const
	{
		if (m_pNextStation != nullptr)
		{
			os << this->getItemName() << " --> " << m_pNextStation->getItemName() << '\n';
		}
		else
		{
			os << this->getItemName() << " --> End of Line" << '\n';
		}
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(move(newOrder));
		return *this;
	}
}