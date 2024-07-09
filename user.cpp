#include "user.h"
#include <iostream>
#include <fstream>

using namespace std;

// User class implementations

User::User()
{
    credentials = 0;
    size = 0;
}


//operator overoloading
ostream& operator<<(ostream& os, const User& user) 
{
    os << "User Name: " << user.getUserName() << "\n";
    os << "User Password: " << user.getUserName() << "\n";
    return os;
}

istream& operator>>(istream& is, User& user) {
    string temp;

    cout << "Enter User Name: ";
    is >> temp;
    user.setUserName(temp);

    cout << "Enter Password: ";
    is >> temp;
    user.setPassword(temp);  


    return is;
}



void User::Register(string& filename) {
    //read existing data from file
    ifstream inFile(filename);
    int currentSize = 0;
    if (inFile.is_open()) {
        inFile >> currentSize;
        credentials = new login[currentSize];
        string line;
        getline(inFile, line); 


        for (int i = 0; i < currentSize; ++i) {
            getline(inFile, credentials[i].username);
            getline(inFile, credentials[i].password);
        }
        inFile.close();
    }

    //increment size for new user
    size = currentSize + 1;

    //new user data
    cout << "ENTER USERNAME TO REGISTER:\t";
    string name, password;
    cin.ignore();
    getline(cin, name);
    cout << "\nENTER PASSWORD TO REGISTER:\t";
    getline(cin, password);

    //Add new user to the credentials
    login* temp = new login[size];
    for (int i = 0; i < currentSize; ++i) {
        temp[i].username = credentials[i].username;
        temp[i].password = credentials[i].password;
    }
    temp[size - 1].username = name;
    temp[size - 1].password = password;
    delete[] credentials;
    credentials = temp;

   
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << size << endl;  

        for (int i = 0; i < size; ++i) {
            outFile << credentials[i].username << "\n" << credentials[i].password << "\n";
        }
        outFile.close();
    }
}



void User::ReadUsersFromFile(string& filename) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        file >> size;
        credentials = new login[size];
        getline(file, line);
        for (int i = 0; i < size;i++)
        {
            if (getline(file, line))
                credentials[i].username = line;

            if (getline(file, line))
            {
                credentials[i].password = line;
            }
        }
    }
    file.close();
}

void User::Login()
{
    bool flag = 1;
    cin.ignore();

    string username;
    while (flag)
    {
        username;
        cout << "Login\nENTER UserName: ";
        getline(cin, username);

        string password;
        cout << "\nENTER Password: ";
        cin.clear();
        getline(cin, password);

        for (int i = 0;i < size;i++)
        {
            if (credentials[i].username == username)
            {
                if (credentials[i].password == password)
                    flag = 0;
                else
                {
                    cout << "\nWRONG PASSWORD!!!!!!!!!!!\n";
                    break;
                }
            }
        }
        if (flag)
            cout << "\n\nUsername not found!!!!!!!\n\n";
    }
    currentname = username;
    cout << "LOGIN SUCCESSFUL";


}


void User::RateMenuItem() {
    string filename = "feedback.txt";
    ifstream inFile(filename);
    int feedbackCount = 0;
    string line;

    cin.ignore();
    //Read the current count of feedback entries
    if (inFile.is_open()) {
        if (getline(inFile, line)) {
            feedbackCount = stoi(line);
        }
        inFile.close();
    }

    //Increment feedback count for the new entry
    feedbackCount++;

    //Get user feedback
    string userFeedback;
    cout << "Enter your feedback: ";
    getline(cin, userFeedback);

    //write updated feedback count and new feedback to the file
    ofstream outFile(filename);
    if (outFile.is_open()) {
        //write the new count of feedback entries
        outFile << feedbackCount << endl;

        //append the new feedback
        outFile << "Feedback: " << userFeedback << "\n\n";
        cout << "Thank you for your feedback!" << endl;
    }
    else {
        cout << "Unable to open file to write feedback." << endl;
    }
    outFile.close();
}


void User::ViewNotifications() {
    cout << "Viewing notifications." << endl;

    //Open the notifications.txt file
    ifstream notificationFile("notifications.txt");
    if (!notificationFile.is_open()) {
        cout << "Unable to open notifications.txt" << endl;
        return;
    }

    string notification;
    bool hasNotifications = false;

    cout << "---- Notifications ----" << endl;

    //Read and display each notification
    while (getline(notificationFile, notification)) {
        cout << notification << endl;
        hasNotifications = true;
    }

    if (!hasNotifications) {
        cout << "No notifications available." << endl;
    }

    notificationFile.close();
}