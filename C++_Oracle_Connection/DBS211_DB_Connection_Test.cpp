#include <iostream>
#include <occi.h>
#include <string>
#include <iomanip>
#include "commonHelpers.h"

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

int main(void)
{
	// OCCI Variables
	Environment* env = nullptr;
	Connection* conn = nullptr;

	// User Variables
	string str;
	string usr;
	string pass;
	string srv;

	//Connecting to the database
	try
	{
		cout << "Please enter user name: ";
		cin >> usr;
		cout << "Please enter password: ";
		cin >> pass;
		cout << "please enter server connection: ";
		cin >> srv;

		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(usr, pass, srv);

		//Message to confirm connection was a success
		cout << "Connection is Successful!" << endl;

		//Delcaring and initializing varibles to be used - including emp struct to be used in function parameters
		int choice;
		int shouldLoop = 1;
		struct Employee emp = { 0 };
		int found = 0;
		int delEmployeeNum = 0;

		//Do loop to keep users in the menu if they enter an unexpected value for their choice
		do
		{
			//Call the menu function to display options and request user input/selection
			choice = menu();
			//Enter if statement if their select was valid (0-5)
			if (choice < 6)
			{
				//Option to Exit
				if (choice == 0)
				{
					//Display message to show user they are exiting
					cout << "\nExiting...\n";
					//Set variable to 0 to exit menu loop
					shouldLoop = 0;
					//Terminating connection/environment to safe state
					env->terminateConnection(conn);
					Environment::terminateEnvironment(env);
				}
				//Option to find an employee
				else if (choice == 1)
				{
					//Ask user to input a number for employee to search for
					cout << "Please enter an employee number: ";

					//Call function for user input
					int employeeNumber = getPositiveInteger();
					//Call function to search if employee exists, returns 1 if they exist, returns 0 if they do not
					int errorResult = findEmployee(conn, employeeNumber, &emp);

					//Enter if employee does not exist
					if (errorResult == 0)
					{
						//Error message if employee does not exist
						cout << "\nEmployee " << employeeNumber << " does not exist" << endl;
					}

					//Enter if employee does exist
					if (errorResult == 1)
					{
						//Call function to display details about the employee
						displayEmployee(conn, emp);
					}
				}
				//Option to list all employees
				else if (choice == 2)
				{
					//Call function to display information about all employees in database
					displayAllEmployees(conn);
				}
				//Option to add employee to table
				else if (choice == 3)
				{
					insertEmployee(&emp);
					found = findEmployee(conn, emp.employeeNumber, &emp);
					if (found == 1)
					{
						cout << "An employee with the same employee number exists." << endl;
					}
					else
					{
						insertEmployee(conn, emp);
						cout << endl << "The new employee is added successfully." << endl;
					}
				}
				//Option to update/modify employee in table
				else if (choice == 4)
				{
					//TO BE COMPLETED
					cout << "\nOption " << choice << " not yet available\n." << endl;
				}
				//Option to remove employee from table
				else if (choice == 5)
				{
					cout << "Employee Number: ";
					cin >> delEmployeeNum;
					found = findEmployee(conn, delEmployeeNum, &emp);
					if (found == 1)
					{
						deleteEmployee(conn, delEmployeeNum);
						cout << endl << "The employee with ID " << delEmployeeNum << " is deleted successfully." << endl;
					}
					else
					{
						cout << endl << "The employee with ID " << delEmployeeNum << " does not exist" << endl;
					}
				}
			}

			//Display error message if their selection was invalid (outside of 0-5)
			else
			{
				//Message reminding user what acceptable inputs are
				cout << "\nERROR: Please enter a number 0-5\n" << endl;
			}
			//Menu will loop while shouldLoop has value of 1, otherwise exists loop
		} while (shouldLoop == 1);

	}

	//If there is any error, this will display it
	catch (SQLException& sqlExcp)
	{
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}

	//Return control to OS
	return 0;
}