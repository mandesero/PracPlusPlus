#include <iostream>
#include "stdint.h"
#include "Rational.h"
#include "Complex.h"
#include "Vector.h"
#include "Matrix.h"


int main() {

    // Vector<Rational_number<int8_t>> v1(1);
    Matrix<2, 2, Rational_number<int8_t>> m{};
    Rational_number<int8_t> a("5 / 1");
    m.set(1, 1, a);
    Rational_number<int8_t> b("4 / 1");
    m.set(1, 2, b);
    Rational_number<int8_t> d("-6 / 1");
    m.set(2, 1, d);
    Rational_number<int8_t> c("-1 / 1");
    m.set(2, 2, c);
    std::cout << m.to_string() << std::endl;
    std::cout << (m * m).to_string() << std::endl;    
    std::cout << (~(-m)).to_string() << std::endl;
    // std::cout << a.to_string() << '\n' << (a + a).to_string();
    std::cout << m(1,2).to_string() << std::endl;

    Matrix<3, 3, Rational_number<int8_t>> zerosMatrix = Matrix<3, 3, Rational_number<int8_t>>::zeros();      // Создание матрицы из нулей
    Matrix<2, 2, Rational_number<int8_t>> onesMatrix = Matrix<2, 2, Rational_number<int8_t>>::ones();    // Создание матрицы из единиц
    Matrix<4, 4, Rational_number<int8_t>> eyeMatrix = Matrix<4, 4, Rational_number<int8_t>>::eye();  // Создание единичной матрицы

    std::cout << zerosMatrix.to_string() << std::endl;
    std::cout << onesMatrix.to_string() << std::endl;
    std::cout << eyeMatrix.to_string() << std::endl;

    return 0;
}