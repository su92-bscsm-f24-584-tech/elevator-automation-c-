#ifndef USERS_AUTHENTICATE_H
#define USERS_AUTHENTICATE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include"helper.h"
#include <string>
#include <chrono>
#include <thread>
using namespace std;
struct user{
	string pass,name;
};
class users{
string user_pass;
user u1;
public:
void enter_users() {
  aizen();  // Pause for 3 seconds
 
    this_thread::sleep_for(chrono::seconds(3));
    system("cls"); // Windows
 
  welcome();
  
    this_thread::sleep_for(chrono::seconds(3));
     // Optional: clear screen after display
    system("cls"); // Windows
    // system("clear"); // Linux / macOS
  
	cout << "\n\nEnter PIN: ";
    cin >> user_pass;
}

void timey(string user) {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    int currentHour = localTime->tm_hour;
	
    if (currentHour < 12)
    {
		    cout << "Good morning," << endl;
    }else if (currentHour < 18){
	
        cout << "Good afternoon," << endl;
    }else{
	
        cout << "Good evening" << endl;}
    cout << user << "!" << endl;    
}

void add_new_user(int pass,string uname,string filename) {
    
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    file  << pass << "," << uname << endl;
    file.close();
    cout << "New user added successfully!" << endl;
}

string authenticate(const string& filename) {
    enter_users();
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        exit(0);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, u1.pass, ',');
        getline(ss, u1.name);

        if (u1.pass == user_pass) {
            string userType;

            if (u1.name == "Admin") {
                userType = "admin";
            } else if (u1.name == "Vip") {
                userType = "vip";
            } else {
                userType = "default";
            }

            cout << "Welcome, " << u1.name << "! "
                 << "(User type: " << userType << ")" << endl;

            return userType; // return designation
        }
    }

    cout << "Invalid input, start again.\n";
    system("cls"); // clear screen
    teasingFace();
    bigIDiot();
    exit(0);
}


};
#endif
