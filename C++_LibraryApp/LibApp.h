// Final Project Milestone 2 
// LibApp Module
// File	LibApp.h
// Version 1.0
// Author	Lion Yakubov
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Lion Yakubov       11/11/2021		   Development
//---------------------------------------------------------- -
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
//---------------------------------------------------------- -
/////////////////////////////////////////////////////////////////

#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H

#include "Menu.h"
#include "Lib.h"
#include "Publication.h"

namespace sdds 
{
   class LibApp 
   {
	   // Member veriables: (private)
	   bool m_changed;
	   Menu m_mainMenu;
	   Menu m_exitMenu;
	   char m_fileName[SDDS_MAX_AUTHOR_NAME]{};
	   Publication* m_pubRecords[SDDS_LIBRARY_CAPACITY]{};
	   int m_pubRecordsNum = 0;
	   int m_lastLibRefNum = 0;
	   Menu m_typeMenu;
	   // Member functions: (private)
	   bool confirm(const char* message);
	   void load();
	   void save();
	   int search(int mode);
	   void returnPub();
   public:
	   LibApp(const char* fileName);
	   void newPublication();
	   void removePublication();
	   void checkOutPub();
	   void run();
	   Publication* getPub(int libRef);
	   
   };
}
#endif // !SDDS_LIBAPP_H



