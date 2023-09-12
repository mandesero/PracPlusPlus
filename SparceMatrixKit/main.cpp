#include <iostream>
#include "stdint.h"
#include "Rational.h"


int main() {
    // Rational_number<int32_t> a("2 / 3");
    // std::cout << a.round() << " " << a.floor() << std::endl;
    Rational_number<int64_t> b("-3", "2");
    Rational_number<int64_t> c("3", "2");
    // std::cout << b.round() << " " << b.floor() << std::endl;
    // a.print();
    // b.print();
    // (a + b).print();
    // std::cout << b + c;
    // std::cout << b - c;
    // std::cout << b / c;
    // std::cout << b * c;
    // c /= b;
    // b /= c;
    std::cout << b + c;

    return 1;
}