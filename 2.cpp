#include <iostream>
#include <vector>
#include <list>
using namespace std;
 
const int TABLE_SIZE = 101;
 
struct Entry {
    string word;
    string meaning;
    Entry(string w, string m) : word(w), meaning(m) {}
};
 
class HashTable {
    vector<list<Entry>> table;
 
    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % TABLE_SIZE;
        }
        return hash;
    }
 
public:
    HashTable() : table(TABLE_SIZE) {}
 
    void insert(const string& word, const string& meaning) {
        int idx = hashFunction(word);
        for (auto& entry : table[idx]) {
            if (entry.word == word) {
                entry.meaning = meaning;
                return;
            }
        }
        table[idx].emplace_back(word, meaning);
    }
 
    bool search(const string& word, string& meaning) {
        int idx = hashFunction(word);
        for (auto& entry : table[idx]) {
            if (entry.word == word) {
                meaning = entry.meaning;
                return true;
            }
        }
        return false;
    }
};
 
int main() {
    HashTable dict;
 
    // Manually insert words and meanings
    dict.insert("apple", "a fruit");
    dict.insert("table", "an item of furniture");
    dict.insert("code", "a set of instructions");
    dict.insert("computer", "an electronic device");
    dict.insert("book", "a set of written pages");
 
    cout << "Dictionary loaded. Enter words to look up (type 'exit' to quit):\n";
 
    string word, meaning;
    while (true) {
        cout << "\nWord: ";
        cin >> word;
        if (word == "exit") break;
 
        if (dict.search(word, meaning)) {
            cout << "Meaning: " << meaning << endl;
        } else {
            cout << "Word not found in dictionary." << endl;
        }
    }
 
    return 0;
}