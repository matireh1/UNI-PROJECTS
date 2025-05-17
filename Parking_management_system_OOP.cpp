#include <iostream>
#include <fstream>
using namespace std;

// Car class to store car info
class Car {
public:
    string numberPlate;
    string model;

    Car(string plate = "", string carModel = "") {
        numberPlate = plate;
        model = carModel;
    }
};

// Parking System class
class ParkingSystem {
private:
    int capacity;
    Car* slots;

public:
    ParkingSystem(int totalSlots) {
        capacity = totalSlots;
        slots = new Car[capacity];
    }

    void logToFile(string action, string plate, int slot, string model) {
        ofstream logFile("parking_log.txt", ios::app);
        if (logFile.is_open()) {
            logFile << action << ": Car [" << model << " - " << plate << "] at slot " << slot << "\n";
            logFile.close();
        }
    }

    void parkCar(string plate, string model) {
        for (int i = 0; i < capacity; i++) {
            if (slots[i].numberPlate == "") {
                slots[i] = Car(plate, model);
                cout << "Car [" << model << " - " << plate << "] parked at slot " << i + 1 << ".\n";
                logToFile("PARKED", plate, i + 1, model);
                return;
            }
        }
        cout << "Parking is full.\n";
    }

    void removeCar(int slotNumber) {
        if (slotNumber < 1 || slotNumber > capacity) {
            cout << "Invalid slot number.\n";
            return;
        }

        int index = slotNumber - 1;
        if (slots[index].numberPlate == "") {
            cout << "Slot " << slotNumber << " is already empty.\n";
        } else {
            cout << "Car [" << slots[index].model << " - " << slots[index].numberPlate << "] removed from slot " << slotNumber << ".\n";
            logToFile("REMOVED", slots[index].numberPlate, slotNumber, slots[index].model);
            slots[index] = Car();
        }
    }

    void displayStatus() {
        cout << "\n--- Parking Status ---\n";
        for (int i = 0; i < capacity; i++) {
            if (slots[i].numberPlate == "") {
                cout << "Slot " << i + 1 << ": [Empty]\n";
            } else {
                cout << "Slot " << i + 1 << ": Car [" << slots[i].model << " - " << slots[i].numberPlate << "]\n";
            }
        }
    }

    void showParkingLog() {
        cout << "\n--- Parking History Log ---\n";
        ifstream logFile("parking_log.txt");
        string line;
        if (logFile.is_open()) {
            while (getline(logFile, line)) {
                cout << line << endl;
            }
            logFile.close();
        } else {
            cout << "Could not open log file.\n";
        }
    }

    ~ParkingSystem() {
        delete[] slots;
    }
};

bool login() {
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    if (username == "admin" && password == "1234") {
        cout << "Login successful.\n\n";
        return true;
    } else {
        cout << "Invalid login. Access Denied.\n";
        return false;
    }
}

int main() {
    cout << "Car Parking Management System\n";

    if (!login()) return 0;

    int totalSlots;
    cout << "Enter total parking slots: ";
    cin >> totalSlots;

    ParkingSystem system(totalSlots);
    int choice;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Park a car\n";
        cout << "2. Remove a car\n";
        cout << "3. Show current status\n";
        cout << "4. View parking history (log file)\n";
        cout << "5. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        if (choice == 1) {
            string plate, model;
            cout << "Enter car number plate: ";
            cin >> plate;
            cout << "Enter car model ";
            cin.ignore();
            getline(cin, model);
            system.parkCar(plate, model);
        } else if (choice == 2) {
            int slot;
            cout << "Enter slot number to remove car: ";
            cin >> slot;
            system.removeCar(slot);
        } else if (choice == 3) {
            system.displayStatus();
        } else if (choice == 4) {
            system.showParkingLog();
        } else if (choice == 5) {
            cout << "Exiting system. Goodbye.\n";
        } else {
            cout << "Invalid option.\n";
        }

    } while (choice != 5);

    return 0;
}
