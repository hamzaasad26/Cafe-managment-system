#pragma once
#include "Customer.h"
class Faculty : public Customer
{
public:
	Faculty();
	
	void Register();
	void ViewMenu();
	void Logout();
};

