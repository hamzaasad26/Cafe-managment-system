#include "Administrator.h"
#include "menuItem.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include<sstream>
#include<string>

using namespace std;


//administrator class implementations
Administrator::Administrator() : currentMenuFileName("")   
{
    string filename = "admin.txt";
    User::ReadUsersFromFile(filename);

}

void Administrator::ChooseMenu() {
    cout << "=====================================\n";
    cout << setw(30) << "1. Student Menu\n";
    cout << setw(30) << "2. Faculty Menu\n";
    cout << setw(30) << "3. Non-Faculty Menu\n";
    cout << "=====================================\n";
    cout << "Enter your choice (1-3): ";

    int menuChoice;
    cin >> menuChoice; //choice for what menu to access

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

void Administrator::ViewMenu() { //fucntion for viewingb menu
    int menuChoice = 0;
    ChooseMenu();

    //reading from the selected menu file

    ifstream menuFile(currentMenuFileName.c_str());
    if (!menuFile.is_open()) { //if file unable to open or doesnt exist : 
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

void Administrator::AddMenuItem() { //adding an item to any menu
    cout << "Administrator adding a menu item." << endl;
    string  itemName;
    double itemPrice;
    int itemStock;

    ChooseMenu();


    cout << "Enter Item Name: ";
    cin.ignore(); //for ignoring newline 
    getline(cin, itemName);

    cout << endl;
    cout << "Enter Item Price: ";
    cin >> itemPrice;
    cout << endl;
    cout << "Enter Initial Stock: ";
    cin >> itemStock;

    //updating the menu file with the new item details
    ofstream menuFile(currentMenuFileName.c_str(), ios::app);
    if (menuFile.is_open()) {
        menuFile << itemStock << "\n" << itemName << "\n" << itemPrice << "\n";
    }
    menuFile.close();

    //display that item has been added
    cout << "Menu item added successfully." << endl;
}

void Administrator::RemoveMenuItem() {
    cout << "Administrator removing a menu item." << endl;

    //prompt for which menu to modify
    ChooseMenu();

    //input the name of the item to be removed
    string itemNameToRemove;

    cout << "Enter the name of the item to remove: ";
    cin.ignore(); 
    getline(cin, itemNameToRemove);

   
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
            itemFound = true; //mark that the item was found and skip it
            menuItemCount--;
            menuData[menuItemCount] = ""; //skipping the item by setting it to an empty string
            continue;
        }
        menuItemCount++; //iterates to check if item is available
    }

    menuFile.close();

    //only updates the file if the item was found
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

void Administrator::ManageInventory() {
    cout << "Administrator managing inventory." << endl;
    //display the current menu
    ViewMenu();

    //ask for the item to update
    string updateItem;
    cout << "Enter the name of the item to update: ";
    cin.ignore(); 
    getline(cin, updateItem);

    //new stock?
    int newStock;
    cout << "Enter the new stock: ";
    cin >> newStock;

    //update the stock in the .txt file
    ifstream inputFile(currentMenuFileName.c_str());

    ofstream tempFile("temp.txt");

    string quantity, itemName, price;

    while (inputFile >> quantity >> itemName >> price) {
        if (itemName == updateItem) {
            //update the stock for the specified item
            tempFile << newStock << "\n" << itemName << "\n" << price << "\n";
        }
        else {
            //copy other items without modification
            tempFile << quantity << "\n" << itemName << "\n" << price << "\n";
        }
    }

    inputFile.close();
    tempFile.close();

    //replacing the original file with the updated one
    remove(currentMenuFileName.c_str());
    rename("temp.txt", currentMenuFileName.c_str());


    cout << "Inventory updated successfully." << endl;
}

void Administrator::ManageDiscountPromotion() {
    cout << "Administrator managing discount promotions." << endl;

   
    ViewMenu();

    //ask for the item to update
    string updateItem;
    cout << "Enter the name of the item to manage promotions: ";
    cin.ignore(); 
    getline(cin, updateItem);

    //new discount or promotion
    double newDiscount;
    cout << "Enter the new discount or promotion (in percentage): ";
    cin >> newDiscount;

    //update the discount or promotion in the Menu.txt file
    ifstream inputFile(currentMenuFileName.c_str());

    ofstream tempFile("temp.txt");

    string quantity, itemName, price;

    while (inputFile >> quantity >> itemName >> price) {
        if (itemName == updateItem) 
        {
            //update the discount or promotion for the specified item
            //adjust the price based on the new discount
            double discountedPrice = stod(price) * (1.0 - (newDiscount / 100.0));
            tempFile << quantity << "\n" << itemName << "\n" << discountedPrice << "\n";
        }
        else {
            //no modification
            tempFile << quantity << "\n" << itemName << "\n" << price << "\n";
        }
    }

    inputFile.close();
    tempFile.close();

    //replace the original file with the updated one

    remove(currentMenuFileName.c_str());
    rename("temp.txt", currentMenuFileName.c_str());


    cout << "Discount or promotion updated successfully." << endl;
}

void Administrator::ViewOrderHistory() {
    cout << "Administrator viewing order history." << endl;

    ifstream orderHistoryFile("orderHistory.txt");
    string line;

    if (orderHistoryFile.is_open()) {
        while (getline(orderHistoryFile, line)) {
            cout << line << endl;
        }
        orderHistoryFile.close();
    }
    else {
        cout << "Unable to open order history file." << endl;
    }
}

void Administrator::AddNotification() {
    cout << "Administrator adding a notification." << endl;

    //clear the input buffer to handle previous inputs
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Prompt for notification input
    string notification;
    cout << "Enter the notification text: ";
    getline(cin, notification);  

    //file to store notifications
    string notificationFile = "notifications.txt";
    ofstream outFile(notificationFile, ios::app);  

    if (!outFile.is_open()) {
        cout << "Unable to open " << notificationFile << " for writing." << endl;
        return;
    }

    //Write the notification to file
    if (!notification.empty()) {
        outFile << notification << endl;
        cout << "Notification added successfully." << endl;
    }
    else {
        cout << "No notification text entered." << endl;
    }

    outFile.close();
}

void Administrator::RemoveNotification() {
    cout << "Administrator removing a notification." << endl;

    string notificationFile = "notifications.txt";
    string tempFile = "temp_notifications.txt"; // Temporary file

    ifstream inFile(notificationFile);
    ofstream tempOutFile(tempFile);

    if (!inFile.is_open() || !tempOutFile.is_open()) {
        cout << "Error accessing files." << endl;
        return;
    }

   
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    //which notification to remove
    string notificationToRemove, line;
    cout << "Enter the exact notification text to remove: ";
    getline(cin, notificationToRemove);

    bool found = false;
    while (getline(inFile, line)) {
        if (line != notificationToRemove) {
            tempOutFile << line << endl;
        }
        else {
            found = true; //notification was found
        }
    }

    inFile.close();
    tempOutFile.close();

    if (!found) {
        cout << "Notification not found." << endl;
        remove(tempFile.c_str()); //removing the temporary file if no changes were made
        return;
    }

    //replace the original file with the temporary file
    remove(notificationFile.c_str());
    rename(tempFile.c_str(), notificationFile.c_str());

    cout << "Notification removed successfully." << endl;
}

void Administrator::RateMenuItem() {
    cout << "Administrator rating a menu item." << endl;
    
}

void Administrator::DisplayFromFile() {
    cout << "Administrator ciewing displayed info " << endl;

    cout << "Select user file to view:\n1. Students\n2. Faculty\n3. Non-Faculty\n";
    int choice;
    cin >> choice;

    string filename;
    switch (choice) {
    case 1:
        filename = "students.txt";
        break;
    case 2:
        filename = "faculty.txt";
        break;
    case 3:
        filename = "nonFacutxt";
        break;
    default:
        cout << "Invalid choice." << endl;
        return;
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    bool displayLine = false;
    cout << "Displaying every other line from " << filename << ":" << endl;
    while (getline(file, line)) {
        if (displayLine) {
            cout << line << endl;
        }
        displayLine = !displayLine;
    }

    file.close();
}

void Administrator::ViewUsersFromFile() {
    cout << "Administrator viewing users from file." << endl;
    cout << "Administrator viewing users from file." << endl;

    cout << "Select user file to view:\n1. Students\n2. Faculty\n3. Non-Faculty\n";
    int choice;
    cin >> choice;

    string filename;
    switch (choice) {
    case 1:
        filename = "students.txt";
        break;
    case 2:
        filename = "faculty.txt";
        break;
    case 3:
        filename = "nonFacutxt";
        break;
    default:
        cout << "Invalid choice." << endl;
        return;
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    bool displayLine = false;
    cout << "Displaying every other line from " << filename << ":" << endl;
    while (getline(file, line)) {
        if (displayLine) {
            cout << line << endl;
        }
        displayLine = !displayLine; 
    }

    file.close();
}

void Administrator::ViewMenuItemsFromFile() {
    cout << "Administrator viewing menu items from file." << endl;

    cout << "Select menu file to view:\n1. Student Menu\n2. Non-Faculty Menu\n3. Faculty Menu\n";
    int choice;
    cin >> choice;

    string filename;
    switch (choice) {
    case 1:
        filename = "studentmenu.txt";
        break;
    case 2:
        filename = "NonfacMenu.txt";
        break;
    case 3:
        filename = "facultymenu.txt";
        break;
    default:
        cout << "Invalid choice." << endl;
        return;
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    cout << "Displaying contents of " << filename << ":" << endl;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void Administrator::ViewOrdersFromFile() {

    //Open the OrderHistory.txt file
    ifstream orderHistoryFile("Orderhistory.txt");
    if (!orderHistoryFile.is_open()) {
        cout << "Unable to open Orderhistory.txt" << endl;
        return;
    }

    string line;
    cout << "---- Order History ----" << endl;

    // Read and display each line from the file
    while (getline(orderHistoryFile, line)) {
        cout << line << endl;
    }

    orderHistoryFile.close();
   
}

void Administrator::CalculateMonthlyEarnings() {
    cout << "Administrator calculating monthly earnings." << endl;

    // Open the OrderHistory.txt file
    ifstream orderHistoryFile("Orderhistory.txt");
    if (!orderHistoryFile.is_open()) {
        cout << "Unable to open Orderhistory.txt" << endl;
        return;
    }

    string line;
    int totalEarnings = 0;

    //read each line from the file
    while (getline(orderHistoryFile, line)) {
        size_t pos = line.find("TOTAL:");
        if (pos != string::npos) {
            //extract the substring that contains the earnings
            string earningsStr = line.substr(pos + 7); // 7 is the length of "TOTAL: "

            //convert the extracted substring to an integer
            int earnings = stoi(earningsStr);
            totalEarnings += earnings;
        }
    }

    orderHistoryFile.close();

    //output the total earnings
    cout << "Total Monthly Earnings: " << totalEarnings << endl;
}

void Administrator::ViewRatingsFromFile() {
    cout << "Administrator viewing ratings from file." << endl;

    //File containing feedback
    string feedbackFile = "feedback.txt";
    ifstream inFile(feedbackFile);

    if (!inFile.is_open()) {
        cout << "Unable to open " << feedbackFile << endl;
        return;
    }

    cout << "------ Feedback ------" << endl;

    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }

    inFile.close();
}

void Administrator::ViewPaymentsFromFile() {
    cout << "Administrator viewing payments from file." << endl;
    // Open the OrderHistory.txt file
    ifstream orderHistoryFile("Orderhistory.txt");
    if (!orderHistoryFile.is_open()) {
        cout << "Unable to open Orderhistory.txt" << endl;
        return;
    }

    string line;

    // Read each line from the file
    while (getline(orderHistoryFile, line)) {
        size_t pos = line.find("TOTAL:");
        if (pos != string::npos) {
            // Extract and display the substring that contains the total value
            string totalValue = line.substr(pos);
            cout << totalValue << endl;
        }
    }

    orderHistoryFile.close();
}

void Administrator::Logout() {
    cout << "Administrator logging out." << endl;
    // Logic for logging out
}
void Administrator::Register()
{
    string filename = "admin.txt";
    User::Register(filename);
    User::ReadUsersFromFile(filename);
}
void Administrator::dispInterface()
{
    int adminOption;
    do {
        //display the admin menu
        cout << "\n======================== Admin Menu ========================\n";
        cout << setw(30) << "1. View Menu\n";
        cout << setw(30) << "2. Add Menu Item\n";
        cout << setw(30) << "3. Remove Menu Item\n";
        cout << setw(30) << "4. Manage Inventory\n";
        cout << setw(30) << "5. Manage Discount Promotion\n";
        cout << setw(30) << "6. View Order History\n";
        cout << setw(30) << "7. Add Notification\n";
        cout << setw(30) << "8. Remove Notification\n";
        cout << setw(30) << "9. Rate Menu Item\n";
        cout << setw(30) << "10. Display Data from File\n";
        cout << setw(30) << "11. View Users from File\n";
        cout << setw(30) << "12. View Menu Items from File\n";
        cout << setw(30) << "13. View Orders from File\n";
        cout << setw(30) << "14. Calculate Monthly Earnings\n";
        cout << setw(30) << "15. View Ratings from File\n";
        cout << setw(30) << "16. View Payments from File\n";
        cout << setw(30) << "17. Logout\n";
        cout << "============================================================\n";
        cout << "Enter your choice (1-17): ";
        cin >> adminOption;

        //chosen action
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
            ManageInventory();
            break;
        case 5:
            ManageDiscountPromotion();
            break;
        case 6:
            ViewOrderHistory();
            break;
        case 7:
            AddNotification();
            break;
        case 8:
            RemoveNotification();
            break;
        case 9:
            RateMenuItem();
            break;
        case 10:
            DisplayFromFile();
            break;
        case 11:
            ViewUsersFromFile();
            break;
        case 12:
            ViewMenuItemsFromFile();
            break;
        case 13:
            ViewOrdersFromFile();
            break;
        case 14:
            CalculateMonthlyEarnings();
            break;
        case 15:
            ViewRatingsFromFile();
            break;
        case 16:
            ViewPaymentsFromFile();
            break;
        case 17:
            Logout();
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (adminOption != 17);
}