#pragma once
#include "user.h"


class CafeStaff : public User {
public:

    string currentMenuFileName;

    CafeStaff();

    void Register() override;
    void ViewMenu();
    void ManageInventory();
    void RemoveMenuItem();
    void AddMenuItem();
    void ProcessOrder();
    void Logout();
    void dispInterface();
    void ChooseMenu();
};