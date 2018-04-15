#include <iostream>
//#include "Matrix.h"
#include "MatrixTemplate.h"

using namespace std;

int main() {
    Matrix<float> p;
    Matrix<float> s;
    Matrix<float> g;
//    Matrix<Matrix<int>> t (2,2);


    s.readFromFile("A.txt");
    p.readFromFile("B.txt");
//    cout << s << endl <<p << endl;

//    s*=p;
//    p.trans();
    cin >> g;
    cout << g;

    return 0;
}