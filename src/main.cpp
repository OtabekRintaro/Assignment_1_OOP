/**
Implement the X matrix type which contains integers. These are square matrices that
can contain nonzero entries only in their two diagonals. Don't store the zero entries.
Store only the entries that can be nonzero in a sequence. Implement as methods:
getting the entry located at index (i, j), adding and multiplying two matrices, and
printing the matrix (in a square shape).
*/
#include "lib/menu.h"
#include <iostream>
#include "lib/Matrix.h"

using namespace std;

//#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    Menu m;
    m.run();
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "lib/Matrix.h"
#include "lib/catch.hpp"

TEST_CASE("Create, Read, Write")
{
    SECTION("Creating by giving the size","[size]")
    {
        Matrix m1 = Matrix(1); // 1 sized matrix
        CHECK(m1.getSize() == 1);

        Matrix m2 = Matrix(2);//2 sized matrix
        CHECK(m2.getSize() == 2);

        Matrix m3 = Matrix(5);
        CHECK(m3.getSize() == 5);//5 sized matrix
    }

    SECTION("Creating by reading the vector","[size]")
    {
        const vector<int> sample = {0};
        Matrix m1 = Matrix(sample); // 1 sized matrix
        CHECK(m1.getSize() == 1);

        const vector<int> sample1 = {0,0,0,0};
        Matrix m2 = Matrix(sample1);//2 sized matrix
        CHECK(m2.getSize() == 2);

        const vector<int> sample2 = {0,0,0,0,0,0,0,0,0,0};
        Matrix m3 = Matrix(sample2);
        CHECK(m3.getSize() == 5);//5 sized matrix
    }

    SECTION("Creating by reading from file","[size]")
    {

        Matrix m1 = Matrix("inputs/1sizematrix.txt"); // 1 sized matrix
        CHECK(m1.getSize() == 1);


        Matrix m2 = Matrix("inputs/2sizematrix.txt");//2 sized matrix
        CHECK(m2.getSize() == 2);


        Matrix m3 = Matrix("inputs/5matrix.txt");
        CHECK(m3.getSize() == 5);//5 sized matrix
    }
}

TEST_CASE("Setting an Entry")
{
    SECTION("Setting in the beginning and at the end in the diagonal","[entry]")
    {
        Matrix m;
        m.setElement(1,1,2);
        CHECK(m.getElement(1,1) == 2);

        m.setElement(3,3,2);
        CHECK(m.getElement(3,3) == 2);

    }

    SECTION("Setting in the beginning and at the end out of the diagonal","[entry]")
    {
        Matrix m;
        CHECK_THROWS(m.setElement(1,2,2));
        CHECK_THROWS(m.setElement(3,2,2));
    }

    SECTION("Illegal index, indexing a 0-size matrix","[entry]")
    {
        Matrix m;
        CHECK_THROWS(m.setElement(0,0,1));
        CHECK_THROWS(m.setElement(4,4,1));

        Matrix m1 = Matrix(0);
        CHECK_THROWS(m1.setElement(1,1,1));
    }
}

TEST_CASE("Copy constructor")
{
    SECTION("Creating a matrix b based on matrix a", "[copy]")
    {
        Matrix a;
        Matrix b;
        CHECK(a.getVec() == b.getVec());

        a.setElement(1,1,2);
        CHECK_FALSE(a.getVec() == b.getVec());
    }
}

TEST_CASE("Assignment operator")
{
    SECTION("b = a with the same and not the same sizes", "[assignment]")
    {
        Matrix a;
        Matrix b = a;
        CHECK(a.getVec() == b.getVec());

        a.setElement(1,1,2);
        CHECK_FALSE(a.getVec() == b.getVec());
    }

    SECTION("с = b = a with the same and not the same sizes", "[assignment]")
    {
        Matrix a;
        Matrix b = a;
        Matrix c = b;
        CHECK(a.getVec() == b.getVec());
        CHECK(a.getVec() == c.getVec());
        CHECK(b.getVec() == c.getVec());

        a.setElement(1,1,2);
        CHECK_FALSE(a.getVec() == b.getVec());
        CHECK_FALSE(a.getVec() == c.getVec());
        CHECK(b.getVec() == c.getVec());
    }

    SECTION("b = a with the same and not the same sizes", "[assignment]")
    {
        Matrix a;
        a = a;
        CHECK(a.getVec() == a.getVec());

        Matrix temp = a;
        a.setElement(1,1,2);
        CHECK_FALSE(a.getVec() == temp.getVec());
    }
}

TEST_CASE("Addition of two matrices")
{
    SECTION("Different sizes","[add]")
    {
        Matrix a;
        Matrix b = Matrix("inputs/5matrix.txt");
        CHECK_THROWS(Matrix::add(a,b));

        Matrix c = Matrix(4);
        CHECK_THROWS(Matrix::add(c,a));
    }

    SECTION("Commutativity","[add]")
    {
        Matrix a;
        Matrix b;
        CHECK((Matrix::add(a,b)).getVec() == (Matrix::add(a,b)).getVec());
    }

    SECTION("Associativity","[add]")
    {
        Matrix a;
        Matrix b;
        Matrix c;
        CHECK((Matrix::add(Matrix::add(a,b),c)).getVec() == (Matrix::add(Matrix::add(b,c),a)).getVec());
    }

    SECTION("Neutral element","[add]")
    {
        Matrix a;
        Matrix nullmatrix = Matrix(3);
        CHECK((Matrix::add(a,nullmatrix)).getVec() == a.getVec());
    }
}

TEST_CASE("Multiplying two matrices")
{
    SECTION("Different sizes","[multiply]")
    {
        Matrix a;
        Matrix b = Matrix("inputs/5matrix.txt");
        CHECK_THROWS(Matrix::mul(a,b));

        Matrix c = Matrix(4);
        CHECK_THROWS(Matrix::mul(c,a));
    }

    SECTION("Commutativity","[multiply]")
    {
        Matrix a;
        Matrix b = Matrix("inputs/3matrix.txt");
        CHECK_FALSE((Matrix::mul(a,b)).getVec() == (Matrix::mul(b,a)).getVec());
    }

    SECTION("Associativity","[multiply]")
    {
        Matrix a;
        Matrix b;
        Matrix c;
        CHECK((Matrix::mul(Matrix::mul(a,b),c)).getVec() == (Matrix::mul(Matrix::mul(b,c),a)).getVec());
    }

    SECTION("Neutral element","[multiply]")
    {
        Matrix a;
        Matrix nullmatrix = Matrix(3);
        CHECK((Matrix::mul(a,nullmatrix)).getVec() == nullmatrix.getVec());
    }
    SECTION("Identity matrix","[multiply]")
    {
        Matrix a;
        Matrix identity = Matrix("inputs/3identitymatrix.txt");
        CHECK((Matrix::mul(a,identity)).getVec() == a.getVec());
    }
}

#endif
