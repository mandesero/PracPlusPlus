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
        T rat_to_num = this->numtor / this->dentor;
        if (!(std::numeric_limits<int>::min() <= rat_to_num && rat_to_num <= std::numeric_limits<int>::max()))
            throw std::overflow_error("Overflow occurred during conversion to int");
        return static_cast<int>(rat_to_num);
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

    // operator +

    template <typename OtherT>
    Rational_number<T> operator+(const Rational_number<OtherT> &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        T numerator = this->numtor * static_cast<T>(other.getDentor()) + static_cast<T>(other.getNumtor()) * this->dentor;
        T denominator = this->dentor * static_cast<T>(other.getDentor());
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, denominator);
    }

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
    Rational_number<T> &operator+=(const Rational_number<OtherT> &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        this->numtor = this->numtor * static_cast<T>(other.getDentor()) + static_cast<T>(other.getNumtor()) * this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        else
            this->dentor *= static_cast<T>(other.getDentor());
        return *this;
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

    template <typename OtherT>
    Rational_number<T> operator-(const Rational_number<OtherT> &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        T numerator = this->numtor * static_cast<T>(other.getDentor()) - static_cast<T>(other.getNumtor()) * this->dentor;
        T denominator = this->dentor * static_cast<T>(other.getDentor());
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, denominator);
    }

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
    Rational_number<T> &operator-=(const Rational_number<OtherT> &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        this->numtor = this->numtor * static_cast<T>(other.getDentor()) - static_cast<T>(other.getNumtor()) * this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        else
            this->dentor *= static_cast<T>(other.getDentor());
        return *this;
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

    Rational_number<T> operator-() const
    {
        return Rational_number<T>(-this->numtor, this->dentor);
    }

    // operator *

    template <typename OtherT>
    Rational_number<T> operator*(const Rational_number<OtherT> &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        T numerator = this->numtor * static_cast<T>(other.getNumtor());
        T denominator = this->dentor * static_cast<T>(other.getDentor());
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, denominator);
    }

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
    Rational_number<T> &operator*=(const Rational_number<OtherT> &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        this->numtor *= static_cast<T>(other.getNumtor());
        if (this->numtor == 0)
            this->dentor = 1;
        else
            this->dentor *= static_cast<T>(other.getDentor());
        return *this;
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

    // opeator /

    template <typename OtherT>
    Rational_number<T> operator/(const Rational_number<OtherT> &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        T numerator = this->numtor * static_cast<T>(other.getDentor());
        T denominator = this->dentor * static_cast<T>(other.getNumtor());
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, denominator);
    }

    template <typename OtherT>
    Rational_number<T> operator/(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        if (other == 0)
            throw std::logic_error("Cant devide by zero");

        T numerator = this->numtor;
        T denominator = this->dentor * static_cast<T>(other);
        return Rational_number<T>(numerator, denominator);
    }

    template <typename OtherT>
    Rational_number<T> &operator/=(const Rational_number<OtherT> &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        if (other.getNumtor() == 0)
            throw std::logic_error("Cant devide by zero");

        this->numtor *= static_cast<T>(other.getDentor());
        this->dentor *= static_cast<T>(other.getNumtor());
        return *this;
    }

    template <typename OtherT>
    Rational_number<T> &operator/=(const OtherT &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        if (other == 0)
            throw std::logic_error("Cant devide by zero");

        this->dentor *= static_cast<T>(other);
        return *this;
    }

    // compare operators

    template <typename OtherT>
    bool operator<(const Rational_number<OtherT> &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        return (this->numtor * static_cast<T>(other.getDentor())) < (static_cast<T>(other.getNumtor()) * this->dentor);
    }

    template <typename OtherT>
    bool operator<(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        return (this->numtor) < (static_cast<T>(other) * this->dentor);
    }

    // std::cout

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
        return std::to_string((int)(this->numtor)) + '/' + std::to_string((int)(this->dentor));
    }
};
