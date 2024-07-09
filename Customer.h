#pragma once
#include "user.h"
#include "Cart.h"
class Customer: public User
{
public:
		Cart cart;
		string currentMenuFileName;
		virtual void Register() = 0;
		virtual void ViewMenu() = 0;
		virtual void Logout() = 0;
		void addtoCart();
		void removeFromCart();
		void checkout();
		void viewCart();
		void totalBill();
		void dispInterface();
		void ViewOrderHistory();
		int getStock(const string& itemName) const;
};

