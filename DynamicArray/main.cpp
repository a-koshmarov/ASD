#include <iostream>
//#include "Matrix.h"
#include "MatrixTemplate.h"

using namespace std;

int main() {
    Matrix<float> p;
    Matrix<float> s;
    Matrix<Matrix<int>> t (2,2);


    s.readFromFile("A.txt");
    p.readFromFile("B.txt");
//    cout << s << endl <<p << endl;

//    t = p+s;
//    p.trans();
    cin >> t;
    cout << t;

    return 0;
}