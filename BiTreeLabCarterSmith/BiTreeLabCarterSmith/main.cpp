#include <iostream>
#include <string>
using namespace std;

class BiTree {
private:
    struct Node {
        string data;
        Node* left;
        Node* right;
        Node(string val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Helper methods for recursive operations
    Node* addRecursive(Node* node, string data) {
        if (node == nullptr) {
            return new Node(data);
        }
        if (data < node->data) {
            node->left = addRecursive(node->left, data);
        }
        else if (data > node->data) {
            node->right = addRecursive(node->right, data);
        }
        return node;
    }

    Node* removeRecursive(Node* node, string data) {
        if (node == nullptr) return nullptr;

        if (data < node->data) {
            node->left = removeRecursive(node->left, data);
        }
        else if (data > node->data) {
            node->right = removeRecursive(node->right, data);
        }
        else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children
            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = removeRecursive(node->right, temp->data);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void printInOrder(Node* node) {
        if (node != nullptr) {
            printInOrder(node->left);
            cout << node->data << " ";
            printInOrder(node->right);
        }
    }

    void printReverseOrder(Node* node) {
        if (node != nullptr) {
            printReverseOrder(node->right);
            cout << node->data << " ";
            printReverseOrder(node->left);
        }
    }

    void printTree(Node* root, string indent, bool last) {
        // Print the tree in a 2D tree-like structure
        if (root != nullptr) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "     ";
            }
            else {
                cout << "L----";
                indent += "|    ";
            }
            cout << root->data << endl;
            printTree(root->left, indent, false);
            printTree(root->right, indent, true);
        }
    }

public:
    BiTree() : root(nullptr) {}

    void Add(string data) {
        root = addRecursive(root, data);
    }

    void Remove(string data) {
        root = removeRecursive(root, data);
    }

    void Print() {
        printInOrder(root);
        cout << endl;
    }

    void RPrint() {
        printReverseOrder(root);
        cout << endl;
    }

    void TPrint() {
        printTree(root, "", true);
    }
};

int main() {
    BiTree tree;
    // Add some example websites
    tree.Add("google.com");
    tree.Add("openai.com");
    tree.Add("stackoverflow.com");
    tree.Add("github.com");
    tree.Add("wikipedia.org");
    

    cout << "In Alphabetical Order:" << endl;
    tree.Print();

    cout << "In Reverse Alphabetical Order:" << endl;
    tree.RPrint();

    cout << "Tree Structure:" << endl;
    tree.TPrint();

    // Remove a website
    tree.Remove("openai.com");

    // Print updated tree
    tree.Print();

    return 0;
}
