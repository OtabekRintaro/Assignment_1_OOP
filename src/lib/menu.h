#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "Matrix.h"
#include <vector>

class Menu{
private:
    std::vector<Matrix> ms;
    unsigned int choice;
public:
    ///constructor
    Menu();

    ///commands
    void run();
    void printMenu();
    void create_matrix();
    void putin();
    void putinelement(Matrix &m);
    void delete_matrix();
    void clear_matrix();
    void add_matrices();
    void mul_matrices();
    void print();
    void loadtest();

};

#endif // MENU_H
