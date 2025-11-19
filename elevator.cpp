#ifndef ELEVATOR_H
#define ELEVATOR_H
#include<stack>
#include <iostream>
using namespace std;

class FloorNode {
public:
    int floor_no;
    FloorNode* up;
    FloorNode* down;

    FloorNode(int no) : floor_no(no), up(nullptr), down(nullptr) {}
};

class Elevator {
public:
    int ID;
    int passenger;
    FloorNode* current;
    float mass;

    Elevator(int id = 0) : ID(id), passenger(0),mass(0.00) ,current(nullptr) {}
};

class FloorList {
private:
    FloorNode* head;
FloorNode* tail;
	int elevatorCount=0;
    int totalFloors=0;
    Elevator** elevators;
    stack<Elevator*> unavailable;
public:
    FloorList() {
	head=tail=nullptr;
	} 
	Elevator* ele_unvail(int id){
	for(int i=0;i<elevatorCount;i++){
		if(elevators[i]->ID==id){
			unavailable.push(elevators[i]);
		elevators[i]=nullptr;
		}
	}
	}void enableElevator() {
    if (unavailable.empty()) {
        cout << "No elevators to enable.\n";
        return;
    }

    Elevator* e = unavailable.top(); // get last disabled elevator
    unavailable.pop();               // remove from stack

    // Find first empty slot in elevators array
    for (int i = 0; i < elevatorCount - 1; i++) { // skip MASS
        if (elevators[i] == nullptr) {
            elevators[i] = e;
            cout << "Elevator " << e->ID << " enabled.\n";
            return;
        }
    }

    cout << "No space to re-enable elevator.\n";
}

    FloorNode* addFloor(int no) {
        FloorNode* newfloor = new FloorNode(no);
        if (!head) {
            head = newfloor;
            tail=newfloor;
        } else {
            newfloor->down = head;
            head->up = newfloor;
            head = newfloor;
        }
        return newfloor;
    }

    void createFloors(int count) {
        for (int i = 0; i < count; ++i) {
            addFloor(i);
        }
    }
void totalFloor(){
	    FloorNode* temp = head;
        while (temp) { totalFloors++; temp = temp->down; }
        cout<<"Total floor: "<<totalFloors<<endl;
}

void createElevators() {
    totalFloor();  // calculate floors

    FloorNode* temp = head;

    // Normal elevator count = 1/3 of floors (minimum 1)
    elevatorCount = max(1, totalFloors / 3);

    // We need +1 slot for MASS elevator
    elevators = new Elevator*[elevatorCount + 1];

    int step = totalFloors / elevatorCount;

    // --- Create normal elevators ---
    for (int i = 0; i < elevatorCount; ++i) {
        elevators[i] = new Elevator(i + 1);

        temp = head;
        int targetFloor = i * step;

        for (int f = 0; f < targetFloor && temp->down; ++f)
            temp = temp->down;

        elevators[i]->current = temp;

    }

    // --- Create MASS elevator ---
    int massID = elevatorCount + 1;
    elevators[elevatorCount] = new Elevator(massID);

    // MASS elevator starts at floor 1
    temp = head;
    int targetFloor = 1;

    for (int f = 0; f < targetFloor && temp->down; ++f)
        temp = temp->down;

    elevators[elevatorCount]->current = temp;


    // Increase total elevator count to include MASS
    elevatorCount++;
}
void mass_move(int destination) {
    int massIndex = elevatorCount - 1; // last elevator = MASS
    Elevator* e = elevators[massIndex];

    if(destination > e->current->floor_no)
        moveup(destination, massIndex);
    else
        movedown(destination, massIndex);

    // update passengers/mass separately
    int enter, leave;
    cout << "Enter passengers entering: "; cin >> enter;
    cout << "Enter passengers leaving: "; cin >> leave;
    e->passenger += enter - leave;
    if(e->passenger < 0) e->passenger = 0;
    e->mass = e->passenger * 90;
}


    void showFloors() {
        FloorNode* temp = head;
        cout << "Floors from top to bottom:\n";
        while (temp) {
            cout << "Floor: " << temp->floor_no << "\n";
            temp = temp->down;
        }
    }
	void moveup(int destination, int no) {
    if (no < 0 || elevators == nullptr) return;

    Elevator* e = elevators[no];
    if (!e->current) return;

    FloorNode* temp = e->current;

    while (temp && temp->floor_no < destination) {
        temp = temp->up; // move up in the linked list
    }

    if (temp && temp->floor_no == destination) {
        e->current = temp; // elevator reached destination
        cout << "Elevator " << e->ID 
     << " reached floor " << temp->floor_no 
     << " | Passengers: " << e->passenger << endl;

    } else {
        cout << "Destination floor not found!" << endl;
    }
}

void movedown(int destination,int no){
	if(no<0||elevators==nullptr)return;
	Elevator *e=elevators[no];
	if(!e->current)return;
	FloorNode* temp=e->current;
while(temp && temp->floor_no > destination){
    temp = temp->down;
   // cout << "Elevator " << e->ID << " passed floor " << temp->floor_no << endl;
}

if(temp && temp->floor_no == destination){
    e->current = temp;
cout << "Elevator " << e->ID 
     << " reached floor " << temp->floor_no; 
   if (no != elevatorCount - 1) { // not MASS
    cout << " | Passengers: " << e->passenger;
}
} else {
    cout << "Destination floor not found!" << endl;
}
}
Elevator* full_automation(int destination){
    if (!elevators) return nullptr; // no elevators created

    int minDist = 1e9; // large number
    int closestIndex = -1;
    int massIndex = elevatorCount - 1;
    for(int i = 0; i < elevatorCount; i++){
        Elevator* tmp = elevators[i];
        if(i == massIndex) continue;
        if(!tmp->current) continue;

        int dist = abs(tmp->current->floor_no - destination);
        if(dist < minDist){
            minDist = dist;
            closestIndex = i;
        }
    }

    if (closestIndex == -1) return nullptr; // safety

    Elevator* e = elevators[closestIndex]; // <- declare here

    if(destination > e->current->floor_no){
        moveup(destination, closestIndex);
    } else {
        cout << "To down\n";
        movedown(destination, closestIndex);
    }

    int enter = -1, leave = -1;
    while (true) {
        cout << "Enter number of passengers entering (0-9): ";
        cin >> enter;
        if (enter < 0 || enter > 9) {
            cout << "Invalid input! Must be between 0 and 9.\n";
            continue;
        }

        cout << "Enter number of passengers leaving (0-9): ";
        cin >> leave;
        if (leave < 0 || leave > 9) {
            cout << "Invalid input! Must be between 0 and 9.\n";
            continue;
        }

        int newCount = e->passenger + enter - leave;
        if (newCount < 0) {
            cout << "Passengers cannot be negative. Try again.\n";
            continue;
        } else if (newCount > 9) {
            cout << "Elevator cannot contain more than 9 passengers. Try again.\n";
            continue;
        }

        e->passenger = newCount;
        e->mass = e->passenger * 90;
        break; // valid entry
    }
    return e;
}

void restricted_automation() {
    int des;

    int enter,leave;

    do
	{
        cout << "Enter your destination: ";
        cin >> des;

        if (des < 0 || des > totalFloors || des == 22 || des == 23 || des == 24) {
            cout << "Wrong input! Please enter a floor.\n";
        } else {
            break; // valid input
        }
    }while(true);
	 Elevator* e = full_automation(des);
if (!e) {
    cout << "No elevators available!\n";
    return;
}


}void showAllElevators() {
    if (!elevators) {
        cout << "No elevators created!\n";
        return;
    }

    cout << "\n======= ELEVATORS STATUS =======\n";
    for (int i = 0; i < elevatorCount; i++) {
        Elevator* e = elevators[i];
        if (!e) continue; // skip unavailable elevators
        if (i == elevatorCount - 1) { // MASS elevator
            cout << "MASS Elevator " << e->ID 
                 << " | Floor: " << e->current->floor_no
                 << " | Mass: " << e->mass << " kg\n";
        } else { // NORMAL elevators
            cout << "NORMAL Elevator " << e->ID 
                 << " | Floor: " << e->current->floor_no 
                 << " | Passengers: " << e->passenger
                 << " | Mass: " << e->mass << " kg\n";
        }
    }
    cout << "===============================\n";
}


};
/*
int main() {
    FloorList f;
    f.createFloors(15);
    f.showFloors();

    cout << "\nCreating elevators...\n";
    Elevator** elevators = f.createElevators();

}
*/
#endif
