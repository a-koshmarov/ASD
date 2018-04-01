#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


void heapify(vector<int> &a, int n, int root) {
    int top = root, tmp;

    // Правый и левый наследник
    int l_child = 2 * root + 1;
    int r_child = 2 * root + 2;

    // Находим максимальный из 3 элементов
    if (l_child < n && a[top] < a[l_child]) {
        top = l_child;
    }

    if (r_child < n && a[top] < a[r_child]) {
        top = r_child;
    }

    // Заменяем root на максимальный элемент
    if (top != root) {
        tmp = a[root];
        a[root] = a[top];
        a[top] = tmp;

        // Рекурсивно применяем heapify на элемент, который мы поменяли
        heapify(a, n, top);
    }
}

void heap_sort(vector<int> &a, int n) {
    int tmp;

    // Строим кучу, начиная с последнего элемента у которого есть наследник
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }


    for (int i = n - 1; i >= 0; i--) {
        // Перемещаем root (максимальный элемент) на место i-го элемента, начиная с последнего
        tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;

        // Заново строим невозрастающую кучу на массиве длины i (так как мы теперь не учитваем последний элемент)
        heapify(a, i, 0);
    }
}


int main() {
    int n, num;
    vector<int> data;

    ifstream infile;
    infile.open("sort.in");
    infile >> n;


    for (int i = 0; i < n; i++) {
        infile >> num;
        data.push_back(num);
    }
    infile.close();

    heap_sort(data, n);

    ofstream outfile;
    outfile.open("sort.out");
    for (int i = 0; i < n; i++) {
        outfile << data[i] << " ";
    }
    outfile.close();
    return 0;
}