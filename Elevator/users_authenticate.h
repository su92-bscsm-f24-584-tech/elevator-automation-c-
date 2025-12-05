#ifndef USERS_AUTHENTICATE_H
#define USERS_AUTHENTICATE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include"utilities.h"
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
  cout<<"=========================This Is MATROLO HOTEL At Your Service==========================\n";
  cout<<"DEFAULT PIN IS 0000"<<endl;
	cout << "\nEnter THE PIN: ";
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

void change_pin(int new_pin,string designation){
string filename = "users.csv";

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    ofstream temp("temp.csv");
    if (!temp.is_open()) {
        cout << "Error creating temp file!" << endl;
        return;
    }

   
	string line;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, u1.pass, ',');
        getline(ss, u1.name);
            if (u1.name == designation) {
            temp << new_pin << "," << u1.name << "\n";
        } else {
            temp << u1.pass << "," << u1.name << "\n";
        }
    }

    file.close();
    temp.close();

    // Replace original file
    remove("users.csv");
    rename("temp.csv", "users.csv");

    cout << "PIN updated for " << designation << "." << endl;
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
                userType = "Admin";
            } else if (u1.name == "Vip") {
                userType = "Vip";
            } else if (u1.name == "Staff") {
                userType = "Staff";
            }  else {
                userType = "Users";
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
