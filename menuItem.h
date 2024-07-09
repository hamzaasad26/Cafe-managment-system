#pragma once


#include <string>

using namespace std;
struct item
{
    string ItemID, ItemName, ItemDescription;
    double Price;
    int check;
};

class MenuItem {
    item* items;
    int QuantityInStock;

public:
    MenuItem(string id, string name, string desc, double price, int stock);
    void UpdateStock(int newStock);  
};
//items = new item[num];






