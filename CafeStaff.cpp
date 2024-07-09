#include "CafeStaff.h"
#include <fstream>
#include<iostream>
#include<iomanip>

using namespace std;

//cafeStaff class implementations
CafeStaff::CafeStaff()
{
    string filename = "cafeStaff.txt";
    User::ReadUsersFromFile(filename);
}

void CafeStaff::ChooseMenu() {
    cout << "Choose the menu to operate on:\n";
    cout << "1. Student Menu\n";
    cout << "2. Faculty Menu\n";
    cout << "3. Non-Faculty Menu\n";
    cout << "Enter your choice (1-3): ";

    int menuChoice;
    cin >> menuChoice;

    switch (menuChoice) {
    case 1:
        currentMenuFileName = "studentMenu.txt";
        break;
    case 2:
        currentMenuFileName = "facultymenu.txt";
        break;
    case 3:
        currentMenuFileName = "NonfacMenu.txt";
        break;
    default:
        cout << "Invalid choice. Using the default menu.\n";

        break;
    }
}


void CafeStaff::ViewMenu() {
    int menuChoice = 0;
    ChooseMenu();

    //reading from the selected menu file
    ifstream menuFile(currentMenuFileName.c_str());
    if (!menuFile.is_open()) {
        cout << "Error opening " << currentMenuFileName << endl;
        return;
    }

    string quantity, itemName, price;
    int lineCount = 0;

    cout << "--------------------- " << currentMenuFileName << " ----------------------" << endl;
    cout << "Quantity  |  Item Name  |  Price" << endl;
    cout << "--------------------------------------------------" << endl;

    while (menuFile >> quantity) {
        getline(menuFile >> ws, itemName);
        menuFile >> price;

        cout << setw(10) << left << quantity;
        cout << setw(15) << left << itemName;
        cout << setw(10) << left << price << endl;

        lineCount++;
        if (lineCount % 3 == 0) {
            cout << endl;
        }
    }

    menuFile.close();
}

void CafeStaff::ProcessOrder() {
    cout << "CafeStaff processing an order." << endl;
    
}

void CafeStaff::AddMenuItem() 
{
    cout << "Administrator adding a menu item." << endl;
    string  itemName;
    double itemPrice;
    int itemStock;

    ChooseMenu();


    cout << "Enter Item Name: ";
    cin.ignore(); 
    getline(cin, itemName);


    cout << "Enter Item Price: ";
    cin >> itemPrice;

    cout << "Enter Initial Stock: ";
    cin >> itemStock;

    //update the menu file with the new item details
    ofstream menuFile(currentMenuFileName.c_str(), ios::app);
    if (menuFile.is_open()) {
        menuFile << itemStock << "\n" << itemName << "\n" << itemPrice << "\n";
    }
    menuFile.close();

   
    cout << "Menu item added successfully." << endl;
}

void CafeStaff::RemoveMenuItem() {
    cout << "Administrator removing a menu item." << endl;

    
    ChooseMenu();

    // Input the name of the item to be removed
    string itemNameToRemove;
    cout << "Enter the name of the item to remove: ";
    cin.ignore(); 
    getline(cin, itemNameToRemove);

    // reading menu items from file
    ifstream menuFile(currentMenuFileName);
    if (!menuFile.is_open()) {
        cout << "Error opening " << currentMenuFileName << endl;
        return;
    }

    const int MAX_MENU_ITEMS = 100;
    string menuData[MAX_MENU_ITEMS];
    int menuItemCount = 0;
    bool itemFound = false;

    while (getline(menuFile, menuData[menuItemCount]) && menuItemCount < MAX_MENU_ITEMS) {
        if (itemFound)
        {
            itemFound = false;
            continue;
        }
        if (menuData[menuItemCount].find(itemNameToRemove) != string::npos) {
            itemFound = true; // Mark that the item was found and skip it
            menuItemCount--;
            menuData[menuItemCount] = ""; // Skip the item by setting it to an empty string
            continue;
        }
        menuItemCount++;
    }

    menuFile.close();

    // Only update the file if the item was found
    ofstream updatedMenuFile(currentMenuFileName);
    if (!updatedMenuFile.is_open()) {
        cout << "Error opening " << currentMenuFileName << " for writing" << endl;
        return;
    }

    for (int i = 0; i < menuItemCount; ++i) {
        updatedMenuFile << menuData[i] << endl;
    }

    updatedMenuFile.close();
    cout << "Menu item removed successfully." << endl;

}

void CafeStaff::ManageInventory() {
    cout << "Administrator managing inventory." << endl;
    //display the current menu
    ViewMenu();

    //ask for the item to update
    string updateItem;
    cout << "Enter the name of the item to update: ";
    cin.ignore(); // Ignore the newline character in the buffer
    getline(cin, updateItem);

    //ask for the new stock
    int newStock;
    cout << "Enter the new stock: ";
    cin >> newStock;

    //Update the stock in the .txt file
    ifstream inputFile(currentMenuFileName.c_str());

    ofstream tempFile("temp.txt");

    string quantity, itemName, price;

    while (inputFile >> quantity >> itemName >> price) {
        if (itemName == updateItem) {
            //Update the stock for the specified item
            tempFile << newStock << "\n" << itemName << "\n" << price << "\n";
        }
        else {
            //Copy other items without modification
            tempFile << quantity << "\n" << itemName << "\n" << price << "\n";
        }
    }

    inputFile.close();
    tempFile.close();

    //Replace the original file with the updated one
    remove(currentMenuFileName.c_str());
    rename("temp.txt", currentMenuFileName.c_str());


    cout << "Inventory updated successfully." << endl;
}



void CafeStaff::Logout() {
    cout << "CafeStaff logging out." << endl;
    
}

void CafeStaff::Register()
{
    string filename = "cafeStaff.txt";
    User::Register(filename);
}

void CafeStaff::dispInterface()
{
    int adminOption;
    do {
        
        cout << "\n======================== Cafe staff Menu ========================\n";
        cout << setw(30) << "1. View Menu\n";
        cout << setw(30) << "2. Add Menu Item\n";
        cout << setw(30) << "3. Remove Menu Item\n";
        cout << setw(30) << "4. Logout\n";
        cout << "============================================================\n";
        cout << "Enter your choice (1-4): ";
        cin >> adminOption;

        // Perform the chosen action
        switch (adminOption) {
        case 1:
            ViewMenu();
            break;
        case 2:
            AddMenuItem();
            break;
        case 3:
            RemoveMenuItem();
            break;
        case 4:
            Logout();
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (adminOption != 5);
}