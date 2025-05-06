#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string FILENAME = "students.txt";

class Student {
public:
    int rollNo;
    string name;
    char division;
    string address;

    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Division: ";
        cin >> division;
        cin.ignore();
        cout << "Enter Address: ";
        getline(cin, address);
    }

    void display() const {
        cout << "Roll No: " << rollNo << "\nName: " << name
             << "\nDivision: " << division << "\nAddress: " << address << "\n";
    }

    string to_string_record() const {
        return std::to_string(rollNo) + "," + name + "," + division + "," + address + "\n";
    }

    bool from_string_record(const string &line) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos)
            return false;

        rollNo = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        division = line[pos2 + 1];
        address = line.substr(pos3 + 1);
        return true;
    }
};

// Add a new record
void addRecord() {
    Student s;
    ofstream out(FILENAME, ios::app);
    s.input();
    out << s.to_string_record();
    out.close();
    cout << "Record added.\n";
}

// Display all records
void displayAll() {
    ifstream in(FILENAME);
    string line;
    Student s;

    while (getline(in, line)) {
        if (s.from_string_record(line)) {
            s.display();
            cout << "------------------\n";
        }
    }
    in.close();
}

// Search by roll number
void searchRecord(int roll) {
    ifstream in(FILENAME);
    string line;
    Student s;
    bool found = false;

    while (getline(in, line)) {
        if (s.from_string_record(line) && s.rollNo == roll) {
            s.display();
            found = true;
            break;
        }
    }
    in.close();
    if (!found)
        cout << "Record not found.\n";
}

// Delete a record
void deleteRecord(int roll) {
    ifstream in(FILENAME);
    ofstream temp("temp.txt");
    string line;
    Student s;
    bool found = false;

    while (getline(in, line)) {
        if (s.from_string_record(line) && s.rollNo == roll) {
            found = true;
            continue; // skip this record
        }
        temp << line << endl;
    }

    in.close();
    temp.close();
    remove(FILENAME.c_str());
    rename("temp.txt", FILENAME.c_str());

    if (found)
        cout << "Record deleted.\n";
    else
        cout << "Record not found.\n";
}

// Edit a record
void editRecord(int roll) {
    ifstream in(FILENAME);
    ofstream temp("temp.txt");
    string line;
    Student s;
    bool found = false;

    while (getline(in, line)) {
        if (s.from_string_record(line) && s.rollNo == roll) {
            cout << "Current record:\n";
            s.display();
            cout << "Enter new data:\n";
            s.input();
            temp << s.to_string_record();
            found = true;
        } else {
            temp << line << endl;
        }
    }

    in.close();
    temp.close();
    remove(FILENAME.c_str());
    rename("temp.txt", FILENAME.c_str());

    if (found)
        cout << "Record updated.\n";
    else
        cout << "Record not found.\n";
}

// Menu
int main() {
    int choice, roll;
    do {
        cout << "\n--- Student File Menu (Sequential File) ---\n";
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
