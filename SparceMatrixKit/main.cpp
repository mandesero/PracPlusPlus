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

#include <iterator>
#include <map>
#include <unordered_map>

#include "Matrix.h"

int main()
{

    // Matrix<std::unordered_map, Rational_number<int64_t>> a(1, 2);
    // auto m = new Matrix<std::map, Rational_number<int64_t>>(3,3, 0.5);
    // auto x = m->operator[](Matrix_coords(1,1));
    // delete m;
    // x.print();


    // std::string filename = "input/in_matrix_2";
    // std::ifstream file(filename);
    // auto x = Matrix<std::map, Complex_number<int8_t, double>>::readFromStream(file);
    
    
    // Matrix<std::unordered_map, Rational_number<int64_t>> b(3,4, 0.5);
    // b[std::make_pair(1,1)] = Rational_number<int64_t>("2/3");
    // std::cout << b.to_string() << std::endl;
    // auto a = b[Matrix_row_coord(1)];
    // std::cout << a.to_string() << std::endl;
    // auto c = a.create_vector();

    std::string input = "1 2 <1 / 4>";
    std::istringstream iss(input);
    std::vector<std::string> params(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

    for (auto &s: params)
        std::cout << s << '\n';

    // std::cout << a(9, 2);
    // Matrix_coords(-1, 2, 3, 4).calculate();
    // std::cout << (~a).to_string() << std::endl;
    // std::cout << a.to_string() << '\n' << b.to_string() << std::endl;
}
