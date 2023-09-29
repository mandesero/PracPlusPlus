#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>
#include "Rational.h"

template <typename T>
class Rational_number;

/**
 * @brief Шаблонный класс для хранения комлпексных чисел
 *
 * @tparam T
 * @tparam U
 */
template <typename T = double, typename U = T>
class Complex_number
{

    static_assert(std::is_arithmetic<T>::value, "Type T must be numeric");
    static_assert(std::is_arithmetic<U>::value, "Type U must be numeric");

protected:
    T real; /**< Действительная часть */
    U imag; /**< Мнимая часть */

private:
public:

    static auto getTypeNames()
    {
        return std::pair<const char *, const char *>(typeid(T).name(), typeid(U).name());
    }

    /**
     * @brief Вывод названия типа
     *
     */
    static auto type()
    {
        return "complex";
    }

    /**
     * @brief Конструктор
     *
     * @param re Действительная часть
     * @param im Мнимая часть
     */
    Complex_number(T re, U im) : real(re), imag(im) {}

    /**
     * @brief Конструктор по умолчанию
     *
     */
    Complex_number() : real(0), imag(0) {}

    /**
     * @brief Конструктор
     *
     * @param re Действительная часть
     */
    Complex_number(long int re) : real(static_cast<T>(re)), imag(0) {}

    /**
     * @brief Конструктор
     *
     * @param r [const char *] Действительная часть
     * @param i [const char *] Мнимая часть
     */
    Complex_number(const char *r, const char *i) : real(static_cast<T>(std::atof(r))), imag(static_cast<U>(std::atof(i))) {}

    /**
     * @brief Конструктор
     *
     * @param str [const char *] число в формате 'n , m' или 'k'
     */
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

    /**
     * @brief Получить действительную часть числа
     *
     * @return T
     */
    T getReal() const
    {
        return this->real;
    }

    /**
     * @brief Получить мнимую часть числа
     *
     * @return U
     */
    U getImag() const
    {
        return this->imag;
    }

    /**
     * @brief Get the Radius object
     *
     * @return double
     */
    double getRadius() const
    {
        return static_cast<double>(this->real) * static_cast<double>(this->real) + static_cast<double>(this->imag) * static_cast<double>(this->imag);
    }

    /**
     * @brief Оператор присваивания
     *
     * @param other
     * @return Complex_number<T, U>&
     */
    Complex_number<T, U> &operator=(const Complex_number<T, U> &other)
    {
        if (this != &other)
        {
            this->real = other.getReal();
            this->imag = other.getImag();
        }
        return *this;
    }

    /**
     * @brief Констуктор копирования
     *
     * @param other
     */
    Complex_number(const Complex_number &other) : real(other.getReal()), imag(other.getImag()) {}

    /**
     * @brief Перегрузка оператора сложения с комплексными числами
     *
     * @param other
     * @return Complex_number<T, U>
     */
    Complex_number<T, U> operator+(const Complex_number<T, U> &other) const
    {
        T re = this->real + other.getReal();
        U im = this->imag + other.getImag();
        return Complex_number<T, U>(re, im);
    }

    /**
     * @brief Перегрузка оператора += с комплексными числами
     *
     * @param other
     * @return Complex_number<T, U>&
     */
    Complex_number<T, U> &operator+=(const Complex_number<T, U> &other)
    {
        this->real += other.getReal();
        this->imag += other.getImag();
        return *this;
    }

    /**
     * @brief Перегрузка оператора сложения со стандартными типами
     *
     * @param other
     * @return Complex_number<T, U>
     */
    template <typename T1>
    Complex_number<T, U> operator+(const T1 &num) const
    {
        T re = this->real + static_cast<T>(num);
        U im = this->imag;
        return Complex_number<T, U>(re, im);
    }

    /**
     * @brief Перегрузка оператора += со стандартными типами
     *
     * @param other
     * @return Complex_number<T, U>&
     */
    template <typename T1>
    Complex_number<T, U> &operator+=(const T1 &num)
    {
        this->real += static_cast<T>(num);
        return *this;
    }

    /**
     * @brief Перегрузка оператора сложения с рациональными числами
     *
     * @param other
     * @return Complex_number<T, U>
     */
    template <typename OtherT>
    Complex_number<T, U> operator+(const Rational_number<OtherT> &other) const
    {
        return Complex_number<T, U>(this->real + static_cast<double>(other.getNumtor()) / other.getDentor(), this->imag);
    }

    /**
     * @brief Оператор прифексного инкримента
     *
     * @return Complex_number<T, U>&
     */
    Complex_number<T, U> &operator++()
    {
        this->real += static_cast<T>(1);
        return *this;
    }

    /**
     * @brief Оператор постфиксного инкримента
     *
     * @param val
     * @return Complex_number<T, U>&
     */
    Complex_number<T, U> &operator++(int val)
    {
        this->real += static_cast<T>(1);
        return *this;
    }

    /**
     * @brief Перегрузка оператора вычитания с комплексными числами
     *
     * @param other
     * @return Complex_number<T, U>
     */
    Complex_number<T, U> operator-(const Complex_number<T, U> &other) const
    {
        T re = this->real - other.getReal();
        U im = this->imag - other.getImag();
        return Complex_number<T, U>(re, im);
    }

    /**
     * @brief Перегрузка оператора -= с комплексными числами
     *
     * @param other
     * @return Complex_number<T, U>&
     */
    Complex_number<T, U> &operator-=(const Complex_number<T, U> &other)
    {
        this->real -= other.getReal();
        this->imag -= other.getImag();
        return *this;
    }

    /**
     * @brief Перегрузка оператора вычитания со стандартными типами
     *
     * @param other
     * @return Complex_number<T, U>
     */
    template <typename T1>
    Complex_number<T, U> operator-(const T1 &num) const
    {
        T re = this->real - static_cast<T>(num);
        U im = this->imag;
        return Complex_number<T, U>(re, im);
    }

    /**
     * @brief Перегрузка оператора -= со стандартными типами
     *
     * @param other
     * @return Complex_number<T, U>&
     */
    template <typename T1>
    Complex_number<T, U> &operator-=(const T1 &num)
    {
        this->real -= static_cast<T>(num);
        return *this;
    }

    /**
     * @brief Перегрузка оператора вычитания с рациональными числами
     *
     * @param other
     * @return Complex_number<T, U>
     */
    template <typename OtherT>
    Complex_number<T, U> operator-(const Rational_number<OtherT> &other) const
    {
        return Complex_number<T, U>(this->real - static_cast<double>(other.getNumtor()) / other.getDentor(), this->imag);
    }

    /**
     * @brief Унарный минус
     *
     * @return Complex_number<T, U>
     */
    Complex_number<T, U> operator-() const
    {
        return Complex_number<T, U>(-this->real, -this->imag);
    }

    /**
     * @brief Перегрузка оператора умножения на комплексные числа
     *
     * @param other
     * @return Complex_number<T, U>
     */
    Complex_number<T, U> operator*(const Complex_number<T, U> &other) const
    {
        T re = this->real * other.getReal() - this->imag * other.getImag();
        U im = this->real * other.getImag() + this->imag * other.getReal();
        return Complex_number<T, U>(re, im);
    }

    /**
     * @brief Перегрузка оператора *= на комплексные числа
     *
     * @param other
     * @return Complex_number<T, U>&
     */
    Complex_number<T, U> &operator*=(const Complex_number<T, U> &other)
    {
        this->real = this->real * other.getReal() - this->imag * other.getImag();
        this->imag = this->real * other.getImag() + this->imag * other.getReal();
        return *this;
    }

    /**
     * @brief Перегрузка оператора умножения на стандартные типы
     *
     * @param other
     * @return Complex_number<T, U>
     */
    template <typename T1>
    Complex_number<T, U> operator*(const T1 num) const
    {
        T re = this->real * static_cast<T>(num);
        U im = this->imag * static_cast<U>(num);
        return Complex_number<T, U>(re, im);
    }

    /**
     * @brief Перегрузка оператора *= на стандартные типы
     *
     * @param other
     * @return Complex_number<T, U>&
     */
    template <typename T1>
    Complex_number<T, U> &operator*=(const T1 num)
    {
        this->real *= static_cast<T>(num);
        this->imag *= static_cast<U>(num);
        return *this;
    }

    /**
     * @brief Перегрузка оператора умножения на рациональные числа
     *
     * @param other
     * @return Complex_number<T, U>
     */
    template <typename OtherT>
    Complex_number<T, U> operator*(const Rational_number<OtherT> &other) const
    {
        T re = this->real * double(other);
        U im = this->imag * double(other);
        return Complex_number<T, U>(re, im);
    }

    /**
     * @brief Перегрузка оператора деления на комплексные числа
     *
     * @param other
     * @return Complex_number<T, U>
     */
    Complex_number<T, U> operator/(const Complex_number<T, U> &other) const
    {
        if (other.getReal() == 0 && other.getImag() == 0)
            throw std::logic_error("Cant devide by zero");
        T re = this->real * other.getReal() + this->imag * other.getImag();
        U im = this->real * other.getImag() - this->imag * other.getReal();
        T tmp = this->real * this->real + this->imag * this->imag;
        return Complex_number<T, U>(re / tmp, im / tmp);
    }

    /**
     * @brief Перегрузка оператора /= на комплексные числа
     *
     * @param other
     * @return Complex_number<T, U>&
     */
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

    /**
     * @brief Перегрузка оператора деления на стандартные типы
     *
     * @param other
     * @return Complex_number<T, U>
     */
    template <typename T1>
    Complex_number<T, U> operator/(const T1 num) const
    {
        if (num == 0)
            throw std::logic_error("Cant devide by zero");
        T re = this->real / static_cast<T>(num);
        U im = this->imag / static_cast<U>(num);
        return Complex_number<T, U>(re, im);
    }

    /**
     * @brief Перегрузка оператора /= на стандартные типы
     *
     * @param other
     * @return Complex_number<T, U>&
     */
    template <typename T1>
    Complex_number<T, U> &operator/=(const T1 num)
    {
        if (num == 0)
            throw std::logic_error("Cant devide by zero");
        this->real /= static_cast<T>(num);
        this->imag /= static_cast<U>(num);
        return *this;
    }

    /**
     * @brief Перегрузка оператора деления на рациональнео число
     *
     * @param other
     * @return Complex_number<T, U>
     */
    template <typename OtherT>
    Complex_number<T, U> operator/(const Rational_number<OtherT> &other)
    {
        this->real /= static_cast<T>(double(other));
        this->imag /= static_cast<T>(double(other));
        return *this;
    }

    /**
     * @brief Сравнения двух комплексных чисел на <
     *
     * @param other
     * @return true
     * @return false
     */
    bool operator<(const Complex_number<T, U> &other) const
    {
        return this->getRadius() < other.getRadius();
    }

    /**
     * @brief Сравнения двух комплексных чисел на <=
     *
     * @param other
     * @return true
     * @return false
     */
    bool operator<=(const Complex_number<T, U> &other) const
    {
        return this->getRadius() <= other.getRadius();
    }

    /**
     * @brief Сравнения двух комплексных чисел на >
     *
     * @param other
     * @return true
     * @return false
     */
    bool operator>(const Complex_number<T, U> &other) const
    {
        return this->getRadius() > other.getRadius();
    }

    /**
     * @brief Сравнения двух комплексных чисел на >=
     *
     * @param other
     * @return true
     * @return false
     */
    bool operator>=(const Complex_number<T, U> &other) const
    {
        return this->getRadius() >= other.getRadius();
    }

    /**
     * @brief Сравнения двух комплексных чисел на ==
     *
     * @param other
     * @return true
     * @return false
     */
    bool operator==(const Complex_number<T, U> &other) const
    {
        return this->getRadius() == other.getRadius();
    }

    /**
     * @brief Сравнения двух комплексных чисел на !=
     *
     * @param other
     * @return true
     * @return false
     */
    bool operator!=(const Complex_number<T, U> &other) const
    {
        return this->getRadius() != other.getRadius();
    }

    /**
     * @brief Перегрузка оператора вывод <<
     *
     * @param out
     * @param other
     * @return std::ostream&
     */
    friend std::ostream &operator<<(std::ostream &out, const Complex_number<T, U> &other)
    {
        out << other.getReal() << "," << other.getImag() << std::endl;
        return out;
    }

    /**
     * @brief Получение модуля числа
     *
     * @return double
     */
    double abs() const
    {
        return sqrt(this->getRadius());
    }

    /**
     * @brief Преобразование числа к строке
     *
     * @return std::string
     */
    std::string to_string() const
    {
        return std::to_string(this->real) + '+' + std::to_string(this->imag) + 'i';
    }
};
