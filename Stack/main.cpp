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
    Stack(int n = 2) : size_(n){
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
};


int main() {
    int n;
    int com;

    ifstream infile("stack.in");
    ofstream outfile("stack.out");

    infile >> n;

    char command;
    Stack stack;
    Stack ans;

    for (int i = 0; i < n; i++) {
        infile >> command;
        if (command == '+'){
            infile >> com;
            stack.push(com);
        } else if (command == '-'){
            outfile << stack.pop() << endl;
        } else if (command == 'd'){
            infile >> com;
            stack.del(com);
        } else {
            stack.print();
        }
    }





//    for (int i=0; i<ans.size(); i++){
//        outfile << ans[i] << endl;
//    }
    infile.close();
    outfile.close();
    return 0;
}