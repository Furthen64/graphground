#ifndef HURKAMATRIXV1_H
#define HURKAMATRIXV1_H

#include <iostream>
#include <string>

class HurkaMatrixV1
{

public:

    HurkaMatrixV1(int _rows, int _cols);
    ~HurkaMatrixV1();
    bool isAllocated() { return allocated; }
    void dump();
    int **matrix;
    int rows;
    int cols;




int **allocateMatrix(int rows, int cols)
{

    if(rows > 10000 || cols > 10000) {
            std::cout << "ERROR cannot allocate matrix of that size! " << rows << ", " << cols << "\n";
        return nullptr;
    }

    // std::cout << "allocateMatrix(" << rows << ", " << cols << ")\n";
    int** matrix = new int*[rows];
    if (rows)
    {
        matrix[0] = new int[rows * cols];
        for (int i = 1; i < rows; ++i)
            matrix[i] = matrix[0] + i * cols;
    }





    for(int r = 0; r < rows; r++) {

        for(int c = 0; c < cols; c++) {
                matrix[r][c] = 0;

        }
    }



    return matrix;

}




/// (++)
void dumpMatrix(int** matrix, int rows, int cols)
{

    std::string cn = "HurkaMatrixV1.hpp";

    if(rows > 10000 || cols > 10000) {
        std::cout << "ERROR" << cn << " too big of a roadmatrix! " << rows << ", " << cols << "\n";
        return ;
    }



    std::cout << "\n\n Matrix: \n{\n";
    for(int r = 0; r < rows; r++) {
        std::cout << "   ";
        for(int c = 0; c < cols; c++) {
                std::cout << matrix[r][c] << ", ";

        }
        std::cout << "\n";
    }
    std::cout << "}\n";


}




private:
    bool allocated;

};

#endif
