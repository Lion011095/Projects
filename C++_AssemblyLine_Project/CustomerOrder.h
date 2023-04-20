
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <string>

#include "Station.h"

namespace sdds
{
	class CustomerOrder
	{
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };
			// 1 arg Constructor
			Item(const std::string& src) : m_itemName(src) {};
		};

		std::string m_name{};				// the name of the customer.
		std::string m_product{};			// the name of the product being assembled.
		std::size_t m_cntItem = 0;			// a count of the number of items in the customer's order.
		Item** m_lstItem{};					// a dynamically allocated array of pointers. Each element of the array points to a dynamically allocated object of type Item.
		static std::size_t m_widthField;	// the maximum width of a field, used for display purposes.
	public:
		CustomerOrder() = default;
		CustomerOrder(const std::string& orderDetails);
		CustomerOrder(const CustomerOrder& right);
		CustomerOrder& operator=(const CustomerOrder&) = delete;
		CustomerOrder(CustomerOrder&& right) noexcept;
		CustomerOrder& operator=(CustomerOrder&& right) noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif // !SDDS_CUSTOMERORDER_H
