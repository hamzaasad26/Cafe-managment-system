#pragma once
#include "Customer.h"
class Student: public Customer
{
public:
	Student();
	
	void Register();
	void ViewMenu();
	void Logout();
};

