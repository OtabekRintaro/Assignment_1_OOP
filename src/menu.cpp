#include "lib/menu.h"

Menu::Menu()
{
    choice = 0;
}

void Menu::run()
{
    std::cout << "--------------DIAGONAL MATRIX--------------" << std::endl;
    std::cout << std::endl;
    do
    {
    std::cout << "--------------------MENU--------------------" << std::endl;
        printMenu();
    std::cout << "-------------------------------------------" << std::endl;
        std::cin >> choice;
        switch(choice)
        {
        case 1:
            create_matrix();
            break;
        case 2:
            putin();
            break;
        case 3:
            delete_matrix();
            break;
        case 4:
            clear_matrix();
            break;
        case 5:
            print();
            break;
        case 6:
            add_matrices();
            break;
        case 7:
            mul_matrices();
            break;
        case 8:
            loadtest();
            break;
        }
    }while(choice != 0);
}

void Menu::printMenu()
{
    std::cout << "\n0 - Exit\n";
    std::cout << "1 - Create Matrix\n";
    std::cout << "2 - Set Element of the Matrix\n";
    std::cout << "3 - Delete Matrix\n";
    std::cout << "4 - Clear Matrix\n";
    std::cout << "5 - Print Matrix\n";
    std::cout << "6 - Sum 2 Matrices\n";
    std::cout << "7 - Multiply 2 Matrices\n";
    std::cout << "8 - Load Test\n";
}

void Menu::create_matrix()
{
    int n;
    std::string filename;
        std::cout << "\n-------------Choose an Option-------------\n";
    int choice_matrix = 0;
    do{
        std::cout << "\n0 - Exit\n";
        std::cout << "1 - Create 3x3 Sample Matrix\n";
        std::cout << "2 - Create Empty Matrix\n";
        std::cout << "3 - Create Custom Matrix(File is needed!)\n";
        std::cout << "-------------------------------------------" << std::endl;
        std::cin >> choice_matrix;
        switch(choice_matrix)
        {
        case 1:
            ms.push_back(Matrix());
            choice_matrix = 0;
            break;
        case 2:
            std::cout << "\nWrite size of the Matrix: ";
            std::cin >> n;
            ms.push_back(Matrix(n));
            choice_matrix = 0;
            break;
        case 3:
            std::cout << "\nWrite name of the file with vector: ";
            std::cin >> filename;
            try{
            ms.push_back(Matrix(filename));
            }
            catch(Matrix::InvalidFileNameException ex)
            {
                std::cout << "\nFile opening was unsuccessful!\n";
                choice_matrix = 4;
                break;
            }
            choice_matrix = 0;
            break;
        default:
            std::cout << "\nChoose numbers from 0 to 3\n";
            choice_matrix = 0;
            break;
        }
    }while(choice_matrix != 0);
}

void Menu::putin()
{
    unsigned int choose = 0;
    if(ms.size() == 0)
    {
        std::cout << "\nThere is no matrices yet! Go and create one^~^\n";
        return;
    }
    std::cout << "\n--------------Choose Matrix--------------\n";
    do{
        std::cout << "\n0 - Exit\n";
        for(int i = 1; i <= ms.size(); i++)
        {
            std::cout << "Matrix #" << i << std::endl;
            std::cout << ms[i-1] << std::endl;
            std::cout << "------------------------" << std::endl;
        }
        std::cin >> choose;
        if(choose > ms.size() && choose != 0){
            std::cout << "There is no Matrix #" << choose << "! Try one more time!" << std::endl;
            choose = 1;
        }
        else if(choose != 0){
            putinelement(ms[choose-1]);
            choose = 0;
        }
        std::cout << "-------------------------------------------" << std::endl;
    }while(choose != 0);
}

void Menu::putinelement(Matrix &m)
{
    int i,j,e;
    int n = 0;
    bool created = false;
    do{
    std::cout << "\nWrite Index of the Matrix where you wanna place the element(i and j): ";
    std::cin >> i >> j;
    std::cout << "\nWrite integer value which you want to put in the matrix: ";
    std::cin >> e;
    std::cout << "\nSetting...\n";
    try{
        m.setElement(i,j,e);
    }
    catch(Matrix::IndexOutOfRangeException ex)
    {
        std::cout << "\nYour index is not in the matrix! Try another index!" << std::endl;
        created = true;
    }
    catch(Matrix::NotInDiagonalException ex)
    {
        std::cout << "\nYour index is not on the Diagonal(hint: i = j or i + j = sizeOfTheMatrix)! Try another index!" << std::endl;
        created = true;
    }
    created = !created;
    }while(!created && n);
}

void Menu::delete_matrix()
{
    unsigned int choose = 0;
    Matrix temp;
    if(ms.size() == 0)
    {
        std::cout << "\nThere is no matrices yet! Go and create one^~^\n";
        return;
    }
    std::cout << "\n--------------Choose Matrix--------------\n";
    do{
        std::cout << "\n0 - Exit\n";
        for(int i = 1; i <= ms.size(); i++)
        {
            std::cout << "Matrix #" << i << std::endl;
            std::cout << ms[i-1] << std::endl;
            std::cout << "------------------------" << std::endl;
        }
        std::cin >> choose;
        if(choose-1 >= ms.size() && choose != 0)
        {
            std::cout << "\nThere is no matrix #" << choose << "! Choose another one!" << std::endl;
            choose = 1;
        }
        else if(choose != 0){
            std::cout << "\nDeleting...\n";
            temp = ms[choose-1];
            ms[choose-1] = ms[ms.size() - 1];
            ms[ms.size() - 1] = temp;
            ms.resize(ms.size() - 1);
            std::cout << "\nDeleting was successful!\n";
            choose = 0;
        }

    }while(choose != 0);
}

void Menu::clear_matrix()
{
    int n;
    unsigned int choose = 0;
    if(ms.size() == 0)
    {
        std::cout << "\nThere is no matrices yet! Go and create one^~^\n";
        return;
    }
    std::cout << "\n--------------Choose Matrix--------------\n";
    do{
        std::cout << "\n0 - Exit\n";
        for(int i = 1; i <= ms.size(); i++)
        {
            std::cout << "Matrix #" << i << std::endl;
            std::cout << ms[i-1] << std::endl;
            std::cout << "------------------------" << std::endl;
        }
        std::cin >> choose;
        if(choose-1 >= ms.size() & choose != 0)
        {
            std::cout << "\nThere is no matrix #" << choose << "! Choose another one!" << std::endl;
            choose = 1;
        }
        else if(choose != 0){
            std::cout << "\nClearing...\n";
            try{
            ms[choose-1] = Matrix(ms[choose-1].getSize());
            std::cout << "\nClearing was successful!\n";
            choose = 0;
            }
            catch(Matrix::DimensionMismatchException ex)
            {
                std::cout << "\nClearing was unsuccessful!\n";
                choose = 1;
            }
        }

    }while(choose != 0);
}

void Menu::print()
{
    int n;
    unsigned int choose = 0;
    if(ms.size() == 0)
    {
        std::cout << "\nThere is no matrices yet! Go and create one^~^\n";
        return;
    }
    std::cout << "\n--------------Choose Matrix--------------\n";
    do{
        for(int i = 0; i < ms.size(); i++)
        {
            std::cout << "Matrix #" << i << std::endl;
            std::cout << "------------------------" << std::endl;
        }
        std::cin >> choose;
        if(choose >= ms.size())
        {
            std::cout << "\nThere is no matrix #" << choose << "! Choose another one!" << std::endl;
            choose = 1;
        }
        else{
            std::cout << ms[choose] << std::endl;
            choose = 0;
        }
    }while(choose != 0);
}

void Menu::add_matrices()
{
    Matrix a;
    Matrix b;
    unsigned int choose = 0;
    unsigned int save = 0;
    int cnt = 0;
    if(ms.size() < 2)
    {
        std::cout << "\nThere is not enough matrices yet! Go and create one^~^\n";
        return;
    }
    std::cout << "\n--------------Choose first Matrix--------------\n";
    do{
        for(int i = 0; i < ms.size(); i++)
        {
            std::cout << "Matrix #" << i << std::endl;
            std::cout << "------------------------" << std::endl;
        }
        std::cin >> choose;
        if(choose >= ms.size())
        {
            std::cout << "\nThere is no matrix #" << choose << "! Choose another one!" << std::endl;
            choose = 1;
        }
        else{
            int temp = choose;
            a = ms[temp];
            cnt++;
            choose = 0;
        }
    }while(choose != 0 && cnt != 1);
    std::cout << "\n--------------Choose second Matrix--------------\n";
    do{
        for(int i = 0; i < ms.size(); i++)
        {
            std::cout << "Matrix #" << i << std::endl;
            std::cout << "------------------------" << std::endl;
        }
        std::cin >> choose;
        if(choose >= ms.size())
        {
            std::cout << "\nThere is no matrix #" << choose << "! Choose another one!" << std::endl;
            choose = 1;
        }
        else{
            save = choose;
            b = ms[save];
            cnt++;
            choose = 0;
        }
    }while(choose != 0 && cnt != 2);
    try
    {
        std::cout << Matrix::add(a,b) << std::endl;
    }
    catch(Matrix::DimensionMismatchException ex)
    {
        std::cout << "\nMatrices have different sizes! Try one more time!\n";
        return;
    }
}

void Menu::mul_matrices()
{
    Matrix a;
    Matrix b;
    unsigned int choose = 0;
    unsigned int save = 0;
    int cnt = 0;
    if(ms.size() < 2)
    {
        std::cout << "\nThere is not enough matrices yet! Go and create one^~^\n";
        return;
    }
    std::cout << "\n--------------Choose first Matrix--------------\n";
    do{
        for(int i = 0; i < ms.size(); i++)
        {
            std::cout << "Matrix #" << i << std::endl;
            std::cout << "------------------------" << std::endl;
        }
        std::cin >> choose;
        if(choose >= ms.size())
        {
            std::cout << "\nThere is no matrix #" << choose << "! Choose another one!" << std::endl;
            choose = 1;
        }
        else{
            int temp = choose;
            a = ms[temp];
            cnt++;
            choose = 0;
        }
    }while(choose != 0 && cnt != 1);
    std::cout << "\n--------------Choose second Matrix--------------\n";
    do{
        for(int i = 0; i < ms.size(); i++)
        {
            std::cout << "Matrix #" << i << std::endl;
            std::cout << "------------------------" << std::endl;
        }
        std::cin >> choose;
        if(choose >= ms.size())
        {
            std::cout << "\nThere is no matrix #" << choose << "! Choose another one!" << std::endl;
            choose = 1;
        }
        else{
            save = choose;
            b = ms[save];
            cnt++;
            choose = 0;
        }
    }while(choose != 0 && cnt != 2);
    try
    {
        std::cout << Matrix::mul(a,b) << std::endl;
    }
    catch(Matrix::DimensionMismatchException ex)
    {
        std::cout << "\nMatrices have different sizes! Try one more time!\n";
        return;
    }
}

void Menu::loadtest()
{
    std::cout << "\n--------------Matrix load Test--------------\n";
    std::cout << "\n-------------- -1 Matrix size--------------\n";
    try{Matrix a = Matrix(-1);}
    catch(std::bad_alloc ex){
        std::cout << "\nTest is Succesfull!\n";
        std::cout << "\n-----------------------------------------\n";
        std::cout << "\n\n";
    }

    std::cout << "\n-------------- 0 Matrix size--------------\n";
    Matrix m = Matrix(0);
    std::cout << "\nTest is Succesfull!\n";
    std::cout << "\n-----------------------------------------\n";
    std::cout << "\n\n";

    std::cout << "\n-------------- 1 Matrix size--------------\n";
    m = Matrix(1);
    std::cout << "\nTest is Succesfull!\n";
    std::cout << "\n-----------------------------------------\n";
    std::cout << "\n\n";

    std::cout << "\n-------------- 1000 Matrix size--------------\n";
    m = Matrix(1000);
    std::cout << "\nTest is Succesfull!\n";
    std::cout << "\n-----------------------------------------\n";
    std::cout << "\n\n";
}