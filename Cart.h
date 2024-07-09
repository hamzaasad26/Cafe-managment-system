#pragma once
#include <string>
using namespace std;

class Cart
{
public:
	string* name;
	double* quantity;
	double* price;
	double total;
	int size;

	Cart()
	{
		name = 0;
		quantity = 0;
		price = 0;
		total = 0;
		size = 0;
	}

	void display();
	void add(string n, double q, double p);
	void remove(string n);
};

