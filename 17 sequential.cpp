#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
 
struct Student {
    int rollNo;
    string name;
    char division;
    string address;
};
 
void addStudent() {
    ofstream file("students.txt", ios::app);
    Student s;
    cout << "Enter Roll No: "; cin >> s.rollNo;
    cout << "Enter Name: "; cin.ignore(); getline(cin, s.name);
    cout << "Enter Division: "; cin >> s.division;
    cout << "Enter Address: "; cin.ignore(); getline(cin, s.address);
 
    file << s.rollNo << " " << s.name << " " << s.division << " " << s.address << "\n";
    file.close();
    cout << "Student added successfully.\n";
}
 
void displayAll() {
    ifstream file("students.txt");
    Student s;
    cout << "\n--- Student Records ---\n";
    while (file >> s.rollNo) {
        file >> ws;
        getline(file, s.name, ' ');
        file >> s.division;
        file >> ws;
        getline(file, s.address);
        cout << "Roll No: " << s.rollNo << ", Name: " << s.name
             << ", Division: " << s.division << ", Address: " << s.address << "\n";
    }
    file.close();
}
 
void searchStudent() {
    ifstream file("students.txt");
    Student s;
    int roll;
    cout << "Enter Roll No to search: ";
    cin >> roll;
    bool found = false;
    while (file >> s.rollNo) {
        file >> ws;
        getline(file, s.name, ' ');
        file >> s.division;
        file >> ws;
        getline(file, s.address);
        if (s.rollNo == roll) {
            cout << "Found: " << s.rollNo << " " << s.name << " " << s.division << " " << s.address << "\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Student not found.\n";
    file.close();
}
 
void deleteStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    Student s;
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;
    bool found = false;
 
    while (file >> s.rollNo) {
        file >> ws;
        getline(file, s.name, ' ');
        file >> s.division;
        file >> ws;
        getline(file, s.address);
        if (s.rollNo != roll) {
            temp << s.rollNo << " " << s.name << " " << s.division << " " << s.address << "\n";
        } else {
            found = true;
        }
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found)
        cout << "Student deleted.\n";
    else
        cout << "Student not found.\n";
}
 
void editStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    Student s;
    int roll;
    cout << "Enter Roll No to edit: ";
    cin >> roll;
    bool found = false;
 
    while (file >> s.rollNo) {
        file >> ws;
        getline(file, s.name, ' ');
        file >> s.division;
        file >> ws;
        getline(file, s.address);
 
        if (s.rollNo == roll) {
            found = true;
            cout << "Enter new details:\n";
            cout << "Enter Name: "; cin.ignore(); getline(cin, s.name);
            cout << "Enter Division: "; cin >> s.division;
            cout << "Enter Address: "; cin.ignore(); getline(cin, s.address);
        }
        temp << s.rollNo << " " << s.name << " " << s.division << " " << s.address << "\n";
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found)
        cout << "Student updated.\n";
    else
        cout << "Student not found.\n";
}
 
int main() {
    int choice;
    do {
        cout << "\n1. Add\n2. Display All\n3. Search\n4. Delete\n5. Edit\n0. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: editStudent(); break;
            case 0: cout << "Exit\n"; break;
            default: cout << "Invalid\n";
        }
    } while (choice != 0);
    return 0;
}