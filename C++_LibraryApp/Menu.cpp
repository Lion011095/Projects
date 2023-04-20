// Final Project Milestone 2 
// Menu Module
// File	Menu.cpp
// Version 1.0
// Author	Lion Yakubov
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Lion Yakubov       03/11/2021		   Development
// Lion Yakubov		  11/11/2021		   Update
//---------------------------------------------------------- -
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
//---------------------------------------------------------- -
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

#include "Menu.h"
#include "Utils.h"

namespace sdds
{
	MenuItem::MenuItem(const char* name)
	{
		int n = 0;

		if (name != nullptr && strlen(name) > 0)
		{
			n = strlen(name) + 1;
			m_name = new char[n];
			strcpy(m_name, name);
		}
		else
		{
			m_name = nullptr;
		}
	}

	MenuItem::~MenuItem()
	{
		delete[] m_name;
		m_name = nullptr;
	}

	MenuItem::operator bool() const
	{
		return m_name != 0;
	}

	MenuItem::operator const char* () const
	{
		return m_name;
	}

	ostream& MenuItem::display(ostream& os) const
	{
		if (strlen(m_name) != 0)
		{
			os << m_name;
		}

		return os;
	}

	Menu::Menu() : m_title(nullptr)
	{
		m_numOfItems = 0;
	}

	Menu::Menu(const char* title) : m_title(title)
	{
		m_numOfItems = 0;
	}

	Menu::~Menu()
	{
		int i = 0;
		for (i = 0; i < m_numOfItems; i++)
		{
			delete m_items[i];
		}
		m_items[0] = nullptr;
	}

	ostream& Menu::displayTitle(ostream& os) const
	{
		if (*this && m_title)
		{
			os << m_title.m_name << endl;
		}

		return os;
	}

	ostream& Menu::displayMenu(ostream& os) const
	{
		int i = 0;
		int rowNum = 0;

		if (*this)
		{
			if (m_title)
			{
				displayTitle(os);
			}

			for (i = 0; i < m_numOfItems; i++)
			{
				rowNum = i + 1;
				os.unsetf(ios::left);
				os.width(2);
				os << rowNum << "- " << m_items[i]->m_name << endl;;
			}
			os.width(2);
			os << "0" << "- " << "Exit" << endl;
			os << "> ";
		}

		return os;
	}

	unsigned int Menu::run()
	{
		displayMenu(cout);
		return checkSelection(m_numOfItems);
	}

	unsigned int Menu::operator~()
	{
		displayMenu(cout);
		return checkSelection(m_numOfItems);
	}

	Menu& Menu::operator<<(const char* menuitemContent)
 	{
		if (m_numOfItems + 1 < MAX_MENU_ITEMS)
		{
			MenuItem* item = nullptr;
			item = new MenuItem(menuitemContent);
			m_items[m_numOfItems] = item;
			m_numOfItems++;
		}

		return *this;
	}

	Menu::operator unsigned int() const
	{
		return m_numOfItems;
	}

	Menu::operator int() const
	{
		return m_numOfItems;
	}

	Menu::operator bool() const
	{
		return m_numOfItems > 0;
	}

	const char* Menu::operator[] (int index) const
	{
		return  m_items[index]->m_name;
	}

	ostream& operator<<(ostream& os, const Menu& title)
	{
		title.displayTitle(os);
		return os;
	}
}