#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Transport {
public:
    string name;
    string gender;
    int age;
    string boardingPoint;
    string destination;

    virtual void book(string passengerName, string passengerGender, int passengerAge, string boardPoint, string dest) = 0;
    virtual void checkAvailability() = 0;
    virtual float calculateFare() = 0;
    virtual string getType() = 0;

    void setPassengerDetails(string passengerName, string passengerGender, int passengerAge, string boardPoint, string dest) {
        name = passengerName;
        gender = passengerGender;
        age = passengerAge;
        boardingPoint = boardPoint;
        destination = dest;
    }
};

class Bus : public Transport {
public:
    void book(string passengerName, string passengerGender, int passengerAge, string boardPoint, string dest) override {
        setPassengerDetails(passengerName, passengerGender, passengerAge, boardPoint, dest);
        cout << "Bus ticket booked for " << name << "." << endl;
    }

    void checkAvailability() override {
        cout << "Checking bus seat availability..." << endl;
    }

    float calculateFare() override {
        return 150.0; // Example fare
    }

    string getType() override {
        return "Bus";
    }
};

class Train : public Transport {
public:
    void book(string passengerName, string passengerGender, int passengerAge, string boardPoint, string dest) override {
        setPassengerDetails(passengerName, passengerGender, passengerAge, boardPoint, dest);
        cout << "Train ticket booked for " << name << "." << endl;
    }

    void checkAvailability() override {
        cout << "Checking train seat availability..." << endl;
    }

    float calculateFare() override {
        return 500.0; // Example fare
    }

    string getType() override {
        return "Train";
    }
};

class Flight : public Transport {
public:
    void book(string passengerName, string passengerGender, int passengerAge, string boardPoint, string dest) override {
        setPassengerDetails(passengerName, passengerGender, passengerAge, boardPoint, dest);
        cout << "Flight ticket booked for " << name << "." << endl;
    }

    void checkAvailability() override {
        cout << "Checking flight seat availability..." << endl;
    }

    float calculateFare() override {
        return 5000.0; // Example fare
    }

    string getType() override {
        return "Flight";
    }
};

void writeDataToCSV(Transport* transport) {
    ofstream file("transport_data.csv", ios::app); // Open CSV file in append mode
    if (file.is_open()) {
        file << "mode: " << transport->getType() << ","
             << "name: " << transport->name << ","
             << "gender: " << transport->gender << ","
             << "age: " << transport->age << ","
             << "boardingPoint: " << transport->boardingPoint << ","
             << "destination: " << transport->destination << ","
             << "fare: " << transport->calculateFare() << endl;
        file.close();
        cout << "Data written to CSV file." << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
}

void deleteEntryFromCSV(string name) {
    ifstream file("transport_data.csv");
    ofstream temp("temp.csv");
    string line;
    while (getline(file, line)) {
        if (line.find(name) == string::npos) {
            temp << line << endl;
        }
    }
    file.close();
    temp.close();
    remove("transport_data.csv");
    rename("temp.csv", "transport_data.csv");
    cout << "Entry deleted from CSV file if found." << endl;
}

void clearCSV() {
    ofstream file("transport_data.csv", ofstream::out | ofstream::trunc);
    if (file.is_open()) {
        file.close();
        cout << "CSV file cleared." << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
}

int main() {
    Transport* transport;
    Bus bus;
    Train train;
    Flight flight;

    int choice;
    string name, gender, boardingPoint, destination;
    int age;

    while (true) {
        cout << "Choose action:\n1. Book a ticket\n2. Delete an entry\n3. Clear CSV file\n4. Exit\n";
        cin >> choice;

        if (choice == 4) break;

        switch (choice) {
        case 1:
            cout << "Choose transport mode:\n1. Bus\n2. Train\n3. Flight\n";
            cin >> choice;

            cout << "Enter passenger name: ";
            cin >> name;
            cout << "Enter passenger gender: ";
            cin >> gender;
            cout << "Enter passenger age: ";
            cin >> age;
            cout << "Enter boarding point: ";
            cin >> boardingPoint;
            cout << "Enter destination: ";
            cin >> destination;

            switch (choice) {
            case 1:
                transport = &bus;
                break;
            case 2:
                transport = &train;
                break;
            case 3:
                transport = &flight;
                break;
            default:
                cout << "Invalid choice." << endl;
                continue;
            }

            transport->book(name, gender, age, boardingPoint, destination);
            transport->checkAvailability();
            cout << "Fare: " << transport->calculateFare() << endl;
            writeDataToCSV(transport);
            break;
        case 2:
            cout << "Enter name of the entry to delete: ";
            cin >> name;
            deleteEntryFromCSV(name);
            break;
        case 3:
            clearCSV();
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
