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
    vector<string> commands;
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
            addKey(key);
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
            addKey(key);
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
                    delKey(key);
                    delete node;
                } else if (node->next_ == nullptr) {
                    node->prev_->next_ = nullptr;
                    delKey(key);
                    delete node;
                } else if (node->prev_ == nullptr) {
                    node->next_->prev_ = nullptr;
                    data_[hash] = node->next_;
                    delKey(key);
                    delete node;
                } else {
                    node->next_->prev_ = node->prev_;
                    node->prev_->next_ = node->next_;
                    delKey(key);
                    delete node;
                }
            } else {
                del(node->next_, key);
            }
        }
    }

    void addKey(string &key){
        commands.push_back(key);
    }

    void delKey(string &key){
        for (int i = 0; i<commands.size()-1; i++){
            if (commands[i] == key){
                swap(commands[i], commands[i+1]);
            }
        }
        if (commands[commands.size()-1] == key){
            commands.pop_back();
        }
    }

    string getNext(string &key){
        if (commands.empty()){
            return "none";
        }

        for (int i = 0; i<commands.size()-1; i++){
            if (commands[i] == key){
                int h = hash_f(commands[i+1]);
                return get(getHead(h), commands[i+1]);
            }
        }
        return "none";
    }

    string getPrev(string &key){
        if (commands.empty()){
            return "none";
        }

        for (int i = 1; i<commands.size(); i++){
            if (commands[i] == key){
                int h = hash_f(commands[i-1]);
                return get(getHead(h), commands[i-1]);
            }
        }
        return "none";
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
            fout << set.getNext(key) << endl;
        } else if (command == "prev") {
            fout << set.getPrev(key) << endl;
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