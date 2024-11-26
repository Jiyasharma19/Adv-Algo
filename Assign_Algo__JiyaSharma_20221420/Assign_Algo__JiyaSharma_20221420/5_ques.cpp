#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// BTreeNode class representing a node in the B-tree
class BTreeNode {
    vector<int> keys;  // Dynamic array of keys
    vector<BTreeNode *> children; // Dynamic array of child pointers
    int t; // Minimum degree
    bool leaf; // True if this node is a leaf

public:
    BTreeNode(int _t, bool _leaf);

    // Function to traverse all nodes in a subtree rooted with this node
    void traverse();

    // Function to search a key in the subtree rooted with this node
    BTreeNode *search(int k);

    // Insert a new key into the subtree rooted with this node
    void insertNonFull(int k);

    // Split the child y of this node
    void splitChild(int i, BTreeNode *y);

    friend class BTree;

private:
    int numKeys; // Number of keys in the node
};

// BTree class representing the B-tree
class BTree {
    BTreeNode *root; // Pointer to the root node
    int t;           // Minimum degree

public:
    BTree(int _t) : root(nullptr), t(_t) {}

    // Function to traverse the tree
    void traverse() {
        if (root != nullptr) root->traverse();
    }

    // Function to search a key in the tree
    BTreeNode *search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    // Insert a new key in the B-tree
    void insert(int k);
};

BTreeNode::BTreeNode(int t1, bool leaf1) : t(t1), leaf(leaf1), numKeys(0) {
    keys.resize(2 * t - 1);
    children.resize(2 * t);
}

void BTreeNode::traverse() {
    for (int i = 0; i < numKeys; i++) {
        if (!leaf && children[i] != nullptr)
            children[i]->traverse();
        cout << " " << keys[i];
    }
    if (!leaf && children[numKeys] != nullptr)
        children[numKeys]->traverse();
}

BTreeNode *BTreeNode::search(int k) {
    int i = 0;
    while (i < numKeys && k > keys[i])
        i++;

    if (i < numKeys && keys[i] == k) return this;

    if (leaf) return nullptr;

    return children[i] != nullptr ? children[i]->search(k) : nullptr;
}

void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->numKeys = 1;
    } else {
        if (root->numKeys == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->children[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k) i++;
            s->children[i]->insertNonFull(k);

            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

void BTreeNode::insertNonFull(int k) {
    int i = numKeys - 1;
    if (leaf) {
        keys.resize(numKeys + 1);
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        numKeys++;
    } else {
        while (i >= 0 && keys[i] > k) i--;
        if (children[i + 1] != nullptr && children[i + 1]->numKeys == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < k) i++;
        }
        if (children[i + 1] != nullptr)
            children[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->numKeys = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }

    y->numKeys = t - 1;

    children.resize(numKeys + 2);
    for (int j = numKeys; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = z;

    keys.resize(numKeys + 1);
    for (int j = numKeys - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    numKeys++;
}

int main() {
    BTree t(3); // A B-Tree with minimum degree 3
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "Traversal of the constructed B-Tree is:" << endl;
    t.traverse();
    cout << "\n";

    int k = 6;
    cout << "\nSearching for element: " << k << "\n";
    (t.search(k) != nullptr) ? cout << "Present\n" : cout << "Not Present\n";

    k = 15;
    cout << "\nSearching for element: " << k << "\n";
    (t.search(k) != nullptr) ? cout << "Present\n" : cout << "Not Present\n";

    return 0;
}
