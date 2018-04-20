#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;


struct Node {
    string key_;
    string value_;
    Node *next_;
    Node *prev_;
    Node *nextKey_;
    Node *prevKey_;

    Node(string &key, string &value) : key_(key), value_(value) {
        next_ = nullptr;
        prev_ = nullptr;
        nextKey_ = nullptr;
        prevKey_ = nullptr;
    }
};

class HashMap {
private:
    int size_;
    vector<Node *> data_;
    Node *command;

public:
    HashMap(int size) : size_(size), command(nullptr) {
        data_ = vector<Node*>(size_);
    }

    ~HashMap() {
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
            addKey(data_[hash], key);
        } else {
            addElement(data_[hash], key, value);
        }

    }

    void addElement(Node *node, string &key, string &value) {
        if (node->key_ == key) {
            node->value_ = value;
        } else if (!node->next_) {
            node->next_ = new Node(key, value);
            node->next_->prev_ = node;
            addKey(node->next_, key);
        } else {
            addElement(node->next_, key, value);
        }
    }

    string get(Node *node, string &key) {
        if (!node) {
            return "none";
        } else if (node->key_ == key) {
            return (node->value_);
        } else return (get(node->next_, key));
    }

    void del(Node *node, string &key){
        int hash = hash_f(key);
        if (node) {
            if (node->key_ == key){
                if (node->prev_ == nullptr && node ->next_ == nullptr){
                    data_[hash] = nullptr;
                    delKey(node, key);
                    delete node;
                } else if (node->next_ == nullptr) {
                    node->prev_->next_ = nullptr;
                    delKey(node, key);
                    delete node;
                } else if (node->prev_ == nullptr) {
                    node->next_->prev_ = nullptr;
                    data_[hash] = node->next_;
                    delKey(node, key);
                    delete node;
                } else {
                    node->next_->prev_ = node->prev_;
                    node->prev_->next_ = node->next_;
                    delKey(node, key);
                    delete node;
                }
            } else {
                del(node->next_, key);
            }
        }
    }

    void addKey(Node* node, string &key){
        if (command){
            if (command->key_ == key){
                return;
            }
//            cout << command->value_ << ' ';
            node->prevKey_ = command;
//            cout << node->prevKey_->value_ << ' ';
            command->nextKey_ = node;
//            cout << command->nextKey_->value_ << ' ';
            command = node;
//            cout << command->value_ << endl;
        } else {
            command = node;
        }
    }

    void delKey(Node *node, string &key){
        if (node->prevKey_){
//            cout << node->prevKey_->value_ << ' ';
            node->prevKey_->nextKey_ = node->nextKey_;
//            cout << node->prevKey_->nextKey_->value_ << endl;
        }

        if (node->nextKey_){
//            cout << node->nextKey_->value_ << ' ';
            node->nextKey_->prevKey_ = node->prevKey_;
//            cout << node->nextKey_->prevKey_->value_ << endl;
        }

        if (node == command){
            command = node->prevKey_;
        }
    }

    string getNext(Node *node, string &key){
        if (!node) {
            return "none";
        } else if (node->key_ == key) {
            if (node->nextKey_){
                return (node->nextKey_->value_);
            } else return "none";
        } else return (getNext(node->next_, key));
    }

    string getPrev(Node *node, string &key){
        if (!node) {
            return "none";
        } else if (node->key_ == key) {
            if (node->prevKey_){
                return (node->prevKey_->value_);
            } else return "none";
        } else return (getPrev(node->next_, key));
    }
    void print() {
        for (int i = 0; i < size_; i++) {
            if (data_[i]) {
                Node *node = data_[i];
                while (node) {
                    cout << node->key_ << ',' << node->value_ << "->";
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
    HashMap set(100007);
    string command;
    string key, value;


    ifstream fin("linkedmap.in");
    ofstream fout("linkedmap.out");

    while (true) {
        fin >> command >> key;
        if (fin.eof()) break;

        if (command == "put") {
            fin >> value;
            set.insert(key, value);
        } else if (command == "delete") {
            int h = set.hash_f(key);
            set.del(set.getHead(h), key);
        } else if (command == "get") {
            int h = set.hash_f(key);
            fout << set.get(set.getHead(h), key) << endl;
        } else if (command == "next"){
            int h = set.hash_f(key);
            fout << set.getNext(set.getHead(h), key) << endl;
        } else if (command == "prev") {
            int h = set.hash_f(key);
            fout << set.getPrev(set.getHead(h), key) << endl;
        }



//        cin >> command;
//        if (command == "i") {
//            cin >> key;
//            cin >> value;
//            set.insert(key, value);
//        } else if (command == "d") {
//            cin >> key;
//            int h = set.hash_f(key);
//            set.del(set.getHead(h), key);
//        } else if (command == "g") {
//            cin >> key;
//            int h = set.hash_f(key);
//            cout << set.get(set.getHead(h), key) << endl;
//        } else if (command == "p") {
//            set.print();
//        } else if (command == "nx") {
//            cin >> key;
//            int h = set.hash_f(key);
//            cout << set.getNext(set.getHead(h), key) << endl;
//        } else if (command == "pr"){
//            cin >> key;
//            int h = set.hash_f(key);
//            cout << set.getPrev(set.getHead(h), key) << endl;
//        } else if (command == "stop"){
//            break;
//        }
    }

    fin.close();
    fout.close();

    return 0;
}