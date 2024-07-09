#pragma once
#include "Customer.h"
class NonFac : public Customer
{
public:
	NonFac();
	
	void Register();
	void ViewMenu();
	void Logout();
};

