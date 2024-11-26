#include <iostream>
using namespace std;

// Define a Node structure for the tree
struct Node {
    int key;
    Node *left;
    Node *right;

    Node(int value) : key(value), left(nullptr), right(nullptr) {}
};

// Class for Binary Search Tree (BST)
class BinaryTree {
    Node *root;

    // Utility function to insert a new key in the tree
    Node *insert(Node *node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }

        return node;
    }

    // Utility function to search for a key in the tree
    Node *search(Node *node, int key) {
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return search(node->left, key);
        }

        return search(node->right, key);
    }

    // Utility function to print the tree (in-order traversal)
    void inOrderTraversal(Node *node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->key << " ";
            inOrderTraversal(node->right);
        }
    }

    // Utility function to find the minimum value node
    Node* findMin(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Utility function to delete a node from the tree
    Node* deleteNode(Node* node, int key) {
        if (node == nullptr) return node;

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }

public:
    BinaryTree() : root(nullptr) {}

    // Function to insert a key in the tree
    void insert(int key) {
        root = insert(root, key);
    }

    // Function to search for a key in the tree
    void search(int key) {
        Node *result = search(root, key);
        if (result != nullptr) {
            cout << "Element " << key << " found in the tree." << "\n";
        } else {
            cout << "Element " << key << " not found in the tree." << "\n";
        }
    }

    // Function to delete a key from the tree
    void deleteKey(int key) {
        root = deleteNode(root, key);
        cout << "Deleted key: " << key << "\n";
    }

    // Function to print the tree
    void printTree() {
        inOrderTraversal(root);
        cout << "\n";
    }
};

int main() {
    BinaryTree tree;

    // Insert elements into the tree
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    cout << "Initial tree (in-order traversal):" << endl;
    tree.printTree();

    // Search for elements in the tree
    cout << "\nSearching for elements:" << endl;
    tree.search(40);
    tree.search(90);

    // Delete a node from the tree
    cout << "\nDeleting nodes:" << endl;
    tree.deleteKey(20);
    tree.printTree();
    tree.deleteKey(30);
    tree.printTree();
    tree.deleteKey(50);
    tree.printTree();

    return 0;
}

