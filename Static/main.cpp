#include "StaticMatrix.hpp"
#include <assert.h>

/* 
    TO DO:
        Matrix Multiplication C = A*B in Matrix.hpp line 67. 
*/

int main()
{
    Matrix<int, 3, 3> A({
        3,3,3,
        4,4,4,
        5,5,5
    });

    Matrix<int, 3, 3> B({
        4,4,4,
        5,5,5,
        6,6,6
    });

    std::cout 
        << A 
        << "\n-----------------------\n" 
        << B ;

    std::cout << "\n-----------------------\n";
    std::cout << A - B;
    std::cout << "\n-----------------------\n";
    
    assert(A != B);

    assert(A == (Matrix<int, 3, 3>({3,3,3,
                                    4,4,4,
                                    5,5,5}))
    );

    assert(A + B == (Matrix<int, 3, 3>({7,7,7,
                                        9,9,9,
                                        11,11,11}))
    );

    assert(A - B == (Matrix<int, 3, 3>({-1,-1,-1,
                                        -1,-1,-1,
                                        -1,-1,-1}))
    );

    assert(3 * A == (Matrix<int, 3, 3>({9,9,9,
                                        12,12,12,
                                        15,15,15}))
    );

    assert(A * 3 == (Matrix<int, 3, 3>({9,9,9,
                                       12,12,12,
                                       15,15,15}))
    );

    Matrix<int, 3, 3> asd({ 
        2, 4, 1,
        2, 3, 9,
        3, 1, 8 
    });

    Matrix<int, 3, 3> bsd({
        1, 2, 3,
        3, 6, 1,
        2, 4, 7
    });

    assert(asd.multiply<3>(bsd) == (Matrix<int, 3, 3>({16,32,17,
                                                       29,58,72,
                                                       22,44,66 }))
    );

    Matrix<int, 3, 3> as({
        3,4,5,
        2,3,1,
        5,6,7
    });

    Matrix<int, 3, 1> bs({
        2,
        3,
        4
    });

    std::cout << as.multiply<1>(bs) << std::endl;
    
    assert((as.multiply<1>(bs)) == (Matrix<int, 3, 1>({38,17,56})));



    return 0;
}