#include "Faculty.h"
#include "menuItem.h"
#include <iostream>
#include <fstream>
#include <iomanip>

Faculty::Faculty()
{
    string filename = "faculty.txt";
    User::ReadUsersFromFile(filename);
    currentMenuFileName = "facultymenu.txt";

}
void Faculty::Register()
{
    string filename = "faculty.txt";
    User::Register(filename);
    User::ReadUsersFromFile(filename);
}

void Faculty::ViewMenu() {
    cout << "\nFaculty viewing menu." << endl;

    //reading from file, menu
    ifstream menuFile("facultymenu.txt");

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
        //Read the entire line for item name
        getline(menuFile >> ws, itemName);
        menuFile >> price;

        cout << setw(10) << left << quantity;
        cout << setw(15) << left << itemName;
        cout << setw(10) << left << price << endl;

        //Increment line count
        lineCount++;

        //Check if there is a newline character, if yes, print a separator
        if (lineCount % 3 == 0) {
            cout << endl;
        }
    }

    menuFile.close();
}
void Faculty::Logout()
{
	cout << "Logging out..." << endl;
	exit(0);
}