#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
 
const int MAX = 100;
const char* FILENAME = "students.dat";
 
class Student {
public:
    int rollNo;
    char name[30];
    char division;
    char address[50];
 
    Student() {
        rollNo = -1;
        strcpy(name, "");
        division = '-';
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
        cout << "Enter Address: ";
        cin.ignore();
        cin.getline(address, 50);
    }
 
    void display() {
        if (rollNo != -1) {
            cout << "Roll No: " << rollNo << ", Name: " << name
                 << ", Division: " << division << ", Address: " << address << endl;
        }
    }
};
 
void addStudent() {
    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    Student s;
    s.input();
    int pos = s.rollNo;
    file.seekp(pos * sizeof(Student), ios::beg);
    file.write((char*)&s, sizeof(Student));
    file.close();
    cout << "Student added successfully.\n";
}
 
void searchStudent() {
    fstream file(FILENAME, ios::in | ios::binary);
    int roll;
    cout << "Enter Roll No to search: ";
    cin >> roll;
    Student s;
    file.seekg(roll * sizeof(Student), ios::beg);
    file.read((char*)&s, sizeof(Student));
    if (s.rollNo != -1)
        s.display();
    else
        cout << "Record not found.\n";
    file.close();
}
 
void deleteStudent() {
    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;
    Student s;
    file.seekg(roll * sizeof(Student), ios::beg);
    file.read((char*)&s, sizeof(Student));
    if (s.rollNo != -1) {
        Student blank;
        file.seekp(roll * sizeof(Student), ios::beg);
        file.write((char*)&blank, sizeof(Student));
        cout << "Record deleted.\n";
    } else {
        cout << "Record not found.\n";
    }
    file.close();
}
 
void editStudent() {
    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    int roll;
    cout << "Enter Roll No to edit: ";
    cin >> roll;
    Student s;
    file.seekg(roll * sizeof(Student), ios::beg);
    file.read((char*)&s, sizeof(Student));
    if (s.rollNo != -1) {
        cout << "Existing Record:\n";
        s.display();
        cout << "Enter new details:\n";
        s.input();
        file.seekp(roll * sizeof(Student), ios::beg);
        file.write((char*)&s, sizeof(Student));
        cout << "Record updated.\n";
    } else {
        cout << "Record not found.\n";
    }
    file.close();
}
 
void displayAll() {
    fstream file(FILENAME, ios::in | ios::binary);
    Student s;
    for (int i = 0; i < MAX; ++i) {
        file.seekg(i * sizeof(Student), ios::beg);
        file.read((char*)&s, sizeof(Student));
        if (s.rollNo != -1) s.display();
    }
    file.close();
}
 
int main() {
    // Pre-create a file with 100 empty student records
    fstream file(FILENAME, ios::out | ios::binary);
    Student s;
    for (int i = 0; i < MAX; ++i)
        file.write((char*)&s, sizeof(Student));
    file.close();
 
    int choice;
    do {
        cout << "\n--- Student Information System ---\n";
        cout << "1. Add Student\n2. Search Student\n3. Edit Student\n4. Delete Student\n5. Display All\n0. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: searchStudent(); break;
            case 3: editStudent(); break;
            case 4: deleteStudent(); break;
            case 5: displayAll(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid option!\n";
        }
    } while (choice != 0);
 
    return 0;
}
