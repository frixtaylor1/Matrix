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
    DynamicMatrix<int> identity = DynamicMatrix<int>::identityMatrix(4);

    std::cout << matrixA << "\n\n" << matrixB << "\n";
    std::cout << identity << std::endl;


    assert(matrixA == matrixB);

    assert(matrixA != (DynamicMatrix<int>({{3,4,1},
                                           {2,4,6},
                                           {1,2,3}}))
    );

    assert(matrixA + matrixB == (DynamicMatrix<int>({{2,4,6},
                                                     {2,4,6},
                                                     {2,4,6}}))
    );

    assert(matrixA - matrixB == (DynamicMatrix<int>({{0,0,0},
                                                     {0,0,0},
                                                     {0,0,0}}))
    );

    assert(matrixA * matrixB == (DynamicMatrix<int>({{6,12,18}, 
                                                     {6,12,18}, 
                                                     {6,12,18}}))
    );

    assert(3 * matrixA == (DynamicMatrix<int>({{3,6,9},
                                               {3,6,9},
                                               {3,6,9}}))
    );

    assert(matrixA * DynamicMatrix<int>::identityMatrix(3) == matrixA);

    return 0;
}