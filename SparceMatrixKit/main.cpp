#include <iostream>
#include "stdint.h"
#include "src/Rational.h"


int main() {
    Rational_number<int64_t> a("2 / 3");
    Rational_number<int16_t> b("7", "2");
    std::cout << a.round() << " " << a.floor() << std::endl;
    std::cout << b.round() << " " << b.floor() << std::endl;


    return 1;
}