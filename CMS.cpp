// CMS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "user.h"
#include "menuItem.h"
#include "Administrator.h"
#include "CafeStaff.h"
#include "Student.h"
#include "Faculty.h"
#include "NonFac.h"





using namespace std;

int main() {
    //instances of User, Customer, CafeStaff, and Administrator
    int opt1,opt2;
    User* u1 = 0;

    do
    {
        cout << "1-CUSTOMER\n2-ADMIN\n\n";
        cout << "Select your option : ";
        cin >> opt1;
       if (opt1 <= 0 || opt1 > 2)
           cout << "\n\nEROOR!!!\n";
    } while (opt1 <= 0 || opt1 > 2);

    if (opt1 == 1)
    {
        cout << "1-STUDENT 2-FACULTY 3-NON FAC\n";
        cin >> opt1;
        switch (opt1)
        {
            case 1:
                u1 = new Student;
                break;
            case 2:
                u1 = new Faculty;
                break;
            case 3:
                u1 = new NonFac;
                break;
        }
        cout << endl;
        cout << "1-LOGIN\n2-REGISTER" << endl;
        cin >> opt2;
        if (opt2 == 1)
            u1->Login() ;
		else
			u1->Register();
    }
    else
    {
        cout << endl;
        cout << "\n1-Admin 2-Staff\n";
        cin >> opt1;
        switch (opt1)
        {
        case 1:
            u1 = new Administrator();
            u1->Login();
            break;
        case 2:
            u1 = new CafeStaff();
            u1->Login();
            break;
        }
    }
    
    cout << endl;
    u1->dispInterface();

    return 0;
}


