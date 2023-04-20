#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

struct Employee
{
	int employeeNumber;
	string lastName;
	string firstName;
	string email;
	string phone;
	int reportsTo;
	string jobTitle;
};

typedef struct Employee Employee;

// Functon Prototypes

// Function to call the main menu
int menu(void);

// Checks if input is a positive integer
int getPositiveInteger(void);




// Function to find employees
int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp);

// Function to display a single employee
void displayEmployee(Connection* conn, struct Employee emp);

// Function to display all employees
void displayAllEmployees(Connection* conn);

// Function stores the input in the employee pointer.
void insertEmployee(struct Employee* emp);

// Function to insert a new employee to the table.
void insertEmployee(Connection *conn, struct Employee emp);

// Delete the emplyee with the incoming emplyeeNumber
void deleteEmployee(Connection* conn, int employeeNumber);