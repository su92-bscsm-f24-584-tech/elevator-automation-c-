#include <iostream>
#include "users_authenticate.h"
#include "elevator.cpp"

using namespace std;

int main() {
    users u1;
    string filename = "users.csv";

    // Authenticate user and get their type
    string designation = u1.authenticate(filename);

    FloorList f;
    f.createFloors(30);
    f.createElevators();

    int option;

    // Clear screen after login
    system("cls");
    f.showAllElevators();    // Show elevator status on login
    u1.timey(designation);  // Show greeting with user type

    while (true) {
        system("cls");           // Clear screen at start of menu
        f.showAllElevators();    // Show elevators first
        u1.timey(designation);   // Show greeting with user type

        cout << "\n=========== MAIN MENU ===========\n";
        cout << "0. Exit\n";
        cout << "1. Use Elevator Normally\n";
        cout << "2. Elevators (Admin Panel)\n";
        cout << "3. Mass Elevator\n";
        cout << "4. Staff Elevator\n";
        cout << "Choose: ";
        cin >> option;

        switch (option) {

            // EXIT -------------------------
            case 0:
                return 0;

            // NORMAL ELEVATOR USE ----------
            case 1: {
                system("cls");
                f.showAllElevators();
                u1.timey(designation);
                f.restricted_automation();
                cout << "\nPress Enter to return to Main Menu...";
                cin.ignore(); cin.get();
                break;
            }

            // ELEVATORS (ADMIN PANEL) ------
            case 2: {
                if (designation != "admin") {
                    cout << "Access denied! Admin only.\n";
                    cin.ignore(); cin.get();
                    break;
                }

                int admin_option;
                system("cls"); 
                f.showAllElevators();
                u1.timey(designation);

                cout << "\n========= ADMIN PANEL =========\n";
                cout << "0. Back\n";
                cout << "1. Change ELEVATOR STATUS\n";
                cout << "2. Add or Remove Floors\n";
                cout << "Choose: ";
                cin >> admin_option;

                switch (admin_option) {
                    case 0: break;

                    case 1: {
                        int status_option;
                        cout << "1. DISABLE ELEVATOR\n";
                        cout << "2. ENABLE ELEVATOR\n";
                        cin >> status_option;

                        if (status_option == 1) {
                            int ide;
                            cout << "ENTER THE ELEVATOR ID: ";
                            cin >> ide;
                            f.ele_unvail(ide);
                            cout << "\nPress Enter to Reload...";
                            cin.ignore(); cin.get();
                        } else if (status_option == 2) {
                            f.enableElevator();
                            cout << "\nPress Enter to Reload...";
                            cin.ignore(); cin.get();
                        }
                        break;
                    }

                    case 2: {
                        int new_floors;
                        cout << "Enter new number of floors: ";
                        cin >> new_floors;
                        f.createFloors(new_floors);
                        f.createElevators();
                        cout << "Floors updated.\n";
                        cin.ignore(); cin.get();
                        break;
                    }


                    default:
                        cout << "Invalid option.\n";
                        cin.ignore(); cin.get();
                }
                break;
            }

            // MASS ELEVATOR ----------------
            case 3: {
                system("cls");
                f.showAllElevators();
                u1.timey(designation);
                int dest;
                cout << "Enter your destination: ";
                cin >> dest;
                f.mass_move(dest);
                cout << "\nPress Enter to return to Main Menu...";
                cin.ignore(); cin.get();
                break;
            }

            // STAFF ELEVATOR ---------------
            case 4: {
                if (designation == "STAFF" || designation == "admin") {
                    system("cls");
                    f.showAllElevators();
                    u1.timey(designation);
                    int dest;
                    cout << "Enter your destination: ";
                    cin >> dest;
                    f.full_automation(dest);
                    cout << "\nPress Enter to return to Main Menu...";
                    cin.ignore(); cin.get();
                } else {
                    cout << "Access denied! STAFF only.\n";
                    cin.ignore(); cin.get();
                }
                break;
            }

            default:
                cout << "Invalid option.\n";
                cin.ignore(); cin.get();
        }
    }

    return 0;
}
