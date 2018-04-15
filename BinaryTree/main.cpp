#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Node {
    int value_;
    Node *left_ = NULL;
    Node *right_ = NULL;
    Node *parent_ = NULL;

    void print(int height = 0) {
        if (right_ != NULL)
            right_->print(height + 4);
        for (int i = 0; i < height; i++)
            cout << ' ';
        cout << value_ << endl;
        if (left_ != NULL)
            left_->print(height + 4);
    }
};

class Tree {
private:
    Node *root = NULL;

    void add(Node *root, int value) {
        if (root->value_ < value) {
            if (!root->right_) {
//                cout << value << " is bigger then " << root->value_ << endl;
                root->right_ = new Node;
                root->right_->value_ = value;
                root->right_->parent_ = root;
            } else {
                add(root->right_, value);
            }
        } else {
            if (!root->left_) {
//                cout << value << " is smaller then " << root->value_ << endl;
                root->left_ = new Node;
                root->left_->value_ = value;
                root->left_->parent_ = root;
            } else {
                add(root->left_, value);
            }
        }
    }

    Node *search(Node *root, int value) {
        while (root && root->value_ != value) {
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
        while (root && root->left_ != NULL) {
            root = root->left_;
        }
        return root;
    }

    Node *maximum(Node *root) {
        while (root && root->right_ != NULL) {
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
//            cout << p_node->value_ << endl;

            while (p_node != NULL && node == p_node->right_) {
                node = p_node;

                if (p_node != root){
                    p_node = p_node->parent_;
                } else {
                    return NULL;
                }
            }
            if (p_node) {
                if (search(root, p_node->value_)){
                    return p_node;
                } else {
                    return NULL;
                }
            }
            return p_node;
        } else {
            pair<bool, int> min = make_pair(false, 0);
            node = root;
            int n;
            while (node) {
                if (node->value_ > value) {
                    node = node->left_;
                } else {
                    if (!min.first) {
                        min.second = abs(node->value_ - value);
                        min.first = true;
                        n = node->value_;
                    } else if (abs(node->value_ - value) < min.second) {
                        min.second = abs(node->value_ - value);
                        n = node->value_;
                    }
                    node = node->right_;
                }
            }
            if (min.first) {
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
                if (p_node != root){
                    p_node = p_node->parent_;
                } else {
                    return NULL;
                }
            }
            if (p_node) {
                if (search(root, p_node->value_)){
                    return p_node;
                } else {
                    return NULL;
                }
            }
            return p_node;
        } else {
            pair<bool, int> min = make_pair(false, 0);
            node = root;
            int n;
            while (node) {
                if (node->value_ < value) {
                    node = node->right_;
                } else {
                    if (!min.first) {
                        min.second = abs(node->value_ - value);
                        min.first = true;
                        n = node->value_;
                    } else if (abs(node->value_ - value) < min.second) {
                        min.second = abs(node->value_ - value);
                        n = node->value_;
                    }
                    node = node->left_;
                }
            }
            if (min.first) {
                return (ancestor(n));
            } else {
                Node *t = maximum(root);
                if (t->value_ < value) {
                    return t;
                }
            }
        }
    }

    void deleteNode(int value) {
        Node *element  = search(root, value);

        if (element) {
            if ((element == root) && (element->left_ == NULL) && (element->right_ == NULL)) {
                root = NULL;
            } else if ((element == root) && (element->left_ == NULL)) {
                root = root->right_;
            } else if ((element == root) && (element->right_ == NULL)) {
                root = root->left_;
            } else if ((element->left_ == NULL) && (element->right_ == NULL)) {
                if (element == element->parent_->left_) {
                    element->parent_->left_ = NULL;
                } else {
                    element->parent_->right_ = NULL;
                }
            } else if (element->left_ == NULL) {
                if (element == element->parent_->left_) {
                    element->parent_->left_ = element->right_;
                    element->parent_->left_->parent_ = element->parent_;
                } else {
                    element->parent_->right_ = element->right_;
                    element->parent_->right_->parent_ = element->parent_;
                }
            } else if (element->right_ == NULL) {
                if (element == element->parent_->left_) {
                    element->parent_->left_ = element->left_;
                    element->parent_->left_->parent_ = element->parent_;
                } else {
                    element->parent_->right_ = element->left_;
                    element->parent_->right_->parent_ = element->parent_;
                }
            } else {
                Node *node = minimum(element->right_);
                int n = node->value_;
                deleteNode(n);
                element->value_ = n;
            }
        }
    }

public:
    void newNode(int value) {
        if (root) {
            add(root, value);
        } else {
//            cout << "no root" << endl;
            root = new Node;
            root->value_ = value;
//            cout << "root is " << root->value_ << endl;
        }
    }

    int treeSearch(int value) {
        if (search(root, value)) {
            return 1;
        } else return 0;
    }

    pair<bool, int> treeSuccessor(int value) {
        if (!root) return make_pair(false, 0);
        Node *n = successor(value);
        if (n) {
            return make_pair(true, n->value_);
        } else {
            return make_pair(false, 0);
        }
    }

    pair<bool, int> treeAncestor(int value) {
        if (!root) return make_pair(false, 0);
        Node *n = ancestor(value);
        if (n) {
            return make_pair(true, n->value_);
        } else {
            return make_pair(false, 0);
        }
    }

    void getRoot() {
        cout << root->value_;
    }

    void getParent(int num) {
        Node *node = search(root, num);

        if(node->parent_){
            cout << node->parent_->value_ << endl;
        } else {
            cout << "no parent" << endl;
        }

    }

    int treeDelete(int value) {
        deleteNode(value);
    }
    void print() {
        if (root != NULL)
            root->print();
        else
            printf("empty\n");
    }
};

int main() {
    Tree tree;
    string command;
    int num;
    long long ret;

    ifstream fin("bstsimple.in");
    ofstream fout("bstsimple.out");

    while (true) {
        fin >> command;
        fin >> num;
        if (fin.eof()) break;

        if (command == "insert" && !tree.treeSearch(num)) {
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
            bool ret1;
            int ret2;
            tie(ret1, ret2) = tree.treeSuccessor(num);
            if (ret1){
                fout << ret2 << endl;
            } else {
                fout << "none" << endl;
            }
        } else if (command == "prev") {
            bool ret1;
            int ret2;
            tie(ret1, ret2) = tree.treeAncestor(num);
            if (ret1){
                fout << ret2 << endl;
            } else {
                fout << "none" << endl;
            }
        } else if (command == "parent"){
            tree.getParent(num);
        }
    }
    fin.close();
    fout.close();
    return 0;

}