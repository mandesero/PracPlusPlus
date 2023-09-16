#include <iostream>
#include "stdint.h"
#include "Rational.h"
#include "Complex.h"
#include "Vector.h"
#include "Matrix.h"


int main() {

    // TEST RATIONAL NUMBERS
    Rational_number<int16_t> a(4);
    Rational_number<int16_t> b("1 / 2");

    // TEST COMLEX NUMBERS
    Complex_number<double> c("1, 3");
    Vector<4,  Rational_number<int16_t>> dd;
    dd.set(1, a);
    dd.set(3, b);

    std::cout << (dd * Complex_number<>("1, 2")).to_string() << std::endl;
    return 0;
}