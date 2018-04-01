#include <iostream>
#include <fstream>

using namespace std;

class Node {
public:
    int value_;
    Node *left_;
    Node *right_;
    Node *parent_;

    Node(int val) : value_(val) {
        left_ = NULL;
        right_ = NULL;
        parent_ = NULL;
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
                root->right_->parent_ = root;
            } else {
                add(root->right_, value);
            }
        } else {
            if (!root->left_) {
//                cout << value << " is smaller then " << root->value_ << endl;
                root->left_ = new Node(value);
                root->left_->parent_ = root;
            } else {
                add(root->left_, value);
            }
        }
    }

    Node *search(Node *root, int value) {
        while (root->value_ != value) {
            if (value < root->value_) {
                if (root->left_ != NULL) {
                    root = root->left_;
                } else {
                    return NULL;
                }
            } else if (root->right_ != NULL) {
                root = root->right_;
            } else {
                return NULL;
            }
        }
        return root;
    }

    Node *minimum(Node *root) {
        while (root->left_ != NULL) {
            root = root->left_;
        }
        return root;
    }

    Node *maximum(Node *root) {
        while (root->right_ != NULL) {
            root = root->right_;
        }
        return root;
    }

    Node *successor(int value) {
        Node *node = search(root, value);
        if (node) {
            if (node->right_ != NULL) {
                return minimum(node->right_);
            }

            Node *p_node = node->parent_;

            while (p_node != NULL && node == p_node->right_) {
                node = p_node;
                p_node = p_node->parent_;
            }

//        delete node;
            return p_node;
        } else {
            int min = 1000000001;
            node = root;
            int n;
            while (node) {
                if (node->value_ > value) {
                    node = node->left_;
                } else {
                    if (abs(node->value_ - value) < min) {
                        min = abs(node->value_ - value);
                        n = node->value_;
                    }
                    node = node->right_;
                }
            }
            if (min < 1000000001) {
                return (successor(n));
            } else {
                Node *t = minimum(root);
                if (t->value_ > value) {
                    return t;
                }
            }
        }
    }

    Node *ancestor(int value) {
        Node *node = search(root, value);

        if (node) {
            if (node->left_ != NULL) {
                return maximum(node->left_);
            }

            Node *p_node = node->parent_;

            while (p_node != NULL && node == p_node->left_) {
                node = p_node;
                p_node = p_node->parent_;
            }

//        delete node;
            return p_node;
        } else {
            int min = 1000000001;
            node = root;
            int n;
            while (node) {
                if (node->value_ < value) {
                    node = node->right_;
                } else {
                    if (abs(node->value_ - value) < min) {
                        min = abs(node->value_ - value);
                        n = node->value_;
                    }
                    node = node->left_;
                }
            }
            if (min < 1000000001) {
                return (ancestor(n));
            } else {
                Node *t = maximum(root);
                if (t->value_ < value) {
                    return t;
                }
            }
        }
    }

    Node *deleteNode(Node *root, int value) {
        if (!root) return root;

        if (value < root->value_) {
            root->left_ = deleteNode(root->left_, value);
        } else if (value > root->value_) {
            root->right_ = deleteNode(root->right_, value);
        } else {
            if (root->left_ == NULL) {
                Node *node = root->right_;
                node->parent_ = root->parent_;
                delete root;
                return node;
            } else if (root->right_ == NULL) {
                Node *node = root->left_;
                node->parent_ = root->parent_;
                delete root;
                return node;
            }

            Node *node = minimum(root->right_);
            root->value_ = node->value_;
            root->right_ = deleteNode(root->right_, node->value_);
        }
        return root;
    }

public:
    void newNode(int value) {
        if (root) {
            add(root, value);
        } else {
//            cout << "no root" << endl;
            root = new Node(value);
//            cout << "root is " << root->value_ << endl;
        }
    }

    int treeSearch(int value) {
        if (search(root, value)) {
            return 1;
        } else return 0;
    }

    ostream &treeSuccessor(int value, ostream &s) {
        Node *n = successor(value);
        if (n) {
            s << n->value_ << endl;
        } else {
            s << "none" << endl;
        }
        return s;
    }

    ostream &treeAncestor(int value, ostream &s) {
        Node *n = ancestor(value);
        if (n) {
            s << n->value_ << endl;
        } else {
            s << "none" << endl;
        }
        return s;
    }

    void getRoot() {
        cout << root->value_;
    }

    void getParent(int num) {
        Node *node = search(root, num);

        cout << node->parent_->value_ << endl;
    }

    int treeDelete(int value) {
        Node *node = deleteNode(root, value);
    }

};

int main() {
    Tree tree;
    string command;
    int num;

    ifstream fin("bstsimple.in");
    ofstream fout("bstsimple.out");

    while (true) {
        fin >> command;
        fin >> num;
        if (fin.eof()) break;

        if (command == "insert") {
            tree.newNode(num);
        } else if (command == "delete") {
            tree.treeDelete(num);
        } else if (command == "exists") {
            if (tree.treeSearch(num)) {
                fout << "true" << endl;
            } else {
                fout << "false" << endl;
            }
        } else if (command == "next") {
            tree.treeSuccessor(num, fout);
        } else if (command == "prev") {
            tree.treeAncestor(num, fout);
        }
    }

    fin.close();
    fout.close();
    return 0;

}