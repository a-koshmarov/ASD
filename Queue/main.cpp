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
//        cout << "~Stack" << endl;
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

    int getInUse(){
        return inUse_;
    }
};

class Queue{
private:
    Stack left;
    Stack right;
public:
    Queue(){};
    ~Queue(){
//        cout << "~Queue" << endl;
    };

    void push(int num){
        left.push(num);
//        cout << "pushing " << num << "to left" << endl;
    }

    int pop(){
        if (right.getInUse() == 0){
            int inUse = left.getInUse();
            for (int i = 0; i<inUse; i++){
                right.push(left.pop());
//                cout << "pushing " << k << "to right" << endl;
            }
        }
//        cout << "popping " << fk << endl;
        return right.pop();
    }


};

int main() {
    int n;
    int com;
    char command;

    Queue queue;

    ifstream infile("queue.in");
    ofstream outfile("queue.out");

    infile >> n;


    for (int i = 0; i < n; i++) {
        infile >> command;
        if (command == '+'){
            infile >> com;
            queue.push(com);
        } else {
            outfile << queue.pop() << endl;
        }
    }

    infile.close();
    outfile.close();
    return 0;
}