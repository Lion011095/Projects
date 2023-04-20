#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <occi.h>
#include <string>
#include <string.h>
#include <sstream>
#include <stdlib.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

#include "commonHelpers.h"
//Function definitions

//Function to display main menu
int menu(void)
{
	//Declare and initialize variable for user input for menu selection
	int selection = 0;

	//Display menu header and menu options
	cout << "\n*************************             HR Menu             *************************" << endl;
	cout << "*********************Tyler Hamvas, Pasha Rahimi, Lion Yakubov**********************\n" << endl;
	printf("1) Find Employee\n");
	printf("2) Report of Employees\n");
	printf("3) Add Employee\n");
	printf("4) Update Employee\n");
	printf("5) Remove Employee\n");
	printf("0) Exit\n");
	cout << "Please select an option (0-5): ";

	//Call for user input to select a menu option
	selection = getPositiveInteger();

	//Return the user selection to main logic
	return selection;
}

//checks if input is a positive integer
int getPositiveInteger(void)
{
	//Declare variable to be returned by function 
	int num;

	//Get user input to initialize num variable
	cin >> num;

	//Return value to determine whether next function should be called, or error displayed
	return num;
	
}

//Function to find employees
int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp)
{
	//Code to convert the employeeNumber to a string type so that it can pass into the following SQL query
	stringstream ss;
	ss << employeeNumber;
	string str = ss.str();
	int exist = 0;

	Statement* stmt = conn->createStatement();

	//Query sent to SQL to retrieve information based on the employeeNumber input by user
	ResultSet* rs = stmt->executeQuery("SELECT EMPLOYEE_ID, Last_Name, first_name, email, phone_number, job_id, manager_id FROM EMPLOYEES where employee_id = " + str);

	//Enter if rs contains information based on employeeNumber 
	while (rs->next())
	{
		//Create variables for the data received and store data
		int empNum = rs->getInt(1);
		string lastName = rs->getString(2);
		string firstName = rs->getString(3);
		string email = rs->getString(4);
		string phone = rs->getString(5);
		string jobID = rs->getString(6);
		int managerID = rs->getInt(7);

		//Pass data received to emp struct
		emp->employeeNumber = empNum;
		emp->firstName = firstName;
		emp->lastName = lastName;
		emp->email = email;
		emp->phone = phone;
		emp->jobTitle = jobID;
		emp->reportsTo = managerID;

		//If employee exists, return 1
		exist = 1;
	}
	//End the statement
	conn->terminateStatement(stmt);

	//If employee doesn't exist, return 0 to display error message
	return exist;
}

//Function to display a single employee
void displayEmployee(Connection*conn, struct Employee emp)
{
	//Display employee information from values stored in the emp struct from findEmployee function
	cout << "\n-------------- Employee Information -------------" << endl;
	cout << "Employee Number: " << emp.employeeNumber << endl;
	cout << "Last Name: " << emp.lastName << endl;
	cout << "First Name: " << emp.firstName << endl;
	cout << "Phone Number: " << emp.phone << endl;
	cout << "Email: " << emp.email << endl;
	cout << "Manager ID: " << emp.reportsTo << endl;
	cout << "Job Title: " << emp.jobTitle << endl;

	//Print the information directly from the struct in this case
}

//Function to display all employees
void displayAllEmployees(Connection* conn)
{
	//Create a statement
	Statement* stmt = conn->createStatement();

	//The query to be run in SQL to retrieve information from all employees in the database
	ResultSet* rs = stmt->executeQuery("SELECT e.EMPLOYEE_ID, e.Last_Name || ' ' || e.first_name, e.email, e.phone_number, m.first_name || ' ' || m.last_name FROM EMPLOYEES e LEFT OUTER JOIN EMPLOYEES m ON m.employee_id = e.manager_id order by e.employee_id");

	//Displays a header for the employee details
	cout << "ID  Employee Name             Email                   Phone                Manager Name" << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl;

	//Loop through each employee and format to display correctly as per header
	while (rs->next())
	{
		//Create variables for the data received and store data
		int empNum = rs->getInt(1);
		string fullName = rs->getString(2);
		string email = rs->getString(3);
		string phone = rs->getString(4);
		string managerID = rs->getString(5);

		//Outputting information based on above, with formatting
		cout
			<< left
			<< setw(3)
			<< empNum
			<< " "
			<< left
			<< setw(25)
			<< fullName
			<< " "
			<< left
			<< setw(23)
			<< email
			<< " "
			<< left
			<< setw(20)
			<< phone
			<< " "
			<< left
			<< setw(4)
			<< managerID << endl;
	}

	//Terminate the statement
	conn->terminateStatement(stmt);
}

void insertEmployee(struct Employee* emp)
{
	cout << "\n-------------- Employee Information -------------" << endl;
	cout << "Employee Number: ";
	cin >> emp->employeeNumber;
	cout << "Last Name: ";
	cin >> emp->lastName;
	cout << "First Name: ";
	cin >> emp->firstName;
	cout << "Phone Number: ";
	cin >> emp->phone;
	cout << "Email: ";
	cin >> emp->email;
	cout << "Manager ID: ";
	cin >> emp->reportsTo;
	cout << "Job Title: ";
	cin >> emp->jobTitle;
}

void insertEmployee(Connection* conn, struct Employee emp)
{
	//Create a statement
	Statement* stmt = conn->createStatement();

	//string insertQuery = "INSERT INTO employees(employee_id, first_name, last_name, email, phone_number, job_id, manager_id) VALUES( '" + emp.employeeNumber + "', '" + emp.firstName + "', '" + emp.lastName + "', '" + emp.email + "', '" + emp.phone + "', '" + emp.jobTitle + emp.reportsTo + "')";

//
	// The query to be run in SQL to insert information to the new employee
	stmt->executeUpdate("INSERT INTO employees(employee_id, first_name, last_name, email, phone_number, hire_date, job_id, manager_id) VALUES(" + to_string(emp.employeeNumber) + ", '" + emp.firstName + "', '" + emp.lastName + "', '" + emp.email + "', '" + emp.phone + "', '05-DEC-2021', '" + emp.jobTitle + "', " + to_string(emp.reportsTo) + ")");

	conn->commit();
	conn->terminateStatement(stmt);
}

void deleteEmployee(Connection* conn, int employeeNumber)
{
	Statement* stmt = conn->createStatement();

	stmt->executeUpdate("DELETE FROM employees WHERE employee_id =" + to_string(employeeNumber));

	conn->commit();
	conn->terminateStatement(stmt);
}
