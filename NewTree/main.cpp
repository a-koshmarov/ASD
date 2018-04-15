#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Node{
    int value_;
    Node *left_;
    Node *right_;
    Node *parent_;

};

class Tree{
public:
    Node *minimum(Node *node) {
        if (!node) return NULL;

        while (node->left_) {
            node = node->left_;
        }
        return node;
    }

    Node *maximum(Node *node) {
        if (!node) return NULL;

        while (node->right_) {
            node = node->right_;
        }
        return node;
    }

    Node *search(Node *node, int value){
        if (!node) return NULL;

        if (value == node->value_) return node;

        if(value < node->value_){
            return search(node->left_, value);
        } else {
            return search(node->right_, value);
        }
    }

    Node *newNode(int value){
        Node *node = new Node;
        node->value_ = value;
        node->left_ = NULL;
        node->right_ = NULL;
        node->parent_ = NULL;
    }

    void insert(Node *root_t, int value){
        if (!root) {
            root = newNode(value);
        } else if (root_t->value_ < value) {
            if (!root_t->right_) {
//                cout << value << " is bigger then " << root->value_ << endl;
                root_t->right_ = newNode(value);
                root_t->right_->parent_ = root_t;
//                cout << "value is " << root_t->right_->value_ << " root is " << root_t->value_ << endl;
            } else {
                insert(root_t->right_, value);
            }
        } else {
            if (!root_t->left_) {
//                cout << value << " is smaller then " << root->value_ << endl;
                root_t->left_ = newNode(value);
                root_t->left_->parent_ = root_t;
//                cout << "value is " << root_t->left_->value_ << " root is " << root_t->value_ << endl;
            } else {
                insert(root_t->left_, value);
            }
        }
    }

    bool exists(int value){
        if (!root) return NULL;
        Node *node = search(root, value);

        return (node!=NULL);
    }

    Node *remNode(Node *node, Node *parent, int value){
        if (value < node->value_){
            if (node->left_)
                return remNode(node->left_, node, value);
            else
                return NULL;
        } else if (value > node->value_){
            if (node->right_)
                return remNode(node->right_, node, value);
            else
                return NULL;
        } else {
            if (node->left_&& node->right_){
                node->value_ = minimum(node->right_)->value_;
                return remNode(node->right_, node, node->value_);
            } else if (parent->left_ == node) {
                if (node->left_) {
                    parent->left_ = node->left_;
                } else {
                    parent->left_ = node->right_;
                }
                return node;
            } else if (parent->right_ == node){
                if (node->left_) {
                    parent->right_ = node->left_;
                } else {
                    parent->right_ = node->right_;
                }
                return node;
            }
        }
    }

    bool remove(int value){
        if (!root) return NULL;

        if (root->value_ == value){
            Node *node = newNode(0);
            node->left_ = root;

            Node *rNode = remNode(root, node, value);
            root = node->left_;

            if (rNode) {
                delete rNode;
                return true;
            } else {
                return false;
            }
        } else {
            Node *rNode = remNode(root, NULL, value);
            if (rNode) {
                delete rNode;
                return true;
            } else {
                return false;
            }
        }
    }

    Node *successor(int value){
        if (!root) return NULL;
        Node *node = search(root, value);


        if (node) {
//            cout << "val i " << node->value_ << endl;
//            cout << "parnt " << node->parent_->value_ << endl;
            if (node->right_){
                return minimum(node->right_);
            } else if (root == node) {
                return NULL;
            }

            Node *p_node = node->parent_;
//            cout << "par i " << p_node->value_ << endl;

            while (p_node && node == p_node->right_){
                node = p_node;

                if (p_node != root){
                    p_node = p_node->parent_;
                } else {
                    return NULL;
                }
            }
            if (exists(p_node->value_))
                return p_node;
            else
                return NULL;
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

    Node *ancestor(int value){
        if (!root) return NULL;
        Node *node = search(root, value);

        if (node) {
            if (node->left_){
                return maximum(node->left_);
            } else if (root == node) {
                return NULL;
            }

            Node *p_node = node->parent_;

            while (p_node && node == p_node->left_){
                node = p_node;

                if (p_node != root){
                    p_node = p_node->parent_;
                } else {
                    return NULL;
                }
            }
            if (exists(p_node->value_))
                return p_node;
            else
                return NULL;
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

    void add(int value){
        insert(root, value);
    }


private:
    Node *root = NULL;
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

        if (command == "insert" && !tree.exists(num)) {
            tree.add(num);
        } else if (command == "delete") {
            tree.remove(num);
        } else if (command == "exists") {
            if (tree.exists(num)) {
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
//            tree.getParent(num);
        }
    }
    fin.close();
    fout.close();
    return 0;
}