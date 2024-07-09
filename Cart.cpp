#include "Cart.h"
#include <iostream>
void Cart::add(string n, double q, double p)
{
	if (name == 0)
	{
		name = new string[1];
		quantity = new double[1];
		price = new double[1];
		name[0] = n;
		quantity[0] = q;
		price[0] = p;
		total = p * q;
		size++;
	}
	else
	{
		size++;
		string* tempName = new string[size];
		double* tempQuantity = new double[size];
		double* tempPrice = new double[size];
		for (int i = 0; i < size - 1; i++)
		{
			tempName[i] = name[i];
			tempQuantity[i] = quantity[i];
			tempPrice[i] = price[i];
		}
		tempName[size-1] = n;
		tempQuantity[size-1] = q;
		tempPrice[size-1] = p;
		delete[] name;
		delete[] quantity;
		delete[] price;
		name = tempName;
		quantity = tempQuantity;
		price = tempPrice;
		total += (p * q);
	}
}
void Cart::remove(string n)
{
	int index = -1;
	for (int i = 0; i < size; i++)
	{
		if (name[i] == n)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		cout << "Item not found in cart" << endl;
	}
	else
	{
		size--;
		string* tempName = new string[size];
		double* tempQuantity = new double[size];
		double* tempPrice = new double[size];
		for (int i = 0; i < index; i++)
		{
			tempName[i] = name[i];
			tempQuantity[i] = quantity[i];
			tempPrice[i] = price[i];
		}
		for (int i = index; i < size; i++)
		{
			tempName[i] = name[i + 1];
			tempQuantity[i] = quantity[i + 1];
			tempPrice[i] = price[i + 1];
		}
		total -= (price[index] * quantity[index]);
		delete[] name;
		delete[] quantity;
		delete[] price;
		name = tempName;
		quantity = tempQuantity;
		price = tempPrice;
	}
}
void Cart::display()
{
	cout << "Name\tQuantity\tPrice\n\n" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << name[i] << "\t" << quantity[i] << "\t" << price[i] << endl;
	}
	cout << "Total: " << total << endl;
}