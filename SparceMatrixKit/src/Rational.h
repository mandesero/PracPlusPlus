#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>

template <typename T>
class Rational_number
{
    static_assert(std::is_signed<T>::value && std::is_integral<T>::value);

protected:
    T numtor; /* Numenator */
    T dentor; /* Denomenator */

public:
    Rational_number() : numtor(0), dentor(1) {}

    Rational_number(long int num) : numtor(num), dentor(1) {}

    Rational_number(const char *str)
    {
        std::string s(str);
        size_t i = s.find('/');
        T numerator, denominator;
        if (i != std::string::npos)
        {
            numerator = std::stol(s.substr(0, i));
            denominator = std::stol(s.substr(i + 1));
            if (denominator == 0)
            {
                throw std::logic_error("Denominator cannot be zero");
            }
        }
        else
        {
            numerator = std::stol(s);
            denominator = 1;
        }
        this->numtor = (denominator > 0 ? 1 : -1) * numerator;
        this->dentor = (denominator > 0 ? 1 : -1) * denominator;
    }

    Rational_number(const char *num, const char *denom)
    {
        T numerator = std::atol(num);
        T denominator = std::atol(denom);
        if (denominator == 0)
            throw std::logic_error("Denominator cannot be zero");
        this->numtor = (denominator > 0 ? 1 : -1) * numerator;
        this->dentor = (denominator > 0 ? 1 : -1) * denominator;
    }

    T floor() const
    {
        return this->numtor / this->dentor;
    }

    T round() const
    {
        return static_cast<T>(std::round(static_cast<double>(this->numtor) / this->dentor));
    }

    void print()
    {
        std::cout << this->numtor << " " << this->dentor << std::endl;
    }

    operator double() const
    {
        return static_cast<double>(this->numtor) / this->dentor;
    }

    operator int() const
    {
        T rat_to_num = this->numtor / this->dentor;
        if (!(std::numeric_limits<int>::min() <= rat_to_num && rat_to_num <= std::numeric_limits<int>::max()))
            throw std::overflow_error("Overflow occurred during conversion to int");
        return static_cast<int>(rat_to_num);
    }
};