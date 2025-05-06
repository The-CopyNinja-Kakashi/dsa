#include <iostream>
using namespace std;
 
struct Node {
    int data;
    Node *left, *right;
    bool lthread, rthread;
 
    Node(int val) {
        data = val;
        left = right = nullptr;
        lthread = rthread = true;
    }
};
 
class ThreadedBST {
    Node *root;
 
public:
    ThreadedBST() : root(nullptr) {}
 
    // Q7: Insert into a Threaded BST
    void insert(int key) {
        Node* ptr = root;
        Node* parent = nullptr;
 
        while (ptr != nullptr) {
            if (key == ptr->data) return; // Avoid duplicates
            parent = ptr;
 
            if (key < ptr->data) {
                if (!ptr->lthread)
                    ptr = ptr->left;
                else
                    break;
            } else {
                if (!ptr->rthread)
                    ptr = ptr->right;
                else
                    break;
            }
        }
 
        Node* newNode = new Node(key);
 
        if (parent == nullptr) {
            root = newNode;
        } else if (key < parent->data) {
            newNode->left = parent->left;   // Thread to inorder predecessor
            newNode->right = parent;        // Thread to parent (successor)
            parent->lthread = false;
            parent->left = newNode;
        } else {
            newNode->right = parent->right; // Thread to inorder successor
            newNode->left = parent;         // Thread to parent (predecessor)
            parent->rthread = false;
            parent->right = newNode;
        }
    }
 
    // Q7: Inorder traversal using threads
    void inorder() {
        Node* curr = root;
 
        // Go to leftmost node
        while (curr && !curr->lthread)
            curr = curr->left;
 
        while (curr) {
            cout << curr->data << " ";
            if (curr->rthread) {
                curr = curr->right; // Move to inorder successor via thread
            } else {
                curr = curr->right;
                while (curr && !curr->lthread)
                    curr = curr->left;
            }
        }
        cout << endl;
    }
 
    // Q8: Insert into a normal BST (no threads used)
    void insertNormal(Node*& node, int key) {
        if (!node) {
            node = new Node(key);
            node->lthread = node->rthread = false; // Important: normal BST has no threads
            return;
        }
 
        if (key < node->data)
            insertNormal(node->left, key);
        else if (key > node->data)
            insertNormal(node->right, key);
    }
 
    // Q8: Convert normal BST to Threaded BST
    void convertBSTtoThreaded(Node* root) {
        Node* prev = nullptr;
        convertUtil(root, prev);
        this->root = root;
    }
 
    // Overloaded inorder for Q8 (on passed root)
    void inorder(Node* curr) {
        // Go to leftmost
        while (curr && !curr->lthread)
            curr = curr->left;
 
        while (curr) {
            cout << curr->data << " ";
            if (curr->rthread) {
                curr = curr->right;
            } else {
                curr = curr->right;
                while (curr && !curr->lthread)
                    curr = curr->left;
            }
        }
        cout << endl;
    }
 
private:
    // Utility to convert BST to Threaded BST
    void convertUtil(Node* curr, Node*& prev) {
        if (!curr) return;
 
        convertUtil(curr->left, prev);
 
        // Set left thread
        if (!curr->left) {
            curr->left = prev;
            curr->lthread = true;
        } else {
            curr->lthread = false;
        }
 
        // Set right thread of previous node
        if (prev && !prev->right) {
            prev->right = curr;
            prev->rthread = true;
        } else if (prev) {
            prev->rthread = false;
        }
 
        prev = curr;
        convertUtil(curr->right, prev);
    }
};
 
 
int main() {
    ThreadedBST tbst;
 
    // Q7: Insert in Threaded BST and print
    tbst.insert(20);
    tbst.insert(10);
    tbst.insert(30);
    tbst.insert(5);
    tbst.insert(15);
 
    cout << "[Q7] Inorder Traversal of Threaded BST: ";
    tbst.inorder();
 
    // Q8: Insert into normal BST, then convert to threaded BST
    Node* normalRoot = nullptr;
    tbst.insertNormal(normalRoot, 40);
    tbst.insertNormal(normalRoot, 25);
    tbst.insertNormal(normalRoot, 60);
    tbst.insertNormal(normalRoot, 10);
    tbst.insertNormal(normalRoot, 30);
 
    tbst.convertBSTtoThreaded(normalRoot);
 
    cout << "[Q8] Inorder Traversal after converting Normal BST to Threaded BST: ";
    tbst.inorder(normalRoot);
 
    return 0;
}
 