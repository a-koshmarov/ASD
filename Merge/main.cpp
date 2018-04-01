#include <iostream>
#include <fstream>

using namespace std;

// Объединение
void merge(int *a, int left, int middle, int right) {
//    cout << "merge" << endl;
    int n1 = middle - left;
    int n2 = right - middle + 1;

    // Подмассивы
    int L1[n1], L2[n2];

    // Заполнение подмассивов
    for (int i = 0; i < n1; i++) {
        L1[i] = a[left + i];
//        cout << "L1 " << i << ": " << L1[i] << endl;
    }
    for (int i = 0; i < n2; i++) {
        L2[i] = a[middle + i];
//        cout << "L2 " << i << ": " << L2[i] << endl;
    }

    // Начальные индексы массивов
    int L1_index = 0, L2_index = 0, a_index = left;

    while (L1_index < n1 && L2_index < n2) {
        if (L1[L1_index] <= L2[L2_index]) {
            a[a_index] = L1[L1_index];
//            cout << "L2" << L2_index << ": " << L1[L2_index] << endl;
            L1_index++;
        } else {
            a[a_index] = L2[L2_index];
            L2_index++;
        }
//        cout << "a " << a_index << ": " << a[a_index] << endl;
        a_index++;
    }

    // Заполнение оставшихся элементов
    while (L1_index < n1) {
        a[a_index] = L1[L1_index];
//        cout << "a " << a_index << ": " << a[a_index] << endl;
        L1_index++;
        a_index++;
    }

    while (L2_index < n2) {
        a[a_index] = L2[L2_index];
//        cout << "a " << a_index << ": " << a[a_index] << endl;
        L2_index++;
        a_index++;

    }
}

// Разделение
void mergeSort(int *a, int left, int right) {
    int middle;
    if (left < right) {
        if ((left + right) % 2 != 0) {
            middle = (left + right + 1) / 2;
        } else {
            middle = (left + right) / 2;
        }
//        cout << "left: " << left << "middle: " << middle << "right: " << right << endl;

        mergeSort(a, left, middle - 1);
        mergeSort(a, middle, right);

        merge(a, left, middle, right);
    }
}

int main() {
    int n, count = 0;

    ifstream infile;
    infile.open("sortin.txt");
    infile >> n;

    int data[n];
    for (int i = 0; i < n; i++) {
        infile >> data[i];
    }
    infile.close();

    mergeSort(data, 0, n - 1);

    ofstream outfile;
    outfile.open("sortout.txt");
    for (int i=n-1; i>=0; i--){
        outfile << data[i] << ' ';
    }

    outfile.close();
    return 0;
}