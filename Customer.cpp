#include "Customer.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>


string toLower(const string& str) {
	string result = str;
	transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}
void Customer::dispInterface()
{
	int op1;
	do
	{
		cout << "\n====================== Customer Menu ======================\n";
		cout << "1. View Menu\n";
		cout << "2. Add to Cart\n";
		cout << "3. Remove from Cart\n";
		cout << "4. Place Order\n";
		cout << "5. Total Bill\n";
		cout << "6. Feedback\n";
		cout << "7. View Cart\n";
		cout << "8. View Order History\n";
		cout << "9. Notifications\n";
		cout << "10. Logout\n";
		cout << "============================================================\n";
		cout << "Enter your choice (1-10): ";
		cin >> op1;
		switch (op1)
		{
		case 1:
			ViewMenu();
			break;
		case 2:
			addtoCart();
			break;
		case 3:
			removeFromCart();
			break;
		case 4:
			checkout();
			break;  
		case 5:
			totalBill();
			break;
		case 6:
			RateMenuItem();
			break;
		case 7:
			viewCart();
			break;
		case 8:
			ViewOrderHistory();
			break;
		case 9:
			ViewNotifications();
		case 10:
			Logout();
			break;
		default:
			cout << "INVALID OUTPUT";
			break;
		}
	} while (op1 != 10);
}


void Customer::addtoCart()
{
	string item;
	cout << "Enter the name of the item: ";
	cin.ignore(); //Ignore the newline character in the buffer
	getline(cin, item);

	//check if the item exists in the menu
	ifstream inputFile(currentMenuFileName.c_str());

	if (!inputFile.is_open()) {
		cout << "Error opening menu file: " << currentMenuFileName << endl;
		return;
	}

	string itemName, price;
	int q, p;
	string name;

	string lowercaseInput = toLower(item);

	bool flag = false;
	while (inputFile >> q) {
		//Read the entire line for item name
		getline(inputFile >> ws, itemName);
		inputFile >> price;

		//Read the item name before the if statement
		string lowercaseItem = toLower(itemName);
		if (lowercaseInput == lowercaseItem) {
			name = itemName;
			p = stoi(price);
			flag = true;
			break;
		}
	}

	inputFile.close();

	if (flag) {
		int quantity;
		do {
			cout << "Enter the quantity (must be a positive integer): ";
			while (!(cin >> quantity) || quantity <= 0) {
				cout << "Invalid input. Please enter a positive integer for quantity: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			//checking if the quantity exceeds the available stock
			if (quantity > q) {
				cout << "Error: Quantity exceeds available stock. Current stock is " << q << ".\n";
			}
			else {
				//update the stock in the .txt file
				cart.add(name, quantity, p);
				cout << "Item added to cart";
				break;
			}
		} while (true);
	}
	else {
		cout << "Item not found";
	}
}


void Customer::removeFromCart()
{
	string item;
	cout << "Enter the name of the item: ";
	cin.ignore(); 
	getline(cin, item);
	

	bool flag = 0;
	string* temp = cart.name;
	for (int i = 0; i < cart.size; i++)
	{
		if (temp[i] == item)
		{
			flag = 1;
			break;
		}
	}
	if (flag)
	{
		cart.remove(item);
		cout << "Item Removed from cart";
	}
	else
	{
		cout << "Item not found";
	}
}

void Customer::checkout()
{
	srand(time(0));
	string orderID = to_string(rand() % 10000);
	cout << "Order ID: " << orderID << endl;
	string customerName = currentname;
	cout<<"Customer Name: "<<customerName<<endl;
	string orderStatus = "Placed";
	cout <<"Order Status: "<<orderStatus<<endl;
	cout<<"Items: "<<endl;
	cart.display();
	cout<<"Total: "<<cart.total<<endl;

	fstream file;
	file.open("Orderhistory.txt", ios::app);
	file << orderID << " " << customerName << " " << orderStatus << "\n";
	file << "CART: \n" << endl;	
	for (int i = 0; i < cart.size; i++)
	{
		file << cart.name[i] << " Q: " << cart.quantity[i] << " P: " << cart.price[i] << endl;
	}
	file << "TOTAL: " << cart.total << endl <<endl;
	file.close();
}
void Customer::viewCart()
{
	cart.display();
}
void Customer::totalBill()
{
	cout<<"TOTAL: " << cart.total <<endl;
}

int Customer::getStock(const string& itemName) const
{
	ifstream menuFile(currentMenuFileName);

	if (!menuFile.is_open()) {
		cout << "Error opening menu file: " << currentMenuFileName << endl;
		return -1;  
	}

	string quantity, name, price;
	int stock = -1;  //Default value in case the item is not found

	while (menuFile >> quantity >> name >> price) {
		if (name == itemName) {
			stock = stoi(quantity);
			break;  //item found, now exit the loop
		}
	}

	menuFile.close();
	return stock;
}

void Customer::ViewOrderHistory()
{
	ifstream file("Orderhistory.txt");
	if (!file.is_open())
	{
		cout << "Error opening Orderhistory.txt" << endl;
		return;
	}

	string line;
	while (getline(file, line))
	{
		cout << line << endl;
	}

	file.close();
}
