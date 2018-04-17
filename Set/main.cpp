#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Stack{
private:
    int *pointer_;
    int size_;
    int inUse_;

public:
    Stack(int n = 4) : size_(n){
        inUse_ = 0;
        pointer_ = new int[n];
    }

    ~Stack(){
        delete[] pointer_;
    }

    int pop(){
        inUse_--;
        return pointer_[inUse_];
    }

    void push(int num){
        if (size_ == inUse_){
            int *new_pointer_ = new int[size_*2];

            for (int i = 0; i < size_; i++){
                new_pointer_[i] = pointer_[i];
            }
            size_*=2;
            swap(pointer_, new_pointer_);
            delete[] new_pointer_;
        }
        pointer_[inUse_] = num;
        inUse_++;
    }

    void del(int num){
        for (int i = 0; i<inUse_-1; i++){
            if (pointer_[i] == num){
                swap(pointer_[i],pointer_[i+1]);
            }
        }
        if (pointer_[inUse_-1] == num) {
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

    int get(int pos){
        return pointer_[pos];
    }
};

class HashSet {
private:
    int size_;
    vector<Stack*> data_;

public:
    HashSet(int size) : size_(size) {
        data_ = vector<Stack*>(size_);
        for (int i=0; i<size_; i++){
            data_[i] = new Stack;
        }
    }

    ~HashSet(){
        for (int i=0; i<size_; i++){
            delete data_[i];
        }
    }

    int hash_f(int value) {
        int prime = 100007;
        return abs(value) % prime;
    }

    void insert(int value) {
        int key = hash_f(value);

        if (!search(value)){
            data_[key]->push(value);
        }
    }

    bool search(int value) {
        int key = hash_f(value);

        for (int i = 0; i<data_[key]->getSize(); i++){
            if (data_[key]->get(i) == value){
                return true;
            }
        }
        return false;
    }

    void del(int value) {
        int key = hash_f(value);

        if(search(value)){
            data_[key]->del(value);
        }
    }
};

int main() {
    HashSet set(100007);
    string command;
    int num;

    ifstream fin("set.in");
    ofstream fout("set.out");

    while (true) {
        fin >> command >> num;
        if (fin.eof()) break;

        if (command == "insert") {
            set.insert(num);
        } else if (command == "delete") {
            set.del(num);
        } else if (command == "exists"){
            if (set.search(num)) {
                fout << "true" << endl;
            } else {
                fout << "false" << endl;
            }
        } else {
//            cout << set.getNum(num) << endl;
        }
    }

    fin.close();
    fout.close();

    return 0;
}