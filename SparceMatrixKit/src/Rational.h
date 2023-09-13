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
    Rational_number(T numerator, T denominator)
    {
        this->numtor = (denominator > 0 ? 1 : -1) * numerator;
        this->dentor = (denominator > 0 ? 1 : -1) * denominator;
    }

public:
    T getNumtor() const
    {
        return this->numtor;
    }

    T getDentor() const
    {
        return this->dentor;
    }

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

    Rational_number<T> operator+(const Rational_number<T> &other) const
    {
        T numerator = this->numtor * other.getDentor() + other.getNumtor() * this->dentor;
        T denominator = this->dentor * other.getDentor();
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, denominator);
    }

    Rational_number<T> operator-(const Rational_number<T> &other) const
    {
        T numerator = this->numtor * other.getDentor() - other.getNumtor() * this->dentor;
        T denominator = this->dentor * other.getDentor();
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, denominator);
    }

    Rational_number<T> operator*(const Rational_number<T> &other) const
    {
        T numerator = this->numtor * other.getNumtor();
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        T denominator = this->dentor * other.getDentor();
        return Rational_number<T>(numerator, denominator);
    }

    Rational_number<T> operator/(const Rational_number<T> &other) const
    {
        if (other.getNumtor() == 0)
            throw std::logic_error("Cant devide by zero");
        T numerator = this->numtor * other.getDentor();
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        T denominator = this->dentor * other.getNumtor();
        return Rational_number<T>(numerator, denominator);
    }

    bool operator<(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) < (other.getNumtor() * this->dentor);
    }

    bool operator>(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) > (other.getNumtor() * this->dentor);
    }

    bool operator<=(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) <= (other.getNumtor() * this->dentor);
    }

    bool operator>=(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) >= (other.getNumtor() * this->dentor);
    }

    bool operator==(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) == (other.getNumtor() * this->dentor);
    }

    bool operator!=(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) != (other.getNumtor() * this->dentor);
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

    Rational_number<T> &operator+=(const Rational_number<T> &other)
    {
        this->numtor = this->numtor * other.getDentor() + other.getNumtor() * this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        else
            this->dentor *= other.getDentor();
        return *this;
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

    Rational_number<T> &operator*=(const Rational_number<T> &other)
    {
        this->numtor *= other.getNumtor();
        if (this->numtor == 0)
            this->dentor = 1;
        else
            this->dentor *= other.getDentor();
        return *this;
    }

    Rational_number<T> &operator/=(const Rational_number<T> &other)
    {
        if (this->numtor == 0)
            return *this;
        if (other.getNumtor() == 0)
            throw std::logic_error("Cant devide by zero");
        this->numtor *= (other.getNumtor() > 0 ? 1 : -1) * other.getDentor();
        this->dentor *= (other.getNumtor() > 0 ? 1 : -1) * other.getNumtor();
        return *this;
    }

    Rational_number<T> operator-() const
    {
        return Rational_number<T>(-this->numtor, this->dentor);
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

    template <typename S>
    Rational_number<T> operator+(S num)
    {
        static_assert(std::is_signed<S>::value && std::is_integral<S>::value);

        T numerator = this->numtor + this->dentor * static_cast<T>(num);
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, this->dentor);
    }

    template <typename S>
    Rational_number<T> operator-(S num)
    {
        static_assert(std::is_signed<S>::value && std::is_integral<S>::value);

        T numerator = this->numtor - this->dentor * static_cast<T>(num);
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, this->dentor);
    }

    template <typename S>
    Rational_number<T> operator*(S num)
    {
        static_assert(std::is_signed<S>::value && std::is_integral<S>::value);

        T numerator = this->numtor * static_cast<T>(num);
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, this->dentor);
    }

    template <typename S>
    Rational_number<T> operator/(S num)
    {
        static_assert(std::is_signed<S>::value && std::is_integral<S>::value);

        if (num == 0)
            throw std::logic_error("Cant devide by zero");

        T numerator = this->numtor / static_cast<T>(num);
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, this->dentor);
    }

    template <typename S>
    Rational_number<T> &operator+=(S num)
    {
        static_assert(std::is_signed<S>::value && std::is_integral<S>::value);

        this->numtor += this->dentor * static_cast<T>(num);
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    template <typename S>
    Rational_number<T> &operator-=(S num)
    {
        static_assert(std::is_signed<S>::value && std::is_integral<S>::value);

        this->numtor -= this->dentor * static_cast<T>(num);
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    template <typename S>
    Rational_number<T> &operator*=(S num)
    {
        static_assert(std::is_signed<S>::value && std::is_integral<S>::value);

        this->numtor *= static_cast<T>(num);
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    template <typename S>
    Rational_number<T> &operator/=(S num)
    {
        static_assert(std::is_signed<S>::value && std::is_integral<S>::value);

        if (num == 0)
            throw std::logic_error("Cant devide by zero");

        this->numtor += this->dentor * static_cast<T>(num);
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }
};
