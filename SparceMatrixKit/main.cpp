#include <iostream>
#include "stdint.h"
#include "Rational.h"
#include "Complex.h"
#include "Vector.h"
#include "Matrix.h"


int main() {

    // Vector<Rational_number<int8_t>> v1(1);
    Matrix<4, 2, Rational_number<int8_t>> m{};
    Rational_number<int8_t> a("11 / 23");
    m.setValue(std::make_pair<int, int>(4, 2), a);
    std::cout << m.to_string();

    Matrix<4, 2, Rational_number<int8_t>> mm{};
    mm.setValue(std::make_pair<int, int>(1, 1), a);
    mm.setValue(std::make_pair<int, int>(4, 2), a);

    std::cout << mm.to_string() << std::endl;

    std::cout << (m + mm).to_string() << std::endl;



    return 0;
}