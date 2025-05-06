#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

const int MAX = 100;

struct HuffmanNode {
    char ch;
    int freq;
    int left, right;
};

HuffmanNode tree[MAX];
int nC = 0;

struct Compare {
    bool operator()(int a, int b) {
        return tree[a].freq > tree[b].freq;
    }
};

//  Build Huffman Tree
int buildHuffmanTree(unordered_map<char, int>& freqMap) {
    priority_queue<int, vector<int>, Compare> pq;

    for (auto& pair : freqMap) {
        tree[nC] = {pair.first, pair.second, -1, -1};
        pq.push(nC++);
    }

    while (pq.size() > 1) {
        int left = pq.top(); pq.pop();
        int right = pq.top(); pq.pop();

        tree[nC] = {'\0', tree[left].freq + tree[right].freq, left, right};
        pq.push(nC++);
    }

    return pq.top(); // root index
}

// ✅ Generate Huffman Codes
void generateCodes(int node, string code, unordered_map<char, string>& huffmanCodes) {
    if (node == -1) return;

    if (tree[node].ch != '\0') {
        huffmanCodes[tree[node].ch] = code;
        return;
    }

    generateCodes(tree[node].left, code + "0", huffmanCodes);
    generateCodes(tree[node].right, code + "1", huffmanCodes);
}

// ✅ Encode
string encode(string text, unordered_map<char, string>& huffmanCodes) {
    string encoded = "";
    for (char ch : text)
        encoded += huffmanCodes[ch];
    return encoded;
}

// ✅ Decode
string decode(string encodedStr, int root) {
    string decoded = "";
    int current = root;

    for (char bit : encodedStr) {
        current = (bit == '0') ? tree[current].left : tree[current].right;

        if (tree[current].ch != '\0') {
            decoded += tree[current].ch;
            current = root;
        }
    }

    return decoded;
}

// ✅ Main
int main() {
    unordered_map<char, int> freqMap = {
        {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4},
        {'e', 5}, {'f', 6}, {'g', 7}, {'h', 8}
    };

    string text;
    cout << "Enter a string (only using characters a-h): ";
    cin >> text;

    int root = buildHuffmanTree(freqMap);

    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    cout << "\nHuffman Codes:\n";
    for (auto& pair : huffmanCodes)
        cout << pair.first << ": " << pair.second << endl;

    string encoded = encode(text, huffmanCodes);
    cout << "\nEncoded String: " << encoded << endl;

    string decoded = decode(encoded, root);
    cout << "Decoded String: " << decoded << endl;

    return 0;
}
