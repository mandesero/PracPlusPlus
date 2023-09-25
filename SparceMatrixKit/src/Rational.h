#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>
#include "Complex.h"

template <typename T>
class Rational_number
{
    static_assert(std::is_signed<T>::value && std::is_integral<T>::value);

protected:
    T numtor; /* Numenator */
    T dentor; /* Denomenator */

private:
public:
    Rational_number() : numtor(0), dentor(1) {}

    Rational_number(long int num) : numtor(num), dentor(1) {}

    Rational_number(T numerator, T denominator)
    {
        if (denominator == 0)
            throw std::logic_error("Denominator cannot be zero");
        this->numtor = (denominator > 0 ? 1 : -1) * numerator;
        this->dentor = (denominator > 0 ? 1 : -1) * denominator;
    }

    Rational_number(const char *str)
    {
        std::string s(str);
        size_t i = s.find('/');
        T numerator, denominator;
        if (i != std::string::npos)
        {
            numerator = static_cast<T>(std::stol(s.substr(0, i)));
            denominator = static_cast<T>(std::stol(s.substr(i + 1)));
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
        T numerator = static_cast<T>(std::atol(num));
        T denominator = static_cast<T>(std::atol(denom));
        if (denominator == 0)
            throw std::logic_error("Denominator cannot be zero");
        this->numtor = (denominator > 0 ? 1 : -1) * numerator;
        this->dentor = (denominator > 0 ? 1 : -1) * denominator;
    }

    T getNumtor() const
    {
        return this->numtor;
    }

    T getDentor() const
    {
        return this->dentor;
    }

    T floor() const
    {
        return this->numtor / this->dentor;
    }

    T round() const
    {
        return static_cast<T>(std::round(static_cast<double>(this->numtor) / this->dentor));
    }

    operator double() const
    {
        return static_cast<double>(this->numtor) / this->dentor;
    }

    operator int() const
    {
        T rat_to_int = this->numtor / this->dentor;
        if (!(std::numeric_limits<int>::min() <= rat_to_int && rat_to_int <= std::numeric_limits<int>::max()))
            throw std::overflow_error("Overflow occurred during conversion to int");
        return static_cast<int>(rat_to_int);
    }

    Rational_number<T> &operator=(const Rational_number<T> &other)
    {
        if (this != &other)
        {
            this->numtor = other.getNumtor();
            this->dentor = other.getDentor();
        }
        return *this;
    }

    Rational_number<T> &operator=(T num)
    {
        this->numtor = num;
        this->dentor = 1;
        return *this;
    }

    // operator + and += and ++

    // сложение с рациональными
    Rational_number<T> operator+(const Rational_number<T> &other) const
    {
        T numerator = this->numtor * other.getDentor() + other.getNumtor() * this->dentor;
        T denominator = this->dentor * other.getDentor();
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, denominator);
    }

    Rational_number<T> &operator+=(const Rational_number<T> &other)
    {
        this->numtor = this->numtor * other.getDentor() + other.getNumtor() * this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        else
            this->dentor *= other.getDentor();
        return *this;
    }

    // сложение с стандартными типами
    template <typename OtherT>
    Rational_number<T> operator+(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        T numerator = this->numtor + this->dentor * static_cast<T>(other);
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, this->dentor);
    }

    template <typename OtherT>
    Rational_number<T> &operator+=(const OtherT &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        this->numtor += static_cast<T>(other) * this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    // сложение с комлексными
    template <typename OtherT = double, typename OtherU = OtherT>
    Complex_number<OtherT, OtherU> operator+(const Complex_number<OtherT, OtherU> &other) const
    {
        return Complex_number<OtherT, OtherU>(static_cast<OtherT>(static_cast<double>(this->numtor) / this->dentor)) + other;
    }

    // ++
    Rational_number<T> &operator++()
    {
        this->numtor += this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    Rational_number<T> &operator++(int val)
    {
        this->numtor += this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    // operator -

    // вычитание рациональных
    Rational_number<T> operator-(const Rational_number<T> &other) const
    {
        T numerator = this->numtor * other.getDentor() - other.getNumtor() * this->dentor;
        T denominator = this->dentor * other.getDentor();
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, denominator);
    }

    Rational_number<T> &operator-=(const Rational_number<T> &other)
    {
        this->numtor = this->numtor * other.getDentor() - other.getNumtor() * this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        else
            this->dentor *= other.getDentor();
        return *this;
    }

    // вычитание стандартных типов
    template <typename OtherT>
    Rational_number<T> operator-(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        T numerator = this->numtor - this->dentor * static_cast<T>(other);
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, this->dentor);
    }

    template <typename OtherT>
    Rational_number<T> &operator-=(const OtherT &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        this->numtor -= static_cast<T>(other) * this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    // вычитание комлексных
    template <typename OtherT = double, typename OtherU = OtherT>
    Complex_number<OtherT, OtherU> operator-(const Complex_number<OtherT, OtherU> &other) const
    {
        return Complex_number<OtherT, OtherU>(static_cast<OtherT>(double(this))) - other;
    }

    // унарный минус
    Rational_number<T> operator-() const
    {
        return Rational_number<T>(-this->numtor, this->dentor);
    }

    // operator *

    // умножение на рациональные
    Rational_number<T> operator*(const Rational_number<T> &other) const
    {
        T numerator = this->numtor * other.getNumtor();
        T denominator = this->dentor * other.getDentor();
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, denominator);
    }

    Rational_number<T> &operator*=(const Rational_number<T> &other)
    {
        this->numtor *= other.getNumtor();
        if (this->numtor == 0)
            this->dentor = 1;
        else
            this->dentor *= other.getDentor();
        return *this;
    }

    // умножение на стандартные типы
    template <typename OtherT>
    Rational_number<T> operator*(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        if (other == 0)
            return Rational_number<T>(0, 1);

        T numerator = this->numtor * static_cast<T>(other);
        T denominator = this->dentor;
        return Rational_number<T>(numerator, denominator);
    }

    template <typename OtherT>
    Rational_number<T> &operator*=(const OtherT &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        this->numtor *= static_cast<T>(other);
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    // operator * на Complex

    template <typename OtherT = double, typename OtherU = OtherT>
    Complex_number<OtherT, OtherU> operator*(const Complex_number<OtherT, OtherU> &other) const
    {
        OtherT re = static_cast<OtherT>(static_cast<double>(this->numtor) / this->dentor * other.getReal());
        OtherU im = static_cast<OtherU>(static_cast<double>(this->numtor) / this->dentor * other.getImag());
        return Complex_number<OtherT, OtherU>(re, im);
    }

    // operator /

    // деление на рациональные
    Rational_number<T> operator/(const Rational_number<T> &other) const
    {
        T numerator = this->numtor * other.getDentor();
        T denominator = this->dentor * other.getNumtor();
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>((denominator > 0 ? 1 : -1) * numerator, (denominator > 0 ? 1 : -1) * denominator);
    }

    Rational_number<T> &operator/=(const Rational_number<T> &other)
    {
        if (other.getNumtor() == 0)
            throw std::logic_error("Cant devide by zero");

        this->numtor *= other.getDentor();
        this->dentor *= other.getNumtor();
        this->numtor *= (dentor > 0 ? 1 : -1);
        this->dentor *= (dentor > 0 ? 1 : -1);
        return *this;
    }

    // деление на стандартные типы
    template <typename OtherT>
    Rational_number<T> operator/(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        if (other == 0)
            throw std::logic_error("Cant devide by zero");

        T numerator = this->numtor;
        T denominator = this->dentor * static_cast<T>(other);
        return Rational_number<T>((denominator > 0 ? 1 : -1) * numerator, (denominator > 0 ? 1 : -1) * denominator);
    }

    template <typename OtherT>
    Rational_number<T> &operator/=(const OtherT &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        if (other == 0)
            throw std::logic_error("Cant devide by zero");

        this->dentor *= static_cast<T>(other);
        this->dentor *= (dentor > 0 ? 1 : -1);
        return *this;
    }

    // деление на комплексные
    template <typename OtherT = double, typename OtherU = OtherT>
    Complex_number<OtherT, OtherU> operator/(const Complex_number<OtherT, OtherU> &other) const
    {
        Complex_number<OtherT, OtherU> tmp(static_cast<double>(this->numtor) / this->dentor);
        return tmp / other;
    }

    // compare operators

    // <
    bool operator<(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) < (other.getNumtor() * this->dentor);
    }

    template <typename OtherT>
    bool operator<(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        return (this->numtor) < (static_cast<T>(other) * this->dentor);
    }

    // <=
    bool operator<=(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) <= (other.getNumtor() * this->dentor);
    }

    template <typename OtherT>
    bool operator<=(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        return (this->numtor) <= (static_cast<T>(other) * this->dentor);
    }

    // >
    bool operator>(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) > (other.getNumtor() * this->dentor);
    }

    template <typename OtherT>
    bool operator>(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        return (this->numtor) > (static_cast<T>(other) * this->dentor);
    }

    // >=
    bool operator>=(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) >= (other.getNumtor() * this->dentor);
    }

    template <typename OtherT>
    bool operator>=(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        return (this->numtor) >= (static_cast<T>(other) * this->dentor);
    }

    // ==
    bool operator==(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) == (other.getNumtor() * this->dentor);
    }

    template <typename OtherT>
    bool operator==(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        return (this->numtor) == (static_cast<T>(other) * this->dentor);
    }

    // !=
    bool operator!=(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) != (other.getNumtor() * this->dentor);
    }

    template <typename OtherT>
    bool operator!=(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        return (this->numtor) != (static_cast<T>(other) * this->dentor);
    }

    friend std::ostream &operator<<(std::ostream &out, const Rational_number<T> &other)
    {
        out << other.getNumtor() << "/" << other.getDentor() << std::endl;
        return out;
    }

    void make_canonical()
    {
        T numerator = (this->numtor > 0 ? 1 : -1) * this->numtor;
        T denomerator = (this->dentor > 0 ? 1 : -1) * this->dentor;
        while (numerator != denomerator)
            if (numerator > denomerator)
                numerator -= denomerator;
            else
                denomerator -= numerator;
        this->numtor /= numerator;
        this->dentor /= denomerator;
    }

    double abs() const
    {
        return std::abs(static_cast<double>(this->numtor) / (this->dentor));
    }

    std::string to_string() const
    {
        return std::to_string(this->numtor) + '/' + std::to_string(this->dentor);
    }

    // Rational_number(const Rational_number<T> &other)
    // {
    //     this->numtor = other.getNumtor();
    //     this->dentor = other.getDentor();
    // }
};
