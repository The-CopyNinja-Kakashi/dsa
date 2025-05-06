#include <iostream>
#include <vector>
using namespace std;
 
const int TABLE_SIZE = 10;
 
struct Student {
    int roll;
    int marks;
};
 
struct HashEntry {
    Student student;
    bool isOccupied = false;
};
 
class HashTable {
    HashEntry table[TABLE_SIZE];
 
public:
    void insertWithoutReplacement(Student s) {
        int index = s.roll % TABLE_SIZE;
        while (table[index].isOccupied) {
            index = (index + 1) % TABLE_SIZE;
        }
        table[index].student = s;
        table[index].isOccupied = true;
    }
 
    int searchWithoutReplacement(int roll) {
        int index = roll % TABLE_SIZE;
        int count = 0;
        while (table[index].isOccupied) {
            count++;
            if (table[index].student.roll == roll) {
                cout << "Found Roll: " << table[index].student.roll << ", Marks: "
                     << table[index].student.marks << " in " << count << " comparisons\n";
                return index;
            }
            index = (index + 1) % TABLE_SIZE;
        }
        cout << "Not found in " << count << " comparisons\n";
        return -1;
    }
 
    void clearTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = HashEntry();
        }
    }
 
    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].isOccupied)
                cout << i << " => Roll: " << table[i].student.roll 
                     << ", Marks: " << table[i].student.marks << '\n';
            else
                cout << i << " => Empty\n";
        }
    }
};
 
int main() {
    HashTable ht;
    vector<Student> students = {
        {31, 85}, {13, 90}, {14, 78}, {51, 88}, {16, 92},
        {71, 81}, {48, 75}, {19, 80}
    };
 
    cout << "Linear Probing with Chaining Without Replacement:\n";
    for (auto s : students)
        ht.insertWithoutReplacement(s);
 
    ht.display();
 
    // Example search
    ht.searchWithoutReplacement(71);
 
    return 0;
}
 
 