#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Все элементы слева от key - меньше, а все элементы справа - больше
int partition(vector<long> &a, int left, int right){
//    cout << "partition " << left << ' ' << right << endl;
//    int key_pos = (left + right)/2;
    long key = a[right];

    int l = left-1, r = right, tmp;

    if (left == right){
        return left;
    }

    while (l<r){
        while(a[++l] < key){

        }
        while(a[--r] > key){

        }

        if (l<r){
            // Сохраняем позицию ключевого элемента
//            if (l == key_pos){
//                key_pos = r;
//            } else if (r == key_pos) {
//                key_pos = l;
//            }

            tmp = a[l];
            a[l] = a[r];
            a[r] = tmp;
//            l++;
//            r++;
        }
    }
    tmp = a[l];
    a[l] = a[right];
    a[right] = tmp;

//    for (int i = left; i<=right; i++){
//        cout << a[i] << ' ';
//    }
//    cout << endl;
//
//    cout << "key is " << l << endl;
    return l;
}

long sort(vector<long> &a, int left, int right, int k){
    while(true){
        int key = partition(a, left, right);
        if (key == k){
//            cout << "returning " << a[key] <<endl;
            return a[key];
        } else if (k < key){
            // Сортируем правую часть массива
            right = key-1;
        } else {
            // Сортируем правую часть
            left = key +1;
        }
    }
}

int main() {
    int n, k, A, B, C;
    long a1, a2;
    vector<long> data;
    vector<long>& d = data;

    ifstream infile;
    infile.open("kth.in");
    infile >> n >> k;
    infile >> A >> B >> C >>a1 >>a2;

    data.push_back(a1);
    data.push_back(a2);

    for (int i = 2; i<n; i++){
        data.push_back(A*data[i-2]+B*data[i-1]+C);
//        cout << data[i] << endl;
    }
    infile.close();

    long f = sort(data, 0, n-1, k-1);
//    mergeSort(d, 0, n-1);

    ofstream outfile;
    outfile.open("kth.out");
    outfile << f;
    outfile.close();

//    cout << k << ' ' << data[k];
//    for (int i=0; i<n; i++){
//        cout << data[i] << endl;
//    }
    return 0;
}