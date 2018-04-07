#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class PQueue {
public:
    PQueue() {
        size_ = 0;
        array = new int[1000000];
    }

    void heapify(int root) {
        int top = root, tmp;

        // Правый и левый наследник
        int l_child = 2 * root + 1;
        int r_child = 2 * root + 2;

        // Находим минимальный из 3 элементов
        if (l_child < size_ && array[top] >= array[l_child]) {
            top = l_child;
        }

        if (r_child < size_ && array[top] >= array[r_child]) {
            top = r_child;
        }

        // Заменяем root на минимальный элемент
        if (top != root) {
            swap(array[root], array[top]);
            swap(poses[indexes[root]], poses[indexes[top]]);
            swap(indexes[root], indexes[top]);


            // Рекурсивно применяем heapify на элемент, который мы поменяли
            heapify(top);
        }
    }

    void push(int value, int pos) {
        array[size_] = value;
        poses[pos] = size_;
        indexes[size_] = pos;
        size_++;

        int index = poses[pos];
        int parent;
        if (index) {
            if (index % 2 == 0) {
                parent = index / 2 - 1;
            } else {
                parent = index / 2;
            }
            while (index > 0 && parent >= 0 && (array[index] <= array[parent])) {
                if (array[index] < array[parent] || indexes[index] < indexes[parent]) {
                    swap(array[index], array[parent]);
                    swap(poses[indexes[index]], poses[indexes[parent]]);
                    swap(indexes[index], indexes[parent]);
                }
                index = parent;
                parent = index / 2 - 1;
                if (index % 2 == 0) {
                    parent = index / 2 - 1;
                } else {
                    parent = index / 2;
                }
            }
        }
    }

    pair<bool, int> pop_min() {
        if (size_) {
            int val = array[0];
            size_--;
            array[0] = array[size_];
            poses[indexes[size_]] = 0;
            indexes[0] = indexes[size_];
//            printf(" (%d %d %d)\n", array[0], poses[indexes[0]], indexes[0]);
            heapify(0);
            return make_pair(true, val);
        }
        return make_pair(false, 0);
    }

    void decrease(int pos, int value) {
        int index = poses[pos];
        array[index] = value;

        int parent;

        if (index) {
            if (index % 2 == 0) {
                parent = index / 2 - 1;
            } else {
                parent = index / 2;
            }
            while (index > 0 && parent >= 0 && (array[index] <= array[parent])) {
                if (array[index] < array[parent] || indexes[index] < indexes[parent]) {
                    swap(array[index], array[parent]);
                    swap(poses[indexes[index]], poses[indexes[parent]]);
                    swap(indexes[index], indexes[parent]);
                }
                index = parent;
                if (index % 2 == 0) {
                    parent = index / 2 - 1;
                } else {
                    parent = index / 2;
                }
            }
        }
    }

    int get_size() {
        return size_;
    }

private:
    map<int, int> poses, indexes;
    int size_;
    int *array;
};

int main() {

    ifstream infile("priorityqueue.in");
    ofstream outfile("priorityqueue.out");

    PQueue queue;
    bool exist;
    int val, pos = 0, com1, com2;
    string command;

    while (true) {
        infile >> command;
        pos++;
        if (infile.eof()) break;

        if (command == "push") {
            infile >> com1;
            queue.push(com1, pos);

        } else if (command == "extract-min") {
            tie(exist, val) = queue.pop_min();
            if (exist) {
                outfile << val << endl;
            } else {
                outfile << '*' << endl;
            }

        } else {
            infile >> com1 >> com2;
            queue.decrease(com1, com2);
        }
    }

    infile.close();
    outfile.close();
    return 0;
}