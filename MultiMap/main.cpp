#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <tuple>

using namespace std;

class Stack{
private:
    string *pointer_;
    int size_;
    int inUse_;

public:
    Stack(int n = 4) : size_(n){
        inUse_ = 0;
        pointer_ = new string[n];
    }

    ~Stack(){
        delete[] pointer_;
    }

    string pop(){
        inUse_--;
        return pointer_[inUse_];
    }

    void push(string &value){
        if (size_ == inUse_){
            auto *new_pointer_ = new string[size_*2];

            for (int i = 0; i < size_; i++){
                new_pointer_[i] = pointer_[i];
            }
            size_*=2;
            swap(pointer_, new_pointer_);
            delete[] new_pointer_;
        }
        pointer_[inUse_] = value;
        inUse_++;
    }

    void del(string &value){
        for (int i = 0; i<inUse_-1; i++){
            if (pointer_[i] == value){
                swap(pointer_[i],pointer_[i+1]);
            }
        }
        if (pointer_[inUse_-1] == value) {
            pop();
        }
    }

    void print(){
        for (int i = 0; i<inUse_; i++){
            cout << pointer_[i] << ' ';
        }
        cout << endl;
    }

    int getSize(){
        return inUse_;
    }

    string get(int pos){
        cout << "size " << inUse_ << endl;
        return pointer_[pos];
    }
};

struct Node {
    string key_;
    Node *next_;
    Node *prev_;
    vector<string> values_;
    int size_;

    Node(string &key, string &value) : key_(key),
                                       next_(nullptr),
                                       prev_(nullptr),
                                       size_(1){
        values_.push_back(value);
    }

    void insert(string &value){
        for (int i=0; i<size_; i++){
            if (values_[i] == value){
                return;
            }
        }
        values_.push_back(value);
        size_++;
//        cout << size_ << endl;
    }

    void del(string &value){
        for (int i = 0; i<size_-1; i++){
            if (values_[i] == value){
                swap(values_[i],values_[size_-1]);
                break;
            }
        }
        if (values_[size_-1] == value) {
            values_.pop_back();
            size_--;
        }
    }

    vector<string> get(){
        return values_;
    }

    int getSize(){
        cout << size_ << endl;
        return size_;
    }

    bool isEmpty(){
        return size_ == 0;
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

    pair<int, vector<string>> get(Node *node, string &key) {
        if (!node) {
            return make_pair(0, vector<string>(0));
        } else if (node->key_ == key) {
            return make_pair(node->getSize(), node->get());
        } else return (get(node->next_, key));
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
//                    cout << node->key_ << ',' << node->value_ << "->";
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
            pair<int, vector<string>> elem = set.get(set.getHead(h), key);
            fout << elem.first << ' ';
            for (int i = 0; i<elem.first; i++) {
                fout << elem.second[i] << ' ';
            }
            fout << endl;
        } else if (command == "deleteall") {
            int h = set.hash_f(key);
            set.delAll(set.getHead(h), key);
        }
    }
    return 0;
}