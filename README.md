

# MATROLO Hotel Elevator System Documentation

## Project Overview

This project simulates an elevator management system for a hotel. It supports multiple user types (Users, Staff, VIP, Admin) and different elevator types (Normal, MASS). Features include:

* User authentication and role-based access.
* Dynamic floor creation and elevator allocation.
* Normal and MASS elevator operations.
* Logging elevator activities.
* Admin control for elevator status, floors, and user PIN management.
* Visual greetings and decorative outputs.

---

## Header Files and Their Roles

### 1. `utilities.h`

Utility functions and UI helpers:

* **`exiting()`**: Pauses the program until Enter is pressed.
* **`wrong_handle(int option, int min, int max)`**: Validates user input within a range.
* **`bigIDiot()`**, **`teasingFace()`**, **`welcome()`**, **`aizen()`**: Decorative ASCII art and greetings.

---

### 2. `users_authenticate.h`

Manages user authentication and role-based access:

**Struct:**

```cpp
struct user {
    string pass;
    string name;
};
```

**Class: `users`**

* **`void enter_users()`**: Displays welcome, prompts for PIN input.
* **`string authenticate(const string& filename)`**: Reads `users.csv` and returns the user type.
* **`void timey(string user)`**: Displays greeting based on time of day.
* **`void change_pin(int new_pin, string designation)`**: Updates PIN for a specific role in `users.csv`.

---

### 3. `elevator.h`

Handles floors, elevators, and their movement.

**Class: `FloorNode`**

* Represents a single floor in a doubly linked list.
* Members: `int floor_no; FloorNode* up; FloorNode* down;`.

**Class: `Elevator`**

* Represents an elevator.
* Members: `int ID, passenger; float mass; FloorNode* current;`.

**Class: `FloorList`**

* Manages the list of floors and all elevators.
* Key Members:

  * `int totalFloors, elevatorCount`
  * `Elevator** elevators`
  * `stack<Elevator*> unavailable`

**Key Functions:**

* **`void createFloors(int count)`**: Creates linked floors.
* **`void createElevators()`**: Creates normal and MASS elevators.
* **`void mass_move(int destination)`**: Moves the MASS elevator.
* **`Elevator* full_automation(int destination)`**: Moves closest normal elevator to destination.
* **`void restricted_automation()`**: User-restricted floor selection automation.
* **`void showAllElevators()`**: Displays status of all elevators.
* **`int LoadLog()`**: Loads total floors from `log.csv`.
* **`void logs(Elevator* e)`**: Logs elevator operations.
* **`Elevator* ele_unvail(int id)`**: Disables an elevator.
* **`void enableElevator()`**: Enables a disabled elevator.

---

## `main.cpp` Overview

**Program Flow:**

1. **User Authentication**

   * Calls `u1.authenticate("users.csv")`.
   * Returns user designation: `Users`, `Staff`, `Vip`, or `Admin`.

2. **Floor and Elevator Initialization**

   * Load total floors from log using `f.LoadLog()`.
   * Create floors with `f.createFloors(totalFloors)`.
   * Create elevators with `f.createElevators()`.

3. **Role-based Menu Loop**

   * Loop clears screen and shows current elevator status at the start of each iteration.

   **A. Users Menu**

   * Options: Exit, Use Elevator Normally, Mass Elevator.
   * Normal: Calls `f.restricted_automation()`.
   * Mass: Calls `f.mass_move(destination)`.

   **B. Admin Menu**

   * Options: Exit, Change Elevator Status, Add/Remove Floors, Change PIN.
   * Elevator status: Disable/Enable elevators.
   * Floors: Update total floors and regenerate floors/elevators.
   * PIN: Update PIN for `Staff`, `Admin`, `Users`, or `Vip`.

   **C. Staff/VIP Menu**

   * Only can use full automation to move elevators to a destination using `f.full_automation(dest)`.

   **D. Access Denied**

   * Any unrecognized designation receives "Access Denied" message.

4. **Input Validation**

   * All menu inputs, floor selections, elevator IDs, and PINs are validated using `wrong_handle()`.

5. **Logging**

   * Elevator operations are logged in `log.csv` with timestamp, elevator ID, and floor.

6. **Exit**

   * `exiting()` gracefully pauses program for user to press Enter.

---

## Data Flow Diagram (Simplified)

```
[User] --> [Authentication] --> [Designation]
                                  |
                                  v
                        [FloorList Initialization]
                                  |
                  ---------------------------------
                  |                               |
             [Normal Elevators]               [MASS Elevator]
                  |                               |
          [Restricted/Full Automation]        [Mass Movement]
                  |                               |
                  v                               v
              [Logging in CSV] <-------------------
                  |
                  v
           [Admin Changes / PIN Updates]
```

---

## User Roles and Permissions

| Role  | Access Capabilities                                  |
| ----- | ---------------------------------------------------- |
| Users | Restricted floors, normal elevator, MASS elevator    |
| Staff | Full elevator access                                 |
| VIP   | Full elevator access                                 |
| Admin | Full access: elevator status, floors, PIN management |

---

## Notes

* MASS elevator is treated differently: tracks mass instead of individual passengers.
* Floors are stored as a doubly linked list (`FloorNode`).
* Elevator count = 1/3 of floors minimum, plus 1 MASS elevator.
* Random restricted floors for Users are blocked in `restricted_automation()`.
* Logging ensures operations are traceable.

---
