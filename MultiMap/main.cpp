#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <tuple>

using namespace std;

struct TreeNode {
    string value_;
    TreeNode *left_ = nullptr;
    TreeNode *right_ = nullptr;
    TreeNode *parent_ = nullptr;

    void print(int height = 0) {
        if (right_ != nullptr)
            right_->print(height + 4);
        for (int i = 0; i < height; i++)
            cout << ' ';
        cout << value_ << endl;
        if (left_ != nullptr)
            left_->print(height + 4);
    }
};

class Tree {
private:
    TreeNode *root;
    int size_;

    void add(TreeNode *root, string &value) {
        if (root->value_ == value) return;
        if (root->value_ < value) {
            if (!root->right_) {
//                cout << value << " is bigger then " << root->value_ << endl;
                root->right_ = new TreeNode;
                root->right_->value_ = value;
                root->right_->parent_ = root;
                size_++;
            } else {
                add(root->right_, value);
            }
        } else {
            if (!root->left_) {
//                cout << value << " is smaller then " << root->value_ << endl;
                root->left_ = new TreeNode;
                root->left_->value_ = value;
                root->left_->parent_ = root;
                size_++;
            } else {
                add(root->left_, value);
            }
        }
    }

    TreeNode *search(TreeNode *root, string &value) {
        while (root && root->value_ != value) {
            if (value < root->value_) {
                if (root->left_ != nullptr) {
                    root = root->left_;
                } else {
                    return nullptr;
                }
            } else if (root->right_ != nullptr) {
                root = root->right_;
            } else {
                return nullptr;
            }
        }
        return root;
    }

    TreeNode *minimum(TreeNode *root) {
        while (root && root->left_ != nullptr) {
            root = root->left_;
        }
        return root;
    }

    void deleteNode(string &value) {
        TreeNode *element  = search(root, value);

        if (element) {
            if ((element == root) && (element->left_ == nullptr) && (element->right_ == nullptr)) {
                root = nullptr;
                size_--;
            } else if ((element == root) && (element->left_ == nullptr)) {
                root = root->right_;
                size_--;
            } else if ((element == root) && (element->right_ == nullptr)) {
                root = root->left_;
                size_--;
            } else if ((element->left_ == nullptr) && (element->right_ == nullptr)) {
                if (element == element->parent_->left_) {
                    element->parent_->left_ = nullptr;
                } else {
                    element->parent_->right_ = nullptr;
                }
                size_--;
            } else if (element->left_ == nullptr) {
                if (element == element->parent_->left_) {
                    element->parent_->left_ = element->right_;
                    element->parent_->left_->parent_ = element->parent_;
                } else {
                    element->parent_->right_ = element->right_;
                    element->parent_->right_->parent_ = element->parent_;
                }
                size_--;
            } else if (element->right_ == nullptr) {
                if (element == element->parent_->left_) {
                    element->parent_->left_ = element->left_;
                    element->parent_->left_->parent_ = element->parent_;
                } else {
                    element->parent_->right_ = element->left_;
                    element->parent_->right_->parent_ = element->parent_;
                }
                size_--;
            } else {
                TreeNode *node = minimum(element->right_);
                string n = node->value_;
                deleteNode(n);
                element->value_ = n;
            }
        }
    }

public:
    Tree() : root(nullptr), size_(0){}

    void newNode(string &value) {
        if (root) {
            add(root, value);
        } else {
//            cout << "no root" << endl;
            root = new TreeNode;
            root->value_ = value;
            size_++;
//            cout << "root is " << root->value_ << endl;
        }
    }

    int treeSearch(string &value) {
        if (search(root, value)) {
            return 1;
        } else return 0;
    }

    void getRoot() {
        cout << root->value_;
    }

    void getParent(string &value) {
        TreeNode *node = search(root, value);

        if(node->parent_){
            cout << node->parent_->value_ << endl;
        } else {
            cout << "no parent" << endl;
        }

    }

    void treeDelete(string &value) {
        deleteNode(value);
    }

    void print(TreeNode *node, ostream &s) {
        if (!node) return;

        if (node->left_){
            print(node->left_, s);
        }
        s << node->value_ << ' ';
        if (node->right_){
            print(node->right_, s);
        }
    }

    void treePrint(ostream &s){
        print(root, s);
    }

    int getSize(){
        return size_;
    }
};

struct Node {
    string key_;
    Node *next_;
    Node *prev_;
    Tree values_;

    Node(string &key, string &value) : key_(key),
                                       next_(nullptr),
                                       prev_(nullptr)
                                       {
        values_.newNode(value);
    }

    void insert(string &value){
        values_.newNode(value);
//        cout << size_ << endl;
    }

    void del(string &value){
        values_.treeDelete(value);;
    }


    bool isEmpty(){
        return values_.getSize() == 0;
    }

    void print(ostream &s){
        s << values_.getSize() << ' ';
        values_.treePrint(s);
        s << endl;
    }
};

class MultiMap {
private:
    int size_;
    vector<Node*> data_;

public:
    MultiMap(int size) : size_(size),
                         data_(vector<Node*>(size)) {
    }

    ~MultiMap() {
        for (int i = 0; i < data_.size(); i++) {
            delete data_[i];
        }
    }

    int hash_f(string &key) {
        long long hash = 0;
        for (int i = 0; i < key.length(); i++) {
            hash += int(key[i]) * int(pow(31, i));
        }
        return abs(hash) % size_;
    }

    void insert(string &key, string &value) {
        int hash = hash_f(key);

        if (data_[hash] == nullptr) {
            data_[hash] = new Node(key, value);
        } else {
            addElement(data_[hash], key, value);
        }
    }

    void addElement(Node *node, string &key, string &value) {
        if (node->key_ == key) {
            node->insert(value);
        } else if (!node->next_) {
            node->next_ = new Node(key, value);
            node->next_->prev_ = node;
        } else {
            addElement(node->next_, key, value);
        }
    }

    void get(Node *node, string &key, ostream &s) {
        if (!node) {
            s << 0 << endl;
        } else if (node->key_ == key) {
            node->print(s);
        } else get(node->next_, key, s);
    }

    void del(Node *node, string &key, string &value){
        int hash = hash_f(key);
        if (node) {
            if (node->key_ == key){
                node->del(value);
                if (node->isEmpty()){
                    if (node->prev_ == nullptr && node ->next_ == nullptr){
                        data_[hash] = nullptr;
                        delete node;
                    } else if (node->next_ == nullptr) {
                        node->prev_->next_ = nullptr;
                        delete node;
                    } else if (node->prev_ == nullptr) {
                        node->next_->prev_ = nullptr;
                        data_[hash] = node->next_;
                        delete node;
                    } else {
                        node->next_->prev_ = node->prev_;
                        node->prev_->next_ = node->next_;
                        delete node;
                    }
                }
            } else {
                del(node->next_, key, value);
            }
        }
    }

    void delAll(Node *node, string &key){
        int hash = hash_f(key);
        if (node) {
            if (node->key_ == key){
                if (node->prev_ == nullptr && node ->next_ == nullptr){
                    data_[hash] = nullptr;
                    delete node;
                } else if (node->next_ == nullptr) {
                    node->prev_->next_ = nullptr;
                    delete node;
                } else if (node->prev_ == nullptr) {
                    node->next_->prev_ = nullptr;
                    data_[hash] = node->next_;
                    delete node;
                } else {
                    node->next_->prev_ = node->prev_;
                    node->prev_->next_ = node->next_;
                    delete node;
                }
            } else {
                delAll(node->next_, key);
            }
        }
    }

    void print() {
        for (int i = 0; i < size_; i++) {
            if (data_[i]) {
                Node *node = data_[i];
                while (node) {
                    cout << node->key_<< "->";
                    node = node->next_;
                }
                cout << endl;
            }

        }
    }

    Node *getHead(int hash){
        return data_[hash];
    }
};


int main() {
    MultiMap set(100007);
    string command;
    string key, value, count;
    vector<string> elements;


    ifstream fin("multimap.in");
    ofstream fout("multimap.out");

    while (true) {
        fin >> command >> key;
        if (fin.eof()) break;

        if (command == "put") {
            fin >> value;
            set.insert(key, value);
        } else if (command == "delete") {
            fin >> value;
            int h = set.hash_f(key);
            set.del(set.getHead(h), key, value);
        } else if (command == "get") {
            int h = set.hash_f(key);
            set.get(set.getHead(h), key, fout);
        } else if (command == "deleteall") {
            int h = set.hash_f(key);
            set.delAll(set.getHead(h), key);
        }

//        cin >> command;
//        if (command == "p") {
//            cin >> key >> value;
//            set.insert(key, value);
//        } else if (command == "d") {
//            cin >> key >> value;
//            int h = set.hash_f(key);
//            set.del(set.getHead(h), key, value);
//        } else if (command == "g") {
//            cin >> key;
//            int h = set.hash_f(key);
//            set.get(set.getHead(h), key, cout);
//        } else if (command == "da") {
//            cin >> key;
//            int h = set.hash_f(key);
//            set.delAll(set.getHead(h), key);
//        } else if (command == "stop"){
//            break;
//        } else if (command == "pr"){
//            set.print();
//        }

    }
    return 0;
}