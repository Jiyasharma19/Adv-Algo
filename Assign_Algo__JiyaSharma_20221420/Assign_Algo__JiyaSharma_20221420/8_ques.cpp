#include <iostream>
#include <map>
#include <string>
using namespace std;

// Node class for Suffix Tree
class SuffixTreeNode {
public:
    map<char, SuffixTreeNode*> children;
    int start;
    int *end;
    SuffixTreeNode *suffixLink;

    SuffixTreeNode(int start, int *end) {
        this->start = start;
        this->end = end;
        suffixLink = nullptr;
    }

    int edgeLength() {
        return *end - start + 1;
    }
};

// Suffix Tree class
class SuffixTree {
    string text;
    SuffixTreeNode *root;
    SuffixTreeNode *activeNode;
    int activeEdge;
    int activeLength;
    int remainingSuffixCount;
    int leafEnd;
    int *rootEnd;
    int *splitEnd;
    int size;

public:
    SuffixTree(const string &text) {
        this->text = text;
        size = text.size();
        rootEnd = new int(-1);
        root = new SuffixTreeNode(-1, rootEnd);
        activeNode = root;
        activeEdge = -1;
        activeLength = 0;
        remainingSuffixCount = 0;
        leafEnd = -1;
        buildSuffixTree();
    }

    ~SuffixTree() {
        deleteTree(root);
    }

    void buildSuffixTree() {
        for (int i = 0; i < size; i++) {
            extendSuffixTree(i);
        }
        cout << "Suffix tree built successfully." << endl;
    }

    void extendSuffixTree(int pos) {
        leafEnd = pos;
        remainingSuffixCount++;
        SuffixTreeNode *lastNewNode = nullptr;

        while (remainingSuffixCount > 0) {
            if (activeLength == 0) {
                activeEdge = pos;
            }

            if (activeNode->children.find(text[activeEdge]) == activeNode->children.end()) {
                activeNode->children[text[activeEdge]] = new SuffixTreeNode(pos, &leafEnd);
                if (lastNewNode != nullptr) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = nullptr;
                }
            } else {
                SuffixTreeNode *next = activeNode->children[text[activeEdge]];
                int edgeLength = next->edgeLength();
                if (activeLength >= edgeLength) {
                    activeEdge += edgeLength;
                    activeLength -= edgeLength;
                    activeNode = next;
                    continue;
                }

                if (text[next->start + activeLength] == text[pos]) {
                    if (lastNewNode != nullptr && activeNode != root) {
                        lastNewNode->suffixLink = activeNode;
                        lastNewNode = nullptr;
                    }
                    activeLength++;
                    break;
                }

                splitEnd = new int(next->start + activeLength - 1);
                SuffixTreeNode *split = new SuffixTreeNode(next->start, splitEnd);
                activeNode->children[text[activeEdge]] = split;

                split->children[text[pos]] = new SuffixTreeNode(pos, &leafEnd);

                next->start += activeLength;
                split->children[text[next->start]] = next;

                if (lastNewNode != nullptr) {
                    lastNewNode->suffixLink = split;
                }

                lastNewNode = split;
            }

            remainingSuffixCount--;
            if (activeNode == root && activeLength > 0) {
                activeLength--;
                activeEdge = pos - remainingSuffixCount + 1;
            } else if (activeNode != root) {
                activeNode = activeNode->suffixLink;
            }
        }
    }

    void printTree() {
        cout << "\nSuffix Tree Structure:\n";
        printTree(root, 0);
    }

    void printTree(SuffixTreeNode *node, int height) {
        if (node == nullptr) return;
        for (auto &child : node->children) {
            int start = child.second->start;
            int end = *(child.second->end);
            cout << string(height, ' ') << "+-- " << text.substr(start, end - start + 1) << endl;
            printTree(child.second, height + 4);
        }
    }

private:
    void deleteTree(SuffixTreeNode *node) {
        if (node == nullptr) return;
        for (auto &child : node->children) {
            deleteTree(child.second);
        }
        delete node->end;
        delete node;
    }
};

int main() {
    string text = "xabxac";
    text += "$"; // Add unique end character to the string
    SuffixTree tree(text);
    tree.printTree();
    return 0;
}

/*
Time Complexity Analysis:
1. Building the Suffix Tree: O(n), where n is the length of the input string. This is achieved by Ukkonen's algorithm, which ensures linear time complexity for suffix tree construction.
2. Space Complexity: O(n * |Σ|), where |Σ| is the alphabet size. The space complexity is determined by the number of nodes and edges in the suffix tree.
*/