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
    std::string filename_1 = "input/in_vector_1";
    std::ifstream file_1(filename_1);
    StreamNumber meta_1 = readFromFile(file_1);
    auto v_0 = getCV_ff(meta_1, file_1);
    // auto v_0 = getRV(meta_1, file_1);
    std::cout << v_0.to_string() << std::endl;

    return 0;
}
