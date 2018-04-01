#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int n;

    ifstream infile;
    infile.open("smallsort.in");
    infile >> n;

    int data[n];
    for (int i = 0; i < n; i++) {
        infile >> data[i];
    }
    infile.close();

    int maxpos, tmp;
    for (int i = (n-1); i>0; i--) {
        maxpos = 0;
        for (int j = 1; j<(i+1); j++){
            if (data[j] > data[maxpos]) {
                maxpos = j;
            }
        }
        tmp = data[i];
        data[i] = data[maxpos];
        data[maxpos] = tmp;
    }


    ofstream outfile;
    outfile.open("smallsort.out");
    for (int i = 0; i < n; i++) {
        outfile << data[i] << " ";
    }
    outfile.close();
    return 0;
}