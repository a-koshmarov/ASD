#include <iostream>
//#include "Matrix.h"
#include "MatrixTemplate.h"

using namespace std;

int main() {
    Matrix<float> p;
    Matrix<float> s;
    Matrix<Matrix<float>> g;
//    Matrix<Matrix<float>> t;

    s.readFromFile("A.txt");
    p.readFromFile("B.txt");

//    g+=t;

    s*=p;
//    p.trans();
    cin >> g;
    cout << g;
    cout << s;

    return 0;
}