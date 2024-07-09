#pragma once

#include <string>
#include <iostream>

using namespace std;


struct login
{
    string username;
    string password;
};

class User {
protected:
    login* credentials;
    int size;
    string currentname;
public:

    User();

    // Getters
    string getUserName() const { return credentials->username; }
    string getPassword() const { return credentials->password; }

    // Setters
    void setUserName(const string& name) { credentials->username = name; }
    void setPassword(const string& pwd) { credentials->password = pwd; }
    void ReadUsersFromFile(string&);
    void Register(string&);
    void Login();





    virtual void Register() = 0;
    virtual void dispInterface() = 0;  
 
    virtual void ViewMenu() {}
   
    virtual void AddMenuItem() {}
    virtual void RemoveMenuItem() {}
    virtual void ManageInventory() {}
    virtual void ManageDiscountPromotion() {}
    virtual void ViewOrderHistory() {}

    //virtual void PlaceOrder(); // Method to place an order
    //virtual void AddItemToOrder(const string& itemID); // Method to add an item to the order
    //virtual void RemoveItemFromOrder(const string& itemID); // Method to remove an item from the order
    //virtual void ViewCurrentOrder(); // Method to view the current order


    virtual void AddNotification() {}
    virtual void RemoveNotification() {}
    virtual void ViewNotifications();
    virtual void RateMenuItem();
    virtual void DisplayFromFile() {}
    virtual void ViewUsersFromFile() {}
    virtual void ViewMenuItemsFromFile() {}
    virtual void ViewOrdersFromFile() {}
    virtual void CalculateMonthlyEarnings() {}
    virtual void ViewRatingsFromFile() {}
    virtual void ViewPaymentsFromFile() {}
    virtual void Logout() {}



    friend ostream& operator<<(ostream& os, const User& user);
    friend istream& operator>>(istream& is, User& user);

};








