#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>

template <typename T = double, typename U = T>
class Complex_number
{

    static_assert(std::is_arithmetic<T>::value, "Type T must be numeric");
    static_assert(std::is_arithmetic<U>::value, "Type U must be numeric");

protected:
    T real;
    U imag;

private:
    Complex_number(T re, U im) : real(re), imag(im) {}

public:
    Complex_number() : real(0), imag(0) {}

    Complex_number(long int re) : real(static_cast<T>(re)) {}

    Complex_number(const char *r, const char *i) : real(static_cast<T>(std::atof(r))), imag(static_cast<U>(std::atof(i))) {}

    Complex_number(const char *str)
    {
        std::string s(str);
        size_t i = s.find(',');
        T re;
        U im;
        if (i != std::string::npos)
        {
            re = std::stol(s.substr(0, i));
            im = std::stol(s.substr(i + 1));
        }
        else
        {
            re = std::stol(s);
            im = 0;
        }
        this->real = re;
        this->imag = im;
    }

    T getReal() const
    {
        return this->real;
    }

    U getImag() const
    {
        return this->imag;
    }

    double getRadius() const
    {
        return static_cast<double>(this->real) * static_cast<double>(this->real) + static_cast<double>(this->imag) * static_cast<double>(this->imag);
    }

    Complex_number<T, U> &operator=(const Complex_number<T, U> &other)
    {
        if (this != &other)
        {
            this->real = other.getReal();
            this->imag = other.getImag();
        }
        return *this;
    }

    Complex_number(const Complex_number &other) : real(other.getReal()), imag(other.getImag()) {}

    // operator + and +=
    template <typename T1, typename T2>
    Complex_number<T, U> operator+(const Complex_number<T1, T2> &other) const
    {
        T re = this->real + static_cast<T>(other.getReal());
        U im = this->imag + static_cast<U>(other.getImag());
        return Complex_number<T, U>(re, im);
    }

    template <typename T1>
    Complex_number<T, U> operator+(const T1 num) const
    {
        T re = this->real + static_cast<T>(num);
        U im = this->imag;
        return Complex_number<T, U>(re, im);
    }

    template <typename T1, typename T2>
    Complex_number<T, U> &operator+=(const Complex_number<T1, T2> &other)
    {
        this->real += static_cast<T>(other.getReal());
        this->imag += static_cast<U>(other.getImag());
        return *this;
    }

    template <typename T1>
    Complex_number<T, U> &operator+=(const T1 num)
    {
        this->real += static_cast<T>(num);
        return *this;
    }

    Complex_number<T, U> &operator++()
    {
        this->real += static_cast<T>(1);
        return *this;
    }

    Complex_number<T, U> &operator++(int val)
    {
        this->real += static_cast<T>(1);
        return *this;
    }

    // operator -
    template <typename T1, typename T2>
    Complex_number<T, U> operator-(const Complex_number<T1, T2> &other) const
    {
        T re = this->real - static_cast<T>(other.getReal());
        U im = this->imag - static_cast<U>(other.getImag());
        return Complex_number<T, U>(re, im);
    }

    template <typename T1>
    Complex_number<T, U> operator-(const T1 num) const
    {
        T re = this->real - static_cast<T>(num);
        U im = this->imag;
        return Complex_number<T, U>(re, im);
    }

    template <typename T1, typename T2>
    Complex_number<T, U> &operator-=(const Complex_number<T1, T2> &other)
    {
        this->real -= static_cast<T>(other.getReal());
        this->imag -= static_cast<U>(other.getImag());
        return *this;
    }

    template <typename T1>
    Complex_number<T, U> &operator-=(const T1 num)
    {
        this->real -= static_cast<T>(num);
        return *this;
    }

    Complex_number<T, U> operator-() const
    {
        return Complex_number<T, U>(-this->real, -this->imag);
    }

    // operator *
    template <typename T1, typename T2>
    Complex_number<T, U> operator*(const Complex_number<T1, T2> &other) const
    {
        T re = this->real * static_cast<T>(other.getReal()) - static_cast<T>(this->imag) * static_cast<T>(other.getImag());
        U im = this->real * static_cast<U>(other.getImag()) + static_cast<U>(this->imag) * static_cast<U>(other.getReal());
        return Complex_number<T, U>(re, im);
    }

    template <typename T1>
    Complex_number<T, U> operator*(const T1 num) const
    {
        T re = this->real * static_cast<T>(num);
        U im = this->imag * static_cast<U>(num);
        return Complex_number<T, U>(re, im);
    }

    template <typename T1, typename T2>
    Complex_number<T, U> &operator*=(const Complex_number<T1, T2> &other)
    {
        this->real = this->real * static_cast<T>(other.getReal()) - static_cast<T>(this->imag) * static_cast<T>(other.getImag());
        this->imag = this->real * static_cast<U>(other.getImag()) + static_cast<U>(this->imag) * static_cast<U>(other.getReal());
        return *this;
    }

    template <typename T1>
    Complex_number<T, U> &operator*=(const T1 num)
    {
        this->real *= static_cast<T>(num);
        this->imag *= static_cast<U>(num);
        return *this;
    }

    // operator /
    template <typename T1, typename T2>
    Complex_number<T, U> operator/(const Complex_number<T1, T2> &other) const
    {
        if (other.getReal() == 0 && other.getImag() == 0)
            throw std::logic_error("Cant devide by zero");
        T re = this->real * static_cast<T>(other.getReal()) + static_cast<T>(this->imag) * static_cast<T>(other.getImag());
        U im = this->real * static_cast<U>(other.getImag()) - static_cast<U>(this->imag) * static_cast<U>(other.getReal());
        T tmp1 = this->real * this->real + static_cast<T>(this->imag) * static_cast<T>(this->imag);
        U tmp2 = this->imag * this->imag + static_cast<U>(this->real) * static_cast<U>(this->real);
        return Complex_number<T, U>(re / tmp1, im / tmp2);
    }

    template <typename T1>
    Complex_number<T, U> operator/(const T1 num) const
    {
        if (num == 0)
            throw std::logic_error("Cant devide by zero");
        T re = this->real / static_cast<T>(num);
        U im = this->imag / static_cast<U>(num);
        return Complex_number<T, U>(re, im);
    }

    template <typename T1, typename T2>
    Complex_number<T, U> &operator/=(const Complex_number<T1, T2> &other)
    {
        if (other.getReal() == 0 && other.getImag() == 0)
            throw std::logic_error("Cant devide by zero");
        T re = this->real * static_cast<T>(other.getReal()) + static_cast<T>(this->imag) * static_cast<T>(other.getImag());
        U im = this->real * static_cast<U>(other.getImag()) - static_cast<U>(this->imag) * static_cast<U>(other.getReal());
        T tmp1 = this->real * this->real + static_cast<T>(this->imag) * static_cast<T>(this->imag);
        U tmp2 = this->imag * this->imag + static_cast<U>(this->real) * static_cast<U>(this->real);
        this->real = re / tmp1;
        this->imag = im / tmp2;
        return *this;
    }

    template <typename T1>
    Complex_number<T, U> &operator/=(const T1 num)
    {
        if (num == 0)
            throw std::logic_error("Cant devide by zero");
        this->real /= static_cast<T>(num);
        this->imag /= static_cast<U>(num);
        return *this;
    }

    // compare operators

    template <typename T1, typename T2>
    bool operator<(const Complex_number<T1, T2> &other)
    {
        return this->Radius() < other.Radius();
    }

    template <typename T1, typename T2>
    bool operator<=(const Complex_number<T1, T2> &other)
    {
        return this->Radius() <= other.Radius();
    }

    template <typename T1, typename T2>
    bool operator>(const Complex_number<T1, T2> &other)
    {
        return this->Radius() > other.Radius();
    }

    template <typename T1, typename T2>
    bool operator>=(const Complex_number<T1, T2> &other)
    {
        return this->Radius() >= other.Radius();
    }

    template <typename T1, typename T2>
    bool operator==(const Complex_number<T1, T2> &other)
    {
        return this->Radius() == other.Radius();
    }

    template <typename T1, typename T2>
    bool operator!=(const Complex_number<T1, T2> &other)
    {
        return this->Radius() != other.Radius();
    }

    // out

    friend std::ostream &operator<<(std::ostream &out, const Complex_number<T, U> &other)
    {
        out << other.getReal() << "," << other.getImag() << std::endl;
        return out;
    }
};
