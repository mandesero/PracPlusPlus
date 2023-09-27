#include <iostream>
#include "stdint.h"
#include "Rational.h"
#include "Complex.h"
#include "Vector.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <type_traits>
#include <cmath>
#include "Exceptions.h"

#include "Other.h"

class Aaa
{
public:
    int a = 4;
    Aaa(int b) : a(b) {}
    Aaa operator+(const int &other) const
    {
        return Aaa(a + other);
    }

    friend std::ostream &operator<<(std::ostream &out, const Aaa &other)
    {
        out << other.a;
        return out;
    }
    void g() {}

    friend Aaa operator+(const int64_t &b, const Aaa &other) {
        return other + b;
    }
};
int main()
{
    // Aaa a(4);
    // std::cout << a + 4 << std::endl;
    // std::cout << 9223372036854775806 + a << std::endl;


    Rational_number<int32_t> a("2147483645");
    std::cout << a.to_string() << std::endl; 

    std::cout << (a + 1).to_string() << std::endl; 

    std::cout << (2 - a).to_string() << std::endl; 

    
    // Rational_number<int64_t> b("-9223372036854775808 / 1");
    // std::cout << int(b);

    // try
    // {
    //     Rational_number<int32_t> a("2147483648");
    // }
    // catch (RationalOverflowError<int64_t> &ex)
    // {
    //     ex.what();
    // }
    // try
    // {
    //     Rational_number<int32_t> b("-2147483649");
    // }
    // catch (RationalOverflowError<int64_t> &ex)
    // {
    //     ex.what();
    // }

    // std::cout << std::to_string(std::numeric_limits<int32_t>::max()).c_str() << std::endl;
    // } catch (OverflowError<int64_t> &ex) {
    //     ex.printError();
    // }
    // Rational_number<int32_t>a(5, 0);s
    // std::cout << sizeof(long long) << std::endl;
}