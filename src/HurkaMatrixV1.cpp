#include "HurkaMatrixV1.hpp"

HurkaMatrixV1::HurkaMatrixV1(int _rows, int _cols)
{
    //std::cout << "allocating matrix with rows=" << _rows << ", cols=" << _cols << "\n";
   matrix = allocateMatrix(_rows, _cols);
   rows = _rows;
   cols = _cols;
   allocated = true;
}

HurkaMatrixV1::~HurkaMatrixV1()
{

}

void HurkaMatrixV1::dump()
{
   dumpMatrix(matrix, rows, cols);
}




