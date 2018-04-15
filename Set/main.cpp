#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct element {
    int value_;
    bool deleted_;

    element(int value) : value_(value), deleted_(false) {}
};

class HashSet {
private:
    int size_;
    vector<element *> data_;

public:
    HashSet(int size) : size_(size) {
        data_ = vector<element *>(size);
    }

    int hash_f(int value, int pos) {
        int prime = 200003;
        return ((abs(value) % prime) + pos) % size_;
    }

    void insert(int value) {
        int index = 0;
        while (index != size_) {
            int hash_pos = hash_f(value, index);

            if (data_[hash_pos] == nullptr) {
                data_[hash_pos] = new element(value);
                break;
            } else if (data_[hash_pos]->deleted_ && data_[hash_pos]->value_ == value) {
                data_[hash_pos]->deleted_ = false;
                break;
            } else if (data_[hash_pos]->value_ == value) {
                break;
            } else {
                index++;
            }
        }
    }

    int search(int value) {
        int index = 0;
        while (index != size_) {
            int hash_pos = hash_f(value, index);

            if (!data_[hash_pos]) break;

            if (!(data_[hash_pos]->deleted_) && data_[hash_pos]->value_ == value) {
                return hash_pos;
            } else {
                index++;
            }
        }
        return -1;
    }

    void del(int value) {
        int index = search(value);

        if (index != -1) {
            data_[index]->deleted_ = true;
        }
    }

    int getNum(int index){
        if (!data_[index]->deleted_){
            return data_[index]->value_;
        } else {
            return -1;
        }

    }


};

int main() {
    HashSet set(1000000);
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
            if (set.search(num) != -1) {
                fout << "true" << endl;
            } else {
                fout << "false" << endl;
            }
        } else {
            cout << set.getNum(num) << endl;
        }
    }

    fin.close();
    fout.close();

    return 0;
}