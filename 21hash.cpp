#include <iostream>
using namespace std;
 
const int TABLE_SIZE = 10;
 
struct HashEntry {
    int pnr = -1;
    bool isOccupied = false;
};
 
class HashTable {
    HashEntry table[TABLE_SIZE];
 
public:
    void insertWithReplacement(int pnr) {
        int index = pnr % TABLE_SIZE;
 
        if (!table[index].isOccupied) {
            table[index].pnr = pnr;
            table[index].isOccupied = true;
        } else {
            int existingIndex = table[index].pnr % TABLE_SIZE;
            if (existingIndex != index) {
                // Replace and reinsert the existing element
                int temp = table[index].pnr;
                table[index].pnr = pnr;
                reinsert(temp);
            } else {
                // Linearly probe to find next empty slot
                int newIndex = (index + 1) % TABLE_SIZE;
                while (table[newIndex].isOccupied) {
                    newIndex = (newIndex + 1) % TABLE_SIZE;
                }
                table[newIndex].pnr = pnr;
                table[newIndex].isOccupied = true;
            }
        }
    }
 
    void reinsert(int pnr) {
        int index = pnr % TABLE_SIZE;
        while (table[index].isOccupied) {
            index = (index + 1) % TABLE_SIZE;
        }
        table[index].pnr = pnr;
        table[index].isOccupied = true;
    }
 
    void display() {
        cout << "\nFinal Hash Table:\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].isOccupied)
                cout << i << " => " << table[i].pnr << endl;
            else
                cout << i << " => Empty" << endl;
        }
    }
};
 
int main() {
    HashTable ht;
    int pnrs[] = {11, 21, 31, 34, 55, 52, 33};
 
    for (int pnr : pnrs) {
        ht.insertWithReplacement(pnr);
    }
 
    ht.display();
 
    return 0;
}