#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const char FILENAME[] = "students.dat";

class Student {
public:
    int rollNo;
    char name[30];
    char division;
    char address[50];

    Student() {
        rollNo = 0;
        strcpy(name, "");
        division = ' ';
        strcpy(address, "");
    }

    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 30);
        cout << "Enter Division: ";
        cin >> division;
        cin.ignore();
        cout << "Enter Address: ";
        cin.getline(address, 50);
    }

    void display() const {
        cout << "Roll No: " << rollNo
             << "\nName: " << name
             << "\nDivision: " << division
             << "\nAddress: " << address << "\n";
    }

    int getRollNo() const {
        return rollNo;
    }
};

// Add record to file
void addRecord() {
    Student s;
    ofstream file(FILENAME, ios::binary | ios::app);
    s.input();
    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "Record added successfully.\n";
}

// Display all records
void displayAll() {
    Student s;
    ifstream file(FILENAME, ios::binary);
    while (file.read((char*)&s, sizeof(s))) {
        s.display();
        cout << "------------------\n";
    }
    file.close();
}

// Search record by roll number
void searchRecord(int roll) {
    Student s;
    ifstream file(FILENAME, ios::binary);
    bool found = false;
    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == roll) {
            s.display();
            found = true;
            break;
        }
    }
    file.close();
    if (!found)
        cout << "Record not found.\n";
}

// Delete a record
void deleteRecord(int roll) {
    Student s;
    ifstream inFile(FILENAME, ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    bool found = false;
    while (inFile.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == roll) {
            found = true;
        } else {
            outFile.write((char*)&s, sizeof(s));
        }
    }

    inFile.close();
    outFile.close();
    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found)
        cout << "Record deleted successfully.\n";
    else
        cout << "Record not found.\n";
}

// Edit a record
void editRecord(int roll) {
    fstream file(FILENAME, ios::binary | ios::in | ios::out);
    Student s;
    bool found = false;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == roll) {
            cout << "Current data:\n";
            s.display();
            cout << "Enter new data:\n";
            s.input();
            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));
            found = true;
            break;
        }
    }

    file.close();
    if (!found)
        cout << "Record not found.\n";
    else
        cout << "Record updated successfully.\n";
}

// Menu
int main() {
    int choice, roll;
    do {
        cout << "\n--- Student File Menu ---\n";
        cout << "1. Add Record\n2. Display All\n3. Search Record\n4. Delete Record\n5. Edit Record\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                displayAll();
                break;
            case 3:
                cout << "Enter roll number to search: ";
                cin >> roll;
                searchRecord(roll);
                break;
            case 4:
                cout << "Enter roll number to delete: ";
                cin >> roll;
                deleteRecord(roll);
                break;
            case 5:
                cout << "Enter roll number to edit: ";
                cin >> roll;
                editRecord(roll);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
