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

    Node(string &key, string &value) : key_(key), value_(value) {
        next_ = nullptr;
        prev_ = nullptr;
    }
};

class HashMap {
private:
    int size_;
    vector<Node *> data_;

public:
    HashMap(int size) : size_(size) {
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
                del(node->next_, key);
            }
        }
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

    ifstream fin("map.in");
    ofstream fout("map.out");

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
        }



//        cin >> command;
//        if (command == "i") {
//            cin >> key;
//            cin >> value;
//            set.insert(key, value);
//        } else if (command == "d") {
//            cin >> key;
//            set.del(key);
//        } else if (command == "g") {
//            cin >> key;
//            int h = set.hash_f(key);
//            cout << set.get(set.getHead(h), key) << endl;
//        } else if (command == "p") {
//            set.print();
//        } else if (command == "stop") {
//            break;
//        }
    }

    fin.close();
    fout.close();

    return 0;
}