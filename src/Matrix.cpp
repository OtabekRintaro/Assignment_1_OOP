/**
Implement the X matrix type which contains integers. These are square matrices that
can contain nonzero entries only in their two diagonals. Don't store the zero entries.
Store only the entries that can be nonzero in a sequence. Implement as methods:
getting the entry located at index (i, j), adding and multiplying two matrices, and
printing the matrix (in a square shape).
*/
#include "lib/Matrix.h"



///Constructors

Matrix::Matrix()
{
    _size = 3;
    _vec = {1,2,3,1,0,3};
}

Matrix::Matrix(const std::vector<int> &vec)
{
    setVec(vec);
}

Matrix::Matrix(unsigned int size)
{
    if(size < 0)
    {
        throw Matrix::InvalidMatrixSizeException();
    }
    _size = size;
    _vec.resize(size * 2, 0);
}

Matrix::Matrix(const std::string &fileName)
{
    std::ifstream f(fileName);
    if(f.fail())
    {
        throw InvalidFileNameException();
    }
    int e;
    while(f >> e)
    {
        _vec.push_back(e);
    }
    if(_vec.size() != 1){
    double n=calcSizeFromLength(_vec.size());
        if(n==floor(n))
        {
            _size=n;
        }
        else
        {
            _size=0;
            _vec.clear();
        }
    }
    else{
        _size = _vec.size();
    }
}

///Private Methods

int Matrix::ind(int i, int j) const
{
    if(i == j)
    {
        return i - 1;
    }
    else
    {
        return _size + i - 1;
    }
}

int Matrix::calcSizeFromLength(unsigned int length)
{
    return length / 2;
}

bool InDiagonal(int i, int j, Matrix &m)
{
    return (1<= i && m.getSize() >= i && i == j || 1 <= i && m.getSize() >= i && 1<=j && m.getSize() >= j && i + j == m.getSize() + 1);
}

/// Setters

void Matrix::setVec(const std::vector<int> &vec)
{
    if(vec.size() != 1){
    double n = calcSizeFromLength(vec.size());
    if (n == floor(n))
    {
        _size = n;
        _vec = vec;
    }
    else
    {
        throw InvalidVectorException();
    }
    }
    else{
        _size = vec.size();
        _vec = vec;
    }
}

void Matrix::setElement(int i, int j, int e)
{
    if(i < 1 || j < 1 || i > _size || j > _size)
    {
        throw IndexOutOfRangeException();
    }
    else if( i == j || i + j == _size + 1)
    {
        _vec[ind(i,j)] = e;
    }
    else
    {
        throw NotInDiagonalException();
    }
}
/// Getters

int Matrix::getElement(int i, int j) const
{
    if(1 <= i && _size >= i && j >= 1 && _size >= j && i == j || 1 <= i && _size >= i && j >= 1 && _size >= j && i + j == _size + 1) return _vec[ind(i,j)];
    else if (1 <= i && _size >= i && j >= 1 && _size >= j) return 0;
    else throw IndexOutOfRangeException();
}

/// Static Methods

Matrix Matrix::add(const Matrix &a,const Matrix &b)
{
    if (a.getSize() == b.getSize())
    {
        Matrix sum(a._vec);
        for(int i=0; i<a._vec.size();i++)
        {
            sum._vec[i] += b._vec[i];
        }
        return sum;
    }
    else
    {
        throw DimensionMismatchException();
    }
}

Matrix Matrix::mul(const Matrix &a,const Matrix &b)
{
    if (a.getSize() == b.getSize())
    {
        Matrix mul(a.getSize());
        for (int i=1; i<=a._size;i++)
        {
            for (int j=1;j<=a._size;j++)
            {
                if(1 <= i && a._size >= i && j >= 1 && a._size >= j && i == j || 1 <= i && a._size >= i && j >= 1 && a._size >= j && i + j == a._size + 1)
                {
                    for (int k=1;k<=a._size;k++)
                    {
                        mul.setElement(i,j,mul.getElement(i,j)+a.getElement(i,k)*b.getElement(k,j));
                    }
                }
            }
        }
        return mul;
    }
    else
    {
        throw DimensionMismatchException();
    }
}

std::ostream &operator<<(std::ostream &os, const Matrix& m)
{
    for(int i = 0; i < m._size; i++)
    {
        for(int j = 0; j < m._size; j++)
        {
            if(i == j)
            {
                os << m._vec[i] << " ";
            }
            else if(i + j == m._size - 1)
            {
                os << m._vec[m._size + i] << " ";
            }
            else
            {
                os << 0 << " ";
            }
        }
        os << std::endl;
    }
    return os;
}
