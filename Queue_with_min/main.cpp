#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
class Stack{
private:
    T *pointer_;
    int size_;
    int inUse_;

public:
    Stack(int n = 2) : size_(n){
        inUse_ = 0;
        pointer_ = new T[n];
    }

    ~Stack(){
        delete[] pointer_;
//        cout << "~Stack" << endl;
    }

    T pop(){
        inUse_--;
        return pointer_[inUse_];
    }

    bool empty(){
        return inUse_==0;
    }

    void push(T num){
        if (size_ == inUse_){
            auto *new_pointer_ = new T[size_*2];

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

    T top() {
        return pointer_[inUse_-1];
    }
};

class Queue{
private:
    Stack<pair<int, int>> left;
    Stack<pair<int, int>> right;
    int minimum;
public:
    Queue(){};
    ~Queue(){
//        cout << "~Queue" << endl;
    };

    void push(int num){
        int local_min = left.empty() ? num : min(num, left.top().second);
        left.push(make_pair(num, local_min));
//        cout << "pushing " << num << "to left" << endl;
    }

    int pop(){
        if (right.getInUse() == 0){
            int inUse = left.getInUse();
            for (int i = 0; i<inUse; i++){
                int local_elem = left.top().first;
                left.pop();
                int local_min = right.empty() ? local_elem : min(local_elem, right.top().second);
                right.push(make_pair(local_elem, local_min));
//                cout << "pushing " << k << "to right" << endl;
            }
        }
//        cout << "popping " << fk << endl;
        return right.pop().first;
    }

    int getMin(){
        if (left.empty()){
//            cout << "top right" << endl;
            return right.top().second;
        } else if (right.empty()) {
//            cout << "top left" << endl;
            return left.top().second;
        } else {
//            cout << "top both" << endl;
            return min(left.top().second, right.top().second);
        }
    }
};

int main() {
    int n;
    int com;
    char command;

    Queue queue;

    ifstream infile("queuemin.in");
    ofstream outfile("queuemin.out");

    infile >> n;


    for (int i = 0; i < n; i++) {
        infile >> command;
        if (command == '+'){
            infile >> com;
            queue.push(com);
        } else if (command == '?'){
            outfile << queue.getMin() << endl;
        } else {
            queue.pop();
        }
    }

    infile.close();
    outfile.close();
    return 0;
}