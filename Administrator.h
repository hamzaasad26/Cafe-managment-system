#pragma once
#include "user.h"


class Administrator : public User {

private : 
    string currentMenuFileName;
   

public:
    Administrator();
   
    void Register() override;
    void dispInterface() override;
    void ChooseMenu();
    void ViewMenu();
    void AddMenuItem();
    void RemoveMenuItem();
    void ManageInventory();
    void ManageDiscountPromotion();
    void ViewOrderHistory();
    void AddNotification();
    void RemoveNotification();
    void RateMenuItem();
    void DisplayFromFile();
    void ViewUsersFromFile();
    void ViewMenuItemsFromFile();
    void ViewOrdersFromFile();
    void CalculateMonthlyEarnings();
    void ViewRatingsFromFile();
    void ViewPaymentsFromFile();
    void Logout();
};
