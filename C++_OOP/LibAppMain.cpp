// Final Project
// Seneca Library Application Main Module
// File LibAppMain.cpp
// Version 1.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
//                    2021-11-27           Initial release
/////////////////////////////////////////////////////////////////
#include "LibApp.h"

#include "Date.h"

int main() 
{
   sdds::sdds_day = 10;
   sdds::sdds_mon = 12;
   sdds::sdds_year = 2021;
   sdds::sdds_test = true;
   sdds::LibApp theApp("LibRecs.txt");
   theApp.run();
   return 0;
}