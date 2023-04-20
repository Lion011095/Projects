// Name:				Lion Yakubov
// Seneca Student ID:   129517207
// Seneca email:		lyakubov@myseneca.ca
// Date of completion:  03/04/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <string>
#include <vector>
#include <iomanip>

#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(const string& orderDetails)
	{
		size_t beggining = 0;
		bool isMore = true;
		Utilities itemDetails;
		vector<Item> items;

		m_name = itemDetails.extractToken(orderDetails, beggining, isMore);
		m_product = itemDetails.extractToken(orderDetails, beggining, isMore);
		while(isMore == true)
		{
			++m_cntItem;
			Item item = itemDetails.extractToken(orderDetails, beggining, isMore);
			items.push_back(item);
		}
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			m_lstItem[i] = new Item (items[i]);
		}
		if (CustomerOrder::m_widthField < itemDetails.getFieldWidth())
		{
			CustomerOrder::m_widthField = itemDetails.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& right)
	{
		throw string("Copy constructors are not supported.");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& right) noexcept
	{
		m_lstItem = nullptr;
		*this = move(right);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& right) noexcept
	{
		size_t i;
		if (this != &right)
		{
			for (i = 0; i < m_cntItem && m_lstItem != nullptr; i++)
			{
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_cntItem = right.m_cntItem;
			m_product = right.m_product;
			m_name = right.m_name;
			right.m_cntItem = 0;
			right.m_product = '\0';
			right.m_name = '\0';
			this->m_lstItem = right.m_lstItem;
			right.m_lstItem = nullptr;
		}

		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		size_t i;
		for (i = 0; i < m_cntItem; ++i)
		{
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	bool CustomerOrder::isOrderFilled() const
	{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem && filled == true; ++i)
		{
			if (m_lstItem[i]->m_isFilled == false)
			{
				filled = false;
			}
		}
		return filled;
	}

	bool CustomerOrder::isItemFilled(const string& itemName) const
	{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem && filled == true; ++i)
		{
			if (m_lstItem[i]->m_itemName == itemName && m_lstItem[i]->m_isFilled == false)
			{
				filled = false;
			}
		}
		return filled;
	}

	void CustomerOrder::fillItem(Station& station, ostream& os)
	{
		bool filled = false;
		for (size_t i = 0; i < m_cntItem && filled == false; ++i)
		{
			if (station.getItemName() == m_lstItem[i]->m_itemName && station.getQuantity() > 0 && m_lstItem[i]->m_isFilled == false)
			{
				filled = true;
				m_lstItem[i]->m_isFilled = true;
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				station.updateQuantity();
				os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
			}
			else if (station.getItemName() == m_lstItem[i]->m_itemName && station.getQuantity() == 0 && m_lstItem[i]->m_isFilled == false)
			{
				os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
			}
		}
	}

	void CustomerOrder::display(ostream& os) const
	{
		os << m_name << " - " << m_product << '\n';
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			os << "[" << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] " << setfill(' ');
			os << setw(CustomerOrder::m_widthField + 2) << left << m_lstItem[i]->m_itemName;
			if (m_lstItem[i]->m_isFilled == false)
			{
				os << " - TO BE FILLED";
			}
			else
			{
				os << " - FILLED";
			}
			os << right;
			os << endl;
		}
	}
}