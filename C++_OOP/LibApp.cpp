// Final Project Milestone 2
// LibApp Module
// File	LibApp.cpp
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

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

#include "LibApp.h"
#include "Book.h"
#include "PublicationSelector.h"

using namespace std;

namespace sdds 
{
	const int ALL = 1;
	const int LOANED = 2;
	const int NOT_LOADNED = 3;
	const int NO_PENALTY_DAYS = 15;
	const double COST_PER_PENALTY_DAY = 0.5;

	LibApp::LibApp(const char* fileName) : m_mainMenu("Seneca Library Application"),
										   m_exitMenu("Changes have been made to the data, what would you like to do?"),
										   m_typeMenu("Choose the type of publication:")									// 3 list initializer
	{
		m_changed = false;
		strcpy(m_fileName, fileName);
		m_mainMenu << "Add New Publication"					// main option 1 
				   << "Remove Publication"					// main option 2 
				   << "Checkout publication from library"	// main option 3 
			       << "Return publication to library";		// main option 4 

		m_exitMenu << "Save changes and exit"				// exit option 1
				   << "Cancel and go back to the main menu";// exit option 2

		m_typeMenu << "Book"								// type option 1
				   << "Publication";						// type option 2
		load();
	}

	bool LibApp::confirm(const char* message)
	{
		Menu menu(message);
		bool selection = false;

		menu << "Yes";
		if (menu.run() == 1)
		{
			selection = true;
		}

		return selection;
	}

	void LibApp::load()
	{
		char type{};
		int i;

		cout << "Loading Data" << endl;
		ifstream infile(m_fileName);
		for (i = 0; infile && i < SDDS_LIBRARY_CAPACITY; i++)
		{
			infile >> type;
			infile.ignore();
			if (infile)
			{
				if (type == 'B')
				{
					m_pubRecords[i] = new Book;
					infile >> *m_pubRecords[i];
					if (m_pubRecords[i]->getRef() > m_lastLibRefNum)
					{
						m_lastLibRefNum = m_pubRecords[i]->getRef();
					}
					m_pubRecordsNum++;
				}
				else
				{
					m_pubRecords[i] = new Publication;
					infile >> *m_pubRecords[i];
					if (m_pubRecords[i]->getRef() > m_lastLibRefNum)
					{
						m_lastLibRefNum = m_pubRecords[i]->getRef();
					}
					m_pubRecordsNum++;
				}
			}
		}
	}

	void LibApp::save()
	{
		int i = 0;

		cout << "Saving Data" << endl;
		ofstream outfile(m_fileName);
		for (i = 0; i < m_pubRecordsNum; i++)
		{
			if (m_pubRecords[i]->getRef() != 0)
			{
				m_pubRecords[i]->write(outfile);
			}
		}
	}

	int LibApp::search(int mode)
	{
		int selection;
		int refNum = 0;
		int i;
		string title;
		PublicationSelector ps("Select one of the following found matches:");

		selection = m_typeMenu.run();
		cin.ignore(1000,'\n');
		if (selection != 0)
		{
			cout << "Publication Title: ";
			getline(cin, title, '\n');
			if (mode == LOANED)
			{
				for (i = 0; i < m_pubRecordsNum; i++)
				{
					if (m_pubRecords[i]->onLoan())
					{
						if (selection == 1 && m_pubRecords[i]->type() == 'B' && strstr(*m_pubRecords[i], title.c_str()) && m_pubRecords[i]->getRef() != 0)
						{
							ps << m_pubRecords[i];
						}
						else if (selection == 2 && m_pubRecords[i]->type() == 'P' && strstr(*m_pubRecords[i], title.c_str()) && m_pubRecords[i]->getRef() != 0)
						{
							ps << m_pubRecords[i];
						}
					}
				}
			}
			else if (mode == NOT_LOADNED)
			{
				for (i = 0; i < m_pubRecordsNum; i++)
				{
					if (!m_pubRecords[i]->onLoan())
					{
						if (selection == 1 && m_pubRecords[i]->type() == 'B' && strstr(*m_pubRecords[i], title.c_str()) && m_pubRecords[i]->getRef() != 0)
						{
							ps << m_pubRecords[i];
						}
						else if (selection == 2 && m_pubRecords[i]->type() == 'P' && strstr(*m_pubRecords[i], title.c_str()) && m_pubRecords[i]->getRef() != 0)
						{
							ps << m_pubRecords[i];
						}
					}
				}
			}
			else if (mode == ALL)
			{
				for (i = 0; i < m_pubRecordsNum; i++)
				{
					if (selection == 1 && m_pubRecords[i]->type() == 'B' && strstr(*m_pubRecords[i], title.c_str()) && m_pubRecords[i]->getRef() != 0)
					{
						ps << m_pubRecords[i];
					}
					else if (selection == 2 && m_pubRecords[i]->type() == 'P' && strstr(*m_pubRecords[i], title.c_str()) && m_pubRecords[i]->getRef() != 0)
					{
						ps << m_pubRecords[i];
					}
				}
			}
		}
		else if (selection == 0)
		{
			cout << "Aborted!" << endl;
		}

		if (ps)
		{
			ps.sort();
			refNum = ps.run();
			if (refNum == 0)
			{
				cout << "Aborted!" << endl;
			}
		}
		else
		{
			cout << "No matches found!" << endl;
		}
		return refNum;
	}

	void LibApp::returnPub()
	{
		int refNum = 0;
		bool changed = false;
		Date currentDate;
		int penaltyDays = 0;
		double cost = 0.0;

		cout << "Return publication to the library" << endl;
		refNum = search(LOANED);
		if (refNum != 0)
		{
			getPub(refNum)->write(cout);
			changed = confirm("Return Publication?");
			if (changed == true)
			{
				if ((currentDate - getPub(refNum)->checkoutDate()) > NO_PENALTY_DAYS)
				{
					penaltyDays = currentDate - getPub(refNum)->checkoutDate() - NO_PENALTY_DAYS;
					cost = penaltyDays * COST_PER_PENALTY_DAY;
					cout.setf(ios::fixed);
					cout << "Please pay $"  << setprecision(2) << cost << " penalty for being " << penaltyDays << " days late!" << endl;
				}
				getPub(refNum)->set(0);
			}
			cout << "Publication returned" << endl;
			m_changed = true;
		}
		cout << endl;
	}

	void LibApp::newPublication()
	{
		bool change = false;
		int selection;
		Publication* newPub = nullptr;

		if (m_pubRecordsNum >= SDDS_LIBRARY_CAPACITY)
		{
			cout << "Library is at its maximum capacity!" << endl;
			delete newPub;
		}
		else
		{
			cout << "Adding new publication to the library" << endl;
			selection = m_typeMenu.run();
			switch (selection)
			{
			case 1:
				newPub = new Book;
				break;
			case 2:
				newPub = new Publication;
				break;
			case 0:
				cout << "Aborted!" << endl;
			}
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(2000, '\n');
				cout << "Aborted!";
			}
			else if (selection != 0)
			{
				newPub->read(cin);
				change = confirm("Add this publication to the library?");
				if (change == true)
				{
					if (newPub)
					{
						m_lastLibRefNum++;
						newPub->setRef(m_lastLibRefNum);
						m_pubRecords[m_pubRecordsNum] = newPub;
						m_pubRecordsNum++;
						m_changed = true;
						cout << "Publication added" << endl;
					}
					else
					{
						cout << "Failed to add publication!";
						delete newPub;
					}
				}
			}
		}
		cout << endl;
	}

	void LibApp::removePublication()
	{
		bool change = false;
		int delRefNum = 0;

		cout << "Removing publication from the library" << endl;
		delRefNum = search(ALL);
		if (delRefNum != 0)
		{
			getPub(delRefNum)->write(cout);
			change = confirm("Remove this publication from the library?");
			if (change == true)
			{
				m_changed = true;
				getPub(delRefNum)->setRef(0);
				cout << "Publication removed" << endl;
			}
		}
		cout << endl;
	}

	void LibApp::checkOutPub()
	{
		bool change = false;
		long int memberId;
		int refNum;

		cout << "Checkout publication from the library" << endl;
		refNum = search(NOT_LOADNED);
		if (refNum != 0)
		{
			getPub(refNum)->write(cout);
			change = confirm("Check out publication?");
			if (change == true)
			{
				cout << "Enter Membership number: ";
				cin >> memberId;
				while (memberId > 100000 || memberId < 10000)
				{
					cout << "Invalid membership number, try again: ";
					cin >> memberId;
				}
				getPub(refNum)->set(memberId);
				m_changed = true;
				cout << "Publication checked out" << endl;
			}
		}
		cout << endl;
	}

	void LibApp::run()
	{
		unsigned int selection;
		bool exit = false;
		int i = 0;

		do
		{
			selection = m_mainMenu.run();
			switch (selection)
			{
			case 1:
				newPublication();
				break;
			case 2:
				removePublication();
				break;
			case 3:
				checkOutPub();
				break;
			case 4:
				returnPub();
				break;
			case 0:
				if (m_changed == true)
				{
					do
					{
						selection = m_exitMenu.run();
						switch (selection)
						{
						case 1:
							save();
							selection = 0;
							exit = true;
							break;
						case 2:
							selection = 0;
							cout << endl;
							break;
						case 0:
							exit = confirm("This will discard all the changes are you sure?");
							break;
						}
					} while (selection != 0);
				}
				else
				{
					exit = true;
				}
				break;
			}
		} while (exit == false);

		cout << endl << setw(43) << setfill('-') << "-" << endl;
		cout << setfill(' ') << "Thanks for using Seneca Library Application" << endl;

		for (i = 0; i < m_pubRecordsNum; i++) // dealocating PPA
		{
			delete m_pubRecords[i];
		}
	}

	Publication* LibApp::getPub(int libRef)
	{
		bool found = false;
		int i = 0;

		for (i = 0; i < m_pubRecordsNum && found == false; i++)
		{
			if (libRef == m_pubRecords[i]->getRef())
			{
				found = true;
			}
		}

		return m_pubRecords[i - 1];
	}
}
