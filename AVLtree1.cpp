#include<iostream>
#include<string>
using namespace std;

class Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;
    int height;

public:
    Node(string k, string m) {
        keyword = k;
        meaning = m;
        left = right = nullptr;
        height = 1;
    }
    friend class AVLTree;
};

class AVLTree {
    Node* root;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        return y;
    }

    Node* insert(Node* node, string keyword, string meaning) {
        if (!node) return new Node(keyword, meaning);
        if (keyword < node->keyword)
            node->left = insert(node->left, keyword, meaning);
        else if (keyword > node->keyword)
            node->right = insert(node->right, keyword, meaning);
        else {
            cout << "Keyword already exists. Use update option.\n";
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);
        if (balance > 1 && keyword < node->left->keyword)
            return rightRotate(node);
        if (balance < -1 && keyword > node->right->keyword)
            return leftRotate(node);
        if (balance > 1 && keyword > node->left->keyword) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && keyword < node->right->keyword) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left)
            node = node->left;
        return node;
    }

    Node* deleteNode(Node* root, string keyword) {
        if (!root) return root;

        if (keyword < root->keyword)
            root->left = deleteNode(root->left, keyword);
        else if (keyword > root->keyword)
            root->right = deleteNode(root->right, keyword);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            } else {
                Node* temp = findMin(root->right);
                root->keyword = temp->keyword;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->keyword);
            }
        }

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->keyword << " : " << node->meaning << endl;
        inorder(node->right);
    }

    void reverseInorder(Node* node) {
        if (!node) return;
        reverseInorder(node->right);
        cout << node->keyword << " : " << node->meaning << endl;
        reverseInorder(node->left);
    }

    int search(Node* node, string keyword, int& comparisons) {
        if (!node) return 0;
        comparisons++;
        if (keyword == node->keyword) {
            cout << "Meaning: " << node->meaning << endl;
            return 1;
        }
        if (keyword < node->keyword)
            return search(node->left, keyword, comparisons);
        else
            return search(node->right, keyword, comparisons);
    }

    void update(Node* node, string keyword, string newMeaning) {
        if (!node) return;
        if (keyword == node->keyword) {
            node->meaning = newMeaning;
            cout << "Updated successfully.\n";
            return;
        }
        if (keyword < node->keyword)
            update(node->left, keyword, newMeaning);
        else
            update(node->right, keyword, newMeaning);
    }

public:
    AVLTree() {
        root = nullptr;
    }

    void insert(string keyword, string meaning) {
        root = insert(root, keyword, meaning);
    }

    void deleteKeyword(string keyword) {
        root = deleteNode(root, keyword);
    }

    void updateMeaning(string keyword, string newMeaning) {
        update(root, keyword, newMeaning);
    }

    void searchKeyword(string keyword) {
        int comparisons = 0;
        if (!search(root, keyword, comparisons))
            cout << "Keyword not found.\n";
        else
            cout << "Comparisons made: " << comparisons << endl;
    }

    void displayAscending() {
        inorder(root);
    }

    void displayDescending() {
        reverseInorder(root);
    }
};

int main() {
    AVLTree dict;
    int choice;
    string key, meaning;

    do {
        cout << "\n1. Add Keyword\n2. Delete Keyword\n3. Update Meaning\n4. Search Keyword\n5. Display Ascending\n6. Display Descending\n0. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> key;
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, meaning);
                dict.insert(key, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                cin >> key;
                dict.deleteKeyword(key);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                cin >> key;
                cout << "Enter new meaning: ";
                cin.ignore();
                getline(cin, meaning);
                dict.updateMeaning(key, meaning);
                break;
            case 4:
                cout << "Enter keyword to search: ";
                cin >> key;
                dict.searchKeyword(key);
                break;
            case 5:
                dict.displayAscending();
                break;
            case 6:
                dict.displayDescending();
                break;
        }
    } while (choice != 0);

    return 0;
}
