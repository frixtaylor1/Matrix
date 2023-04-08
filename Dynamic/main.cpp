#include "DynamicMatrix.hpp"
#include <assert.h>

int main()
{

    DynamicMatrix<int> matrixA({ 
        {1,2,3}, 
        {1,2,3}, 
        {1,2,3} 
    });
    DynamicMatrix<int> matrixB({ 
        {1,2,3}, 
        {1,2,3}, 
        {1,2,3} 
    });

    std::cout << matrixA << "\n\n" << matrixB << "\n";

    assert(matrixA == matrixB);

    assert(matrixA * matrixB == (DynamicMatrix<int>({{6,12,18}, {6,12,18}, {6,12,18}})));

    std::cout << matrixA * matrixB << std::endl;
    std::cout << matrixA + matrixB << std::endl;
    std::cout << matrixA - matrixB << std::endl;
    std::cout << 3 * matrixA << std::endl;

    return 0;
}