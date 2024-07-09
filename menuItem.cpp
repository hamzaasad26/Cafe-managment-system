
#include "menuItem.h"
#include <iostream>

using namespace std;


//MenuItem class implementations
MenuItem::MenuItem(string id, string name, string desc, double price, int stock) {
   
    items->ItemID = id;
    items->ItemName = name;
    items->ItemDescription = desc;
    items->Price = price;
    QuantityInStock = stock;
}

void MenuItem::UpdateStock(int newStock) {
    QuantityInStock = newStock;
    cout << "Stock updated for item " << items->ItemName << ". New stock: " << QuantityInStock << endl;
}