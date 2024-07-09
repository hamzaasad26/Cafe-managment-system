#include "Student.h"
#include "menuItem.h"
#include <iostream>
#include <fstream>
#include <iomanip>


Student::Student()
{
    string filename = "students.txt";
    User::ReadUsersFromFile(filename);
    currentMenuFileName = "studentMenu.txt";
}

void Student::Register()
{
    string filename = "students.txt";
    User::Register(filename);
    User::ReadUsersFromFile(filename);
}


void Student::ViewMenu() {
    cout << "\nStudent viewing menu." << endl;

    //reading from file, menu
    ifstream menuFile("studentmenu.txt");

    if (!menuFile.is_open()) {
        cout << "Error opening .txt" << endl;
        return;
    }



    string quantity, itemName, price;
    int lineCount = 0;

    cout << "--------------------- Menu ----------------------" << endl;
    cout << "Quantity  |  Item Name  |  Price" << endl;
    cout << "--------------------------------------------------" << endl;

    while (menuFile >> quantity) {
        
        getline(menuFile >> ws, itemName);
        menuFile >> price;

        cout << setw(10) << left << quantity;
        cout << setw(15) << left << itemName;
        cout << setw(10) << left << price << endl;

        //increment line count
        lineCount++;

       
        if (lineCount % 3 == 0) {
            cout << endl;
        }
    }

    menuFile.close();
}

void Student::Logout()
{
	cout << "Logging out..." << endl;
	exit(0);
}