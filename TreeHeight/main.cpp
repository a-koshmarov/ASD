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
//    Node(int val, Node left, Node right){
//        value_ = val;
//        left_ = left;
//        right_ = right;
//    }
};

class Tree {
public:
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

    void newNode(int value) {
        if (root) {
            add(root, value);
        } else {
//            cout << "no root" << endl;
            root = new Node(value);
        }
    }

    int height(Node *root) {
        if (!root) {
            return 0;
        }
        return 1 + max(height(root->left_), height(root->right_));
    }
};


int main() {
    Tree tree;
    int n, value, left, right;
    ifstream fin("height.in");
    ofstream fout("height.out");

    fin >> n;

    for (int i = 0; i < n; i++) {
        fin >> value >> left >> right;
        tree.newNode(value);
//        cout << "root is " << tree.root->value_ << endl;
    }
    fout << tree.height(tree.root) << endl;

    fin.close();
    fout.close();
    return 0;
}