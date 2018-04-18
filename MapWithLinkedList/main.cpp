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
        data_ = vector<Node *>(size_);
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

    string get(string &key) {
        int hash = hash_f(key);
        Node *node = find(key);

        if (node) {
            return node->value_;
        } else {
            return "none";
        }
    }

    Node *find(string &key) {
        int hash = hash_f(key);

        Node *node = data_[hash];
        while (node) {
            if (node->key_ == key) {
                return node;
            } else {
                node = node->next_;
            }
        }
    }

    void del(string &key) {
        int hash = hash_f(key);
        Node *node = find(key);

        if (node) {
            if (node == data_[hash]) {
                data_[hash] = node->next_;
            }

            if (node->next_ != nullptr) {
                node->next_->prev_ = node->prev_;
            }

            if (node->prev_ != nullptr) {
                node->prev_->next_ = node->next_;
            }
        }
        delete node;
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
};


int main() {
    HashMap set(100007);
    string command;
    string key, value;

    ifstream fin("map.in");
    ofstream fout("map.out");

    while (true) {
//        fin >> command >> key;
//        if (fin.eof()) break;
//
//        if (command == "put") {
//            fin >> value;
//            set.insert(key, value);
//        } else if (command == "delete") {
//            set.del(key);
//        } else if (command == "get") {
//            fout << set.get(key) << endl;
//        }



        cin >> command;
        if (command == "i") {
            cin >> key;
            cin >> value;
            set.insert(key, value);
        } else if (command == "d") {
            cin >> key;
            set.del(key);
        } else if (command == "g") {
            cin >> key;
            cout << set.get(key) << endl;
        } else if (command == "p") {
            set.print();
        } else if (command == "stop") {
            break;
        }
    }

    fin.close();
    fout.close();

    return 0;
}