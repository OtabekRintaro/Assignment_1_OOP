/**
Implement the X matrix type which contains integers. These are square matrices that
can contain nonzero entries only in their two diagonals. Don't store the zero entries.
Store only the entries that can be nonzero in a sequence. Implement as methods:
getting the entry located at index (i, j), adding and multiplying two matrices, and
printing the matrix (in a square shape).
*/
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <math.h>

class Matrix{
public:

    ///Exceptions
    class NotInDiagonalException : std::exception{};
    class IndexOutOfRangeException : std::exception{};
    class DimensionMismatchException : std::exception{};
    class InvalidFileNameException : std::exception{};
    class InvalidVectorException : std::exception{};
    class InvalidMatrixSizeException : std::exception{};

    /// constructors
    Matrix();
    Matrix(unsigned int size);
    Matrix(const std::vector<int> &vec);
    Matrix(const std::string &fileName);

    ///Setters
    void setVec(const std::vector<int> &vec);
    void setElement(int i, int j, int e);

    ///Getters
    int getElement(int i, int j) const;
    int getSize() const {return _size;};
    std::vector<int> getVec() const {return _vec;};

    ///static methods
    static Matrix add(const Matrix &a,const Matrix &b);
    static Matrix mul(const Matrix &a, const Matrix &b);

    ///operator overload
    friend std::ostream &operator<<(std::ostream &os, const Matrix& x);

private:

    std::vector<int> _vec;
    int _size;

    ///private method
    int ind(int i, int j) const;
    int calcSizeFromLength(unsigned int length);
    bool InDiagonal(int i, int j, Matrix &m);

};

#endif // MATRIX_H
