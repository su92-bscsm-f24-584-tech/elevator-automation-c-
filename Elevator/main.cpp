#include <iostream>
#include "users_authenticate.h"
#include "elevator.h"
#include "utilities.h"

using namespace std;

int main() {
    users u1;

    // Authenticate user and get their type
    string designation = u1.authenticate("users.csv");

    FloorList f;
    f.totalFloors = f.LoadLog();  // Load floors from log
    if (f.totalFloors == 0) f.totalFloors = 30;
    f.createFloors(f.totalFloors);
    f.createElevators();  // elevators are based on totalFloors

    int option;

    // Clear screen after login
    system("cls");
    f.showAllElevators();
    u1.timey(designation);

    while (true) {
        system("cls");
        f.showAllElevators();
        u1.timey(designation);

        if (designation == "Users") {
            int normal_option;
            cout << "\n=========== MAIN MENU ===========\n";
            cout << "0. Exit\n";
            cout << "1. Use Elevator Normally\n";
            cout << "2. Mass Elevators\n";
            cout << "Choose: ";
            cin >> normal_option;
            normal_option = wrong_handle(normal_option, 0, 2);
            cin.ignore();  // clear newline

            system("cls");
            f.showAllElevators();
            u1.timey(designation);

            if (normal_option == 0) {
                exiting();
                break;
            } else if (normal_option == 1) {
                cout << "\n=========== NORMAL ELEVATOR MENU ===========\n";
                f.restricted_automation();
            } else if (normal_option == 2) {
                cout << "\n=========== MASS MENU ===========\n";
                int dest;
                cout << "Enter your destination: ";
                cin >> dest;
                dest = wrong_handle(dest, 0, f.totalFloors);
                f.mass_move(dest);
            }
            cout << "\nPress Enter to return to Main Menu...";
            cin.ignore();
            cin.get();

        } else if (designation == "Admin") {
            int admin_option;
            system("cls");
            f.showAllElevators();
            u1.timey(designation);

            cout << "\n========= ADMIN PANEL =========\n";
            cout << "0. Exit\n";
            cout << "1. Change ELEVATOR STATUS\n";
            cout << "2. Add or Remove Floors\n";
            cout << "3. Change PIN code\n";
            cout << "Choose: ";
            cin >> admin_option;
            admin_option = wrong_handle(admin_option, 0, 3);
            cin.ignore();

            switch (admin_option) {
                case 0:
                    exiting();
                    return 0;

                case 1: {
                    int status_option;
                    cout << "1. DISABLE ELEVATOR\n";
                    cout << "2. ENABLE ELEVATOR\n";
                    cout << "Choose: ";
                    cin >> status_option;
                    status_option = wrong_handle(status_option, 1, 2);
                    cin.ignore();

                    if (status_option == 1) {
                        int ide;
                        cout << "ENTER THE ELEVATOR ID: ";
                        cin >> ide;
                        ide = wrong_handle(ide, 1, f.elevatorCount);
                        f.ele_unvail(ide);
                    } else {
                        f.enableElevator();
                    }
                    break;
                }

                case 2: {
                    int new_floors;
                    cout << "Enter new number of floors: ";
                    cin >> new_floors;
                    f.totalFloors = new_floors;
                    f.createFloors(new_floors);
                    f.createElevators();
                    cout << "Floors updated.\n";
                    break;
                }

                case 3: {
                    int input, newpin;
                    cout << "1. STAFF\n2. ADMIN\n3. USERS\n4. VIP\nChoose: ";
                    cin >> input;
                    input = wrong_handle(input, 1, 4);
                    cout << "Enter the new PIN: ";
                    cin >> newpin;
                    newpin = wrong_handle(newpin, 0, 9999);
                    switch (input) {
                        case 1: u1.change_pin(newpin, "Staff"); break;
                        case 2: u1.change_pin(newpin, "Admin"); break;
                        case 3: u1.change_pin(newpin, "Users"); break;
                        case 4: u1.change_pin(newpin, "Vip"); break;
                    }
                    break;
                }

                default:
                    cout << "Invalid option.\n";
            }

            cout << "\nPress Enter to return to Main Menu...";
            cin.ignore();
            cin.get();

        } else if (designation == "Staff" || designation == "Vip") {
            system("cls");
            f.showAllElevators();
            u1.timey(designation);
            int dest;
            cout << "Enter your destination: ";
            cin >> dest;
            dest = wrong_handle(dest, 0, f.totalFloors);
            f.full_automation(dest);
            cout << "\nPress Enter to return to Main Menu...";
            cin.ignore();
            cin.get();
        } else {
            cout << "Access denied!\n";
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}
