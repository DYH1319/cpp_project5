#include <iostream>
#include "matrix.hpp"

using namespace std;

int main() {
    int *data1 = new int[8]{1, 2, 3, 4, 5, 6, 7, 8};
    int *data2 = new int[8]{10, 7, 6, 5, 4, 3, 2, 1};
    int *data3 = new int[12]{1, 2, 2, 3, 4, 4, 1, 5, 2, 6, 6, 3};
    int *data4 = new int[12]{2, 5, 4, 5, 6, 2, 3, 1, 1, 2, 2, 4};

    Matrix<int> matrix1(2, 2, 2, data1);
    matrix1.print();
    Matrix<int> matrix2(2, 2, 2, data2);
    matrix2.print();
    Matrix<int> matrix3 = (matrix1 + matrix2);
    Matrix<int> matrix4 = matrix1 - matrix2;
    matrix3.print();
    cout << matrix4;

    Matrix<int> matrix5(2, 3, 2, data3);
    Matrix<int> matrix6(3, 2, 2, data4);
    cout << matrix5 << (matrix5 * 2);
    cout << matrix3 * matrix4 << (matrix1 == matrix2) << endl;
    Matrix<int> matrix7 = matrix1;
    Matrix<int> matrix8(2, 2, 2, data1);
    matrix8 = matrix1;
    return 0;
}
