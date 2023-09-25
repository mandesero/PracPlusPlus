#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>
#include "Rational.h"

template <typename T>
class Rational_number;

template <typename T = double, typename U = T>
class Complex_number
{

    static_assert(std::is_arithmetic<T>::value, "Type T must be numeric");
    static_assert(std::is_arithmetic<U>::value, "Type U must be numeric");

protected:
    T real;
    U imag;

private:
public:
    Complex_number(T re, U im) : real(re), imag(im) {}

    Complex_number() : real(0), imag(0) {}

    Complex_number(long int re) : real(static_cast<T>(re)), imag(0) {}

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

    // operator + and += and ++

    // сложение с комплексными
    Complex_number<T, U> operator+(const Complex_number<T, U> &other) const
    {
        T re = this->real + other.getReal();
        U im = this->imag + other.getImag();
        return Complex_number<T, U>(re, im);
    }

    Complex_number<T, U> &operator+=(const Complex_number<T, U> &other)
    {
        this->real += other.getReal();
        this->imag += other.getImag();
        return *this;
    }

    // сложение с стандратными типами
    template <typename T1>
    Complex_number<T, U> operator+(const T1 &num) const
    {
        T re = this->real + static_cast<T>(num);
        U im = this->imag;
        return Complex_number<T, U>(re, im);
    }

    template <typename T1>
    Complex_number<T, U> &operator+=(const T1 &num)
    {
        this->real += static_cast<T>(num);
        return *this;
    }

    // сложение с рациональными
    template <typename OtherT>
    Complex_number<T, U> operator+(const Rational_number<OtherT> &other) const
    {
        return Complex_number<T, U>(this->real + static_cast<double>(other.getNumtor()) / other.getDentor(), this->imag);
    }

    // ++
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

    // вычитание комплексных
    Complex_number<T, U> operator-(const Complex_number<T, U> &other) const
    {
        T re = this->real - other.getReal();
        U im = this->imag - other.getImag();
        return Complex_number<T, U>(re, im);
    }

    Complex_number<T, U> &operator-=(const Complex_number<T, U> &other)
    {
        this->real -= other.getReal();
        this->imag -= other.getImag();
        return *this;
    }

    // вычитание стандратных типов
    template <typename T1>
    Complex_number<T, U> operator-(const T1 &num) const
    {
        T re = this->real - static_cast<T>(num);
        U im = this->imag;
        return Complex_number<T, U>(re, im);
    }

    template <typename T1>
    Complex_number<T, U> &operator-=(const T1 &num)
    {
        this->real -= static_cast<T>(num);
        return *this;
    }

    // вычитание рациональных
    template <typename OtherT>
    Complex_number<T, U> operator-(const Rational_number<OtherT> &other) const
    {
        return Complex_number<T, U>(this->real - static_cast<double>(other.getNumtor()) / other.getDentor(), this->imag);
    }

    // унарный минус
    Complex_number<T, U> operator-() const
    {
        return Complex_number<T, U>(-this->real, -this->imag);
    }

    // operator *

    // умножение на комплексные
    Complex_number<T, U> operator*(const Complex_number<T, U> &other) const
    {
        T re = this->real * other.getReal() - this->imag * other.getImag();
        U im = this->real * other.getImag() + this->imag * other.getReal();
        return Complex_number<T, U>(re, im);
    }

    Complex_number<T, U> &operator*=(const Complex_number<T, U> &other)
    {
        this->real = this->real * other.getReal() - this->imag * other.getImag();
        this->imag = this->real * other.getImag() + this->imag * other.getReal();
        return *this;
    }

    // умножение на стандартные типы
    template <typename T1>
    Complex_number<T, U> operator*(const T1 num) const
    {
        T re = this->real * static_cast<T>(num);
        U im = this->imag * static_cast<U>(num);
        return Complex_number<T, U>(re, im);
    }

    template <typename T1>
    Complex_number<T, U> &operator*=(const T1 num)
    {
        this->real *= static_cast<T>(num);
        this->imag *= static_cast<U>(num);
        return *this;
    }

    // operator * на Rational

    template <typename OtherT>
    Complex_number<T, U> operator*(const Rational_number<OtherT> &other) const
    {
        T re = this->real * double(other);
        U im = this->imag * double(other);
        return Complex_number<T, U>(re, im);
    }

    // operator /

    // деление на комплексные
    Complex_number<T, U> operator/(const Complex_number<T, U> &other) const
    {
        if (other.getReal() == 0 && other.getImag() == 0)
            throw std::logic_error("Cant devide by zero");
        T re = this->real * other.getReal() + this->imag * other.getImag();
        U im = this->real * other.getImag() - this->imag * other.getReal();
        T tmp = this->real * this->real + this->imag * this->imag;
        return Complex_number<T, U>(re / tmp, im / tmp);
    }

    Complex_number<T, U> &operator/=(const Complex_number<T, U> &other)
    {
        if (other.getReal() == 0 && other.getImag() == 0)
            throw std::logic_error("Cant devide by zero");
        T re = this->real * other.getReal() + this->imag * other.getImag();
        U im = this->real * other.getImag() - this->imag * other.getReal();
        T tmp = this->real * this->real + this->imag * this->imag;
        this->real = re / tmp;
        this->imag = im / tmp;
        return *this;
    }

    // деление на стандартные типы
    template <typename T1>
    Complex_number<T, U> operator/(const T1 num) const
    {
        if (num == 0)
            throw std::logic_error("Cant devide by zero");
        T re = this->real / static_cast<T>(num);
        U im = this->imag / static_cast<U>(num);
        return Complex_number<T, U>(re, im);
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

    // деление на рациональные

    template <typename OtherT>
    Complex_number<T, U> operator/(const Rational_number<OtherT> &other)
    {
        this->real /= static_cast<T>(double(other)); 
        this->imag /= static_cast<T>(double(other));
        return *this;
    }

    // compare operators

    bool operator<(const Complex_number<T, U> &other) const 
    {
        return this->getRadius() < other.getRadius();
    }

    bool operator<=(const Complex_number<T, U> &other) const
    {
        return this->getRadius() <= other.getRadius();
    }

    bool operator>(const Complex_number<T, U> &other) const
    {
        return this->getRadius() > other.getRadius();
    }

    bool operator>=(const Complex_number<T, U> &other) const
    {
        return this->getRadius() >= other.getRadius();
    }

    bool operator==(const Complex_number<T, U> &other) const
    {
        return this->getRadius() == other.getRadius();
    }

    bool operator!=(const Complex_number<T, U> &other) const
    {
        return this->getRadius() != other.getRadius();
    }

    // out

    friend std::ostream &operator<<(std::ostream &out, const Complex_number<T, U> &other)
    {
        out << other.getReal() << "," << other.getImag() << std::endl;
        return out;
    }

    // abs
    double abs() const
    {
        return sqrt(this->getRadius());
    }

    std::string to_string() const
    {
        return std::to_string(this->real) + '+' + std::to_string(this->imag) + 'i';
    }
};
