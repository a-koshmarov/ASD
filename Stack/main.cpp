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
        } else {
            outfile << stack.pop() << endl;
        }
    }





//    for (int i=0; i<ans.size(); i++){
//        outfile << ans[i] << endl;
//    }
    infile.close();
    outfile.close();
    return 0;
}