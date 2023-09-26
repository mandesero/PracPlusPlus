#include <iostream>
#include "stdint.h"
#include "Rational.h"
#include "Complex.h"
#include "Vector.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Other.h"

int main()
{
    auto ptr = new Matrix<Rational_number<int64_t>>(2, 2);
    auto proxy = (*ptr)[Matrix_column_coord(1)];
    delete ptr;
    std::cout << proxy.to_string();
    return 0;
}
