#include <iostream>
#include <fstream>

using namespace std;

void merge(int low, int mid, int high) {
    int h, i, j, b[50], k;
    h = low;
    i = low;
    j = mid + 1;

    while ((h <= mid) && (j <= high)) {
        if (data[h] <= data[j]) {
            b[i] = data[h];
            h++;
        } else {
            b[i] = data[j];
            j++;
        }
        i++;
    }
    if (h > mid) {
        for (k = j; k <= high; k++) {
            b[i] = data[k];
            i++;
        }
    } else {
        for (k = h; k <= mid; k++) {
            b[i] = data[k];
            i++;
        }
    }
    for (k = low; k <= high; k++) data[k] = b[k];
}

int main() {
    int n;

    ifstream infile;
    infile.open("input.txt");
    infile >> n;

    int data[n];
    for (int i = 0; i < n; i++) {
        infile >> data[i];
    }
    infile.close();


    ofstream outfile;
    outfile.open("output.txt");
    for (int i = 0; i < n; i++) {
        outfile << data[i] << " ";
    }
    outfile.close();
    return 0;
}