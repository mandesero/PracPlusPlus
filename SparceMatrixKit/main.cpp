#include <iostream>
#include "stdint.h"
#include "Rational.h"
#include "Complex.h"
#include "Vector.h"
#include "Matrix.h"


int main() {

    Rational_number<int16_t> a(4);
    Rational_number<int16_t> b("1 / 2");
    Matrix<4,4, decltype(a)> matrix;
    auto mcopy = matrix[Matrix_coords(1,1,3,3)][Matrix_coords(3,3,4,4)];
    matrix[std::make_pair(1, 1)] = a;
    matrix[std::make_pair(2, 3)] = b;
    std::cout << matrix.to_string() << '\n';
    std::cout << mcopy.to_string();

    // auto c = matrix[Matrix_column_coord(1)];
    // auto r = matrix[Matrix_row_coord(2)];

    // std::cout << c.to_string() << std::endl;
    // std::cout << c[1].to_string() << std::endl;
    // std::cout << r.to_string() << std::endl;

    // auto v1 = c.create_vector();
    // auto v2 = r.create_vector();

    // std::cout << v2.to_string() << std::endl;

    return 0;
}