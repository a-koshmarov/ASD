#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class Node {
public:
    int value_;
    Node *left_;
    Node *right_;

    Node(int val) : value_(val) {
        left_ = NULL;
        right_ = NULL;
    };
};

class Tree {
private:
    Node *root = NULL;

    void add(Node *root, int value) {
        if (root->value_ < value) {
            if (!root->right_) {
//                cout << value << " is bigger then " << root->value_ << endl;
                root->right_ = new Node(value);
            } else {
                add(root->right_, value);
            }
        } else {
            if (!root->left_) {
//                cout << value << " is smaller then " << root->value_ <<endl;
                root->left_ = new Node(value);
            } else {
                add(root->left_, value);
            }
        }
    }
public:
    void newNode(int value) {
        if (root) {
            add(root, value);
        } else {
//            cout << "no root" << endl;
            root = new Node(value);
        }
    }


    void deleteNode(){

    }

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}