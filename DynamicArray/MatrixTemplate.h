#ifndef DYNAMICARRAY_MATRIXTEMPLATE_H
#define DYNAMICARRAY_MATRIXTEMPLATE_H

#include <iostream>
#include <fstream>

using namespace std;

//template<class T>
//class Matrix;
//
//template<class T>
//std::istream &operator>>(std::istream &, Matrix<T> &);

template<class T>
class Matrix {
private:
    T **createMatrix(int, int);

    int rows, cols;
    T **array;
public:
    Matrix(int x = 3, int y = 3);

    ~Matrix();

    void set(int, int, T);

    void setSize(int, int);

    T get(int, int) const;

    int getRow() const;

    int getCol() const;

    void clearMatrix();

    void trans();

    Matrix<T> &operator=(const Matrix<T> &);

    Matrix<T> operator+(const Matrix<T> &) const;

    Matrix<T> &operator-();

    Matrix<T> operator-(Matrix<T> &) const;

    Matrix<T> operator*(const Matrix<T> &) const;

    Matrix<T> &operator+=(const Matrix<T> &);

    Matrix<T> &operator-=(const Matrix<T> &);

    Matrix<T> &operator*=(const Matrix<T> &);

    std::ostream &printMatrix(std::ostream &) const;

    void readFromFile(const std::string &);

    void writeToFile(const std::string &) const;

//    template <class T>
//    friend std::istream &operator>>(std::istream &, Matrix<T> &);
};

template<class T>
Matrix<T>::Matrix(int x, int y): rows(x), cols(y) {
    array = createMatrix(rows, cols);
}

template<class T>
T **Matrix<T>::createMatrix(int row, int col) {
    T **a = new T *[row];
    for (int i = 0; i < row; i++) {
        a[i] = new T[col];
        for (int j = 0; j < col; j++) {
            a[i][j] = 0;
        }
    }
    return a;
}

template<class T>
Matrix<T>::~Matrix() {
    clearMatrix();
//    std::cout << "deleted" << std::endl;
}

template<class T>
void Matrix<T>::set(int row, int col, T item) {
    array[row][col] = item;
}

template <class T>
void Matrix<T>::setSize(int row, int col){
    rows = row;
    cols = col;
}

template<class T>
T Matrix<T>::get(int row, int col) const {
    return array[row][col];
}

template <class T>
int Matrix<T>::getRow() const {
    return rows;
}

template <class T>
int Matrix<T>::getCol() const {
    return cols;
}

template<class T>
void Matrix<T>::clearMatrix() {
    for (int i = 0; i < rows; i++) {
        delete[] array[i];
    }
    delete[] array;
}

template<class T>
void Matrix<T>::trans() {
    T **trMatrix = createMatrix(cols, rows);
    int tmp;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            trMatrix[i][j] = array[j][i];
        }
    }
    clearMatrix();
    std::swap(rows, cols);
    array = trMatrix;
}

template<class T>
std::ostream &Matrix<T>::printMatrix(std::ostream &s) const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            s << get(i, j) << ' ';
        }
        s << std::endl;
    }
    return s;
}

template<class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &M) {
//    printMatrix(std::cout);
    if (cols != M.cols || rows != M.rows) {
        clearMatrix();
        rows = M.rows;
        cols = M.cols;
    }

    T **newMatrix = createMatrix(M.rows, M.cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newMatrix[i][j] = M.array[i][j];
        }
    }

    array = newMatrix;
    return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &M) const {
    Matrix newMatrix = Matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newMatrix.array[i][j] = array[i][j] + M.array[i][j];
        }
    }
//    newMatrix.printMatrix(std::cout);
//    std::cout << "adding" << std::endl;
    return newMatrix;
}

template<class T>
Matrix<T> &Matrix<T>::operator-() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = -array[i][j];
        }
    }
//    printMatrix(std::cout);
    return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator-(Matrix<T> &M) const {
    Matrix newMatrix = Matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < M.cols; j++) {
            newMatrix.array[i][j] = array[i][j] - M.array[i][j];
        }
    }
    return newMatrix;
}


// TODO: add * and *= operators
template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &M) const {
    Matrix productMatrix = Matrix(rows, M.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < M.cols; j++) {
            for (int k = 0; k < cols; k++) {
                productMatrix.array[i][j] += array[i][k] * M.array[k][j];
            }
        }
    }
//    productMatrix.printMatrix(std::cout);
    return productMatrix;
}

template<class T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &M) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = array[i][j] + M.array[i][j];
        }
    }
    return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &M) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = array[i][j] - M.array[i][j];
        }
    }
    return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &M) {
    T **productMatrix = createMatrix(rows, M.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < M.cols; j++) {
            for (int k = 0; k < cols; k++) {
                productMatrix[i][j] += array[i][k] * M.array[k][j];
            }
        }
    }

    cols = M.cols;
    clearMatrix();
    array = productMatrix;
    return *this;
}

template<class T>
void Matrix<T>::readFromFile(const std::string &name) {
    std::ifstream infile;

    infile.open(name);
    infile >> rows >> cols;
    clearMatrix();
    array = createMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            infile >> array[i][j];
        }
    }
}

template<class T>
void Matrix<T>::writeToFile(const std::string &name) const {
    std::ofstream outfile;

    outfile.open(name);
    outfile << rows << ' ' << cols << std::endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            outfile << array[i][j] << ' ';
        }
        outfile << std::endl;
    }
}

template<class T>
std::ostream &operator<<(std::ostream &s, const Matrix<T> &M) {
    for (int i = 0; i < M.getRow(); i++) {
        for (int j = 0; j < M.getCol(); j++) {
            s << M.get(i, j) << ' ';
        }
        s << std::endl;
    }
    return s;
}

template<class T>
std::istream &operator>>(std::istream &s, Matrix<T> &M) {
//    int n, m;
    T t;
    std::cout << "Matrix " << M.getRow() << "x" << M.getCol() << ":\n";
//    std::cin >> n >> m;

    for (int i = 0; i < M.getRow(); i++) {
        for (int j = 0; j < M.getCol(); j++) {
            std::cin >> t;
            M.set(i,j,t);
        }
    }
    return s;
//    return M.printMatrix(s);
}

#endif //DYNAMICARRAY_MATRIXTEMPLATE_H
