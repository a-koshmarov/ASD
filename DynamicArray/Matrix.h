//
// Created by Alexander on 28.02.2018.
//
#ifndef DYNAMICARRAY_MATRIX_H
#define DYNAMICARRAY_MATRIX_H

#include <string>
#include <fstream>

class Matrix {
private:
    int **createMatrix(int, int);

    int rows, cols;
    int **array;
public:
    Matrix(int x = 3, int y = 3);

    ~Matrix();

    void set(int, int, int);

    int get(int, int) const;

    void clearMatrix();

    void trans();

    Matrix &operator=(const Matrix &);

    Matrix operator+(const Matrix &) const;

    Matrix &operator-();

    Matrix operator-(Matrix &) const;

    Matrix operator*(const Matrix &) const;

    Matrix &operator+=(const Matrix &);

    Matrix &operator-=(const Matrix &);

    Matrix &operator*=(const Matrix &);

    std::ostream &printMatrix(std::ostream &) const;

    void readFromFile(const std::string &);

    void writeToFile(const std::string &) const;

    friend std::istream &operator>>(std::istream &, Matrix &);
};


Matrix::Matrix(int x, int y): rows(x), cols(y) {
    array = createMatrix(rows, cols);
}

int **Matrix::createMatrix(int row, int col) {
    auto **a = new int *[row];
    for (int i = 0; i < row; i++) {
        a[i] = new int[col];
        for (int j = 0; j < col; j++) {
            a[i][j] = 0;
        }
    }
    return a;
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; i++) {
        delete[]array[i];
    }
    delete[] array;
//    std::cout << "deleted" << std::endl;
}

void Matrix::set(int row, int col, int item) {
    array[row][col] = item;
}

int Matrix::get(int row, int col) const {
    return array[row][col];
}

void Matrix::clearMatrix(){
    for (int i = 0; i < rows; i++) {
        delete[] array[i];
    }
    delete[] array;
}

void Matrix::trans() {
    int **trMatrix = createMatrix(cols, rows);
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

std::ostream &Matrix::printMatrix(std::ostream &s) const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            s << get(i, j) << ' ';
        }
        s << std::endl;
    }
    return s;
}

Matrix &Matrix::operator=(const Matrix &M) {
//    printMatrix(std::cout);
    if (cols != M.cols || rows!= M.rows) {
        clearMatrix();
        rows = M.rows;
        cols = M.cols;
    }

    int **newMatrix = createMatrix(M.rows, M.cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newMatrix[i][j] = M.array[i][j];
        }
    }

    array = newMatrix;
    return *this;
}

Matrix Matrix::operator+(const Matrix &M) const {
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

Matrix &Matrix::operator-() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = -array[i][j];
        }
    }
//    printMatrix(std::cout);
    return *this;
}

Matrix Matrix::operator-(Matrix &M) const {
    Matrix newMatrix = Matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < M.cols; j++) {
            newMatrix.array[i][j] = array[i][j] - M.array[i][j];
        }
    }
    return newMatrix;
}


// TODO: add * and *= operators
Matrix Matrix::operator*(const Matrix &M) const {
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

Matrix &Matrix::operator+=(const Matrix &M) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = array[i][j] + M.array[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &M) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = array[i][j] - M.array[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &M) {
    int **productMatrix = createMatrix(rows, M.cols);
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

void Matrix::readFromFile(const std::string &name) {
    std::ifstream infile;

    infile.open(name);
    infile >> rows >> cols;
    array = createMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            infile >> array[i][j];
        }
    }
}

void Matrix::writeToFile(const std::string &name) const {
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

std::ostream &operator<<(std::ostream &s, const Matrix &M) {
    return M.printMatrix(s);
}

std::istream &operator>>(std::istream &s, Matrix &M) {
//    int n, m;
    std::cout << "Matrix " << M.rows << "x" << M.cols << ":\n";
//    std::cin >> n >> m;

    for (int i = 0; i < M.rows; i++) {
        for (int j = 0; j < M.cols; j++) {
            std::cin >> M.array[i][j];
        }
    }
    return s;
}


#endif //DYNAMICARRAY_MATRIX_H
