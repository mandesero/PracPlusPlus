#include <iostream>
#include "stdint.h"
#include "Rational.h"
#include "Complex.h"
#include "Vector.h"
#include "Matrix.h"


int main() {

    // Vector<Rational_number<int8_t>> v1(1);
    // Matrix<4, 2, Rational_number<int8_t>> m{};
    Rational_number<int8_t> a("11 / 23");
    // m.set(1, 2, a);
    // std::cout << m.to_string() << std::endl;    
    std::cout << a << (a + a).to_string();


    return 0;
}