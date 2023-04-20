// Final Project Milestone 2 
// Menu Module
// File	Menu.h
// Version 1.0
// Author	Lion Yakubov
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Lion Yakubov       03/11/2021		   Development
//---------------------------------------------------------- -
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
//---------------------------------------------------------- -
/////////////////////////////////////////////////////////////////

#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__

#include <iostream>

namespace sdds
{
    const int MAX_MENU_ITEMS = 20;

    class Menu;

    class MenuItem
    {
        // Member Variables:
        char* m_name;

        // Friendships:
        friend class Menu;

        // Member Functions:
        MenuItem(const char* name);
        MenuItem(const MenuItem& source) = delete;
        MenuItem& operator=(const MenuItem& source) = delete;
        ~MenuItem();
        operator bool() const;
        operator const char* () const;
        std::ostream& display(std::ostream& os = std::cout) const;
    };

    class Menu
    {
        // Member Variables:
        MenuItem m_title;
        MenuItem* m_items[MAX_MENU_ITEMS] = {nullptr};
        int m_numOfItems;

    public:
        // Member Functions:
        Menu();
        Menu(const char* title);
        ~Menu();
        std::ostream& displayTitle(std::ostream& os = std::cout) const;
        std::ostream& displayMenu(std::ostream& os = std::cout) const;
        unsigned int run();
        unsigned int operator~();
        Menu(const Menu& source) = delete;
        Menu& operator=(const Menu& source) = delete;
        Menu& operator<<(const char* menuitemContent);
        operator unsigned int() const;
        operator int() const;
        operator bool() const;
        const char* operator[] (int index) const;
    };

    std::ostream& operator<<(std::ostream& os, const Menu& title);

    
}
#endif