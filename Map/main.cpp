#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class Stack {
private:
    pair<string, string> *pointer_;
    int size_;
    int inUse_;

public:
    Stack(int n = 4) : size_(n) {
        inUse_ = 0;
        pointer_ = new pair<string, string>[n];
    }

    ~Stack() {
        delete[] pointer_;
    }

    pair<string, string> pop() {
        inUse_--;
        return pointer_[inUse_];
    }

    void push(string &key, string &value) {
        if (size_ == inUse_) {
            auto *new_pointer_ = new pair<string, string>[size_ * 2];

            for (int i = 0; i < size_; i++) {
                new_pointer_[i].first = pointer_[i].first;
                new_pointer_[i].second = pointer_[i].second;
            }
            size_ *= 2;
            swap(pointer_, new_pointer_);
            delete[] new_pointer_;
        }
        pointer_[inUse_].first = key;
        pointer_[inUse_].second = value;
        inUse_++;
    }

    void del(string &key) {
        for (int i = 0; i < inUse_-1; i++) {
            if (pointer_[i].first == key) {
                swap(pointer_[i], pointer_[inUse_-1]);
                break;
            }
        }
        if (pointer_[inUse_-1].first == key){
            pop();
        }
    }

    void print() {
        for (int i = 0; i < inUse_; i++) {
            cout << pointer_[i].first << ' ' << pointer_[i].second << endl;
        }
        cout << endl;
    }

    int getSize() {
        return inUse_;
    }

    string &get(int pos) {
        return pointer_[pos].first;
    }

    string &getVal(int pos){
        return pointer_[pos].second;
    }

    void setValue(int pos, string &value){
        pointer_[pos].second = value;
    }
};

class HashMap {
private:
    int size_;
    vector<Stack*> data_;

public:
    HashMap(int size) : size_(size) {
        data_ = vector<Stack *>(size_);
        for (int i = 0; i < size_; i++) {
            data_[i] = new Stack(4);
        }
    }

    ~HashMap() {
        for (int i = 0; i < size_; i++) {
            delete data_[i];
        }
    }

    int hash_f(string &key) {
        long long hash = 0;
        for (int i = 0; i < key.length(); i++) {
            hash += int(key[i]) * int(pow(31, i));
        }
        return hash % size_;
    }

    void insert(string &key, string &value) {
        int hash = hash_f(key);

        int pos = search(key);
        if (pos == -1){
            data_[hash]->push(key, value);
        } else {
            data_[hash]->setValue(pos, value);
        }
    }

    int search(string &key) {
        int hash = hash_f(key);

        for (int i = 0; i < data_[hash]->getSize(); i++) {
            if (data_[hash]->get(i) == key) {
                return i;
            }
        }
        return -1;
    }

    void del(string &key) {
        int hash = hash_f(key);

        if (search(key)!=-1) {
            data_[hash]->del(key);
        }
    }

    string &get(string &key){
        int hash = hash_f(key);
        int pos = search(key);

        if (pos!=-1){
            return data_[hash]->getVal(pos);
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
        fin >> command >> key;
//        cout << command << ' ' << key << endl;
        if (fin.eof()) break;

        if (command == "put") {
            fin >> value;
            set.insert(key, value);
        } else if (command == "delete") {
            set.del(key);
        } else if (command == "get") {
            if (set.search(key)!=-1) {
                fout << set.get(key) << endl;
            } else {
                fout << "none" << endl;
            }
        }
    }

    fin.close();
    fout.close();

    return 0;
}