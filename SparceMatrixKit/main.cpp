#include <iostream>
#include "stdint.h"
#include "Rational.h"
#include "Complex.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <type_traits>
#include <cmath>
#include "Exceptions.h"

#include <map>
#include <unordered_map>

#include "Other.h"

#include "NewMatrix.h"

int main()
{

    // Matrix<std::unordered_map, Rational_number<int64_t>> a(1, 2);
    Matrix<std::map, Rational_number<int64_t>> b;
    // std::cout << b.shape().first << b.shape().second << std::endl;
    // std::cout << a.to_string() << '\n' << b.to_string() << std::endl;
}