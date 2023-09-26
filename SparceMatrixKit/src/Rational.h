#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>
#include "Complex.h"

/**
 * @brief Шаблонный класс для хранения рационльного числа
 * 
 * @tparam T - тип числителя и знаменателя
 */
template <typename T>
class Rational_number
{
    static_assert(std::is_signed<T>::value && std::is_integral<T>::value);

protected:
    T numtor; /**< Числитель */
    T dentor; /**< Знаменатель */

private:
public:
    /**
     * @brief Конструктор по умолчанию
     *
     */
    Rational_number() : numtor(0), dentor(1) {}

    /**
     * @brief Конструктор
     *
     * @param num [long int] - числитель
     */
    Rational_number(long int num) : numtor(num), dentor(1) {}

    /**
     * @brief Конструктор
     *
     * @param numerator числитель
     * @param denominator знаменатель
     */
    Rational_number(T numerator, T denominator)
    {
        if (denominator == 0)
            throw std::logic_error("Denominator cannot be zero");
        this->numtor = (denominator > 0 ? 1 : -1) * numerator;
        this->dentor = (denominator > 0 ? 1 : -1) * denominator;
    }

    /**
     * @brief Конструктор
     *
     * @param str [const char *] - строка вида 'n / m' или 'k'
     */
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

    /**
     * @brief Конструктор
     *
     * @param num [const char *] - числитель
     * @param denom [const char *] - знаменатель
     */
    Rational_number(const char *num, const char *denom)
    {
        T numerator = static_cast<T>(std::atol(num));
        T denominator = static_cast<T>(std::atol(denom));
        if (denominator == 0)
            throw std::logic_error("Denominator cannot be zero");
        this->numtor = (denominator > 0 ? 1 : -1) * numerator;
        this->dentor = (denominator > 0 ? 1 : -1) * denominator;
    }

    /**
     * @brief Получение значения числителя
     *
     * @return числитель
     */
    T getNumtor() const
    {
        return this->numtor;
    }

    /**
     * @brief Получение значения знаменателя
     *
     * @return знаменатель
     */
    T getDentor() const
    {
        return this->dentor;
    }

    /**
     * @brief Вычисление целой части дроби
     *
     * @return Целая часть
     */
    T floor() const
    {
        return this->numtor / this->dentor;
    }

    /**
     * @brief Округление до ближайшего целого
     *
     * @return Результат округления
     */
    T round() const
    {
        return static_cast<T>(std::round(static_cast<double>(this->numtor) / this->dentor));
    }

    /**
     * @brief Преобразование дроби к double
     *
     * @return double
     */
    operator double() const
    {
        return static_cast<double>(this->numtor) / this->dentor;
    }

    /**
     * @brief Преобразование дроби к int
     *
     * @return int
     */
    operator int() const
    {
        T rat_to_int = this->numtor / this->dentor;
        if (!(std::numeric_limits<int>::min() <= rat_to_int && rat_to_int <= std::numeric_limits<int>::max()))
            throw std::overflow_error("Overflow occurred during conversion to int");
        return static_cast<int>(rat_to_int);
    }

    /**
     * @brief Оператор присваивания
     *
     * @param other рациональное число
     * @return [Rational_number<T>&] - копия
     */
    Rational_number<T> &operator=(const Rational_number<T> &other)
    {
        if (this != &other)
        {
            this->numtor = other.getNumtor();
            this->dentor = other.getDentor();
        }
        return *this;
    }

    /**
     * @brief Оператор присваивания
     *
     * @param other [T] - число
     * @return [Rational_number<T>&] - копия
     */
    Rational_number<T> &operator=(T num)
    {
        this->numtor = num;
        this->dentor = 1;
        return *this;
    }

    /**
     * @brief Перегрузка оператора сложения с рациональным числом
     *
     * @param other слагаемое
     * @return [Rational_number<T>] - новый объект, являющийся суммой слагаемых
     */
    Rational_number<T> operator+(const Rational_number<T> &other) const
    {
        T numerator = this->numtor * other.getDentor() + other.getNumtor() * this->dentor;
        T denominator = this->dentor * other.getDentor();
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, denominator);
    }

    /**
     * @brief Перегрузка оператора += с рациональным числом
     *
     * @param other слагаемое
     * @return [Rational_number<T>&] - ссылка на измененный элемент
     */
    Rational_number<T> &operator+=(const Rational_number<T> &other)
    {
        this->numtor = this->numtor * other.getDentor() + other.getNumtor() * this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        else
            this->dentor *= other.getDentor();
        return *this;
    }

    /**
     * @brief Перегрузка оператора сложения со стандартными типами
     *
     * @param other слагаемое
     * @return [Rational_number<T>] - новый объект, являющийся суммой слагаемых
     */
    template <typename OtherT>
    Rational_number<T> operator+(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        T numerator = this->numtor + this->dentor * static_cast<T>(other);
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, this->dentor);
    }

    /**
     * @brief Перегрузка оператора += со стандартными типами
     *
     * @param other слагаемое
     * @return [Rational_number<T>&] - ссылка на измененный элемент
     */
    template <typename OtherT>
    Rational_number<T> &operator+=(const OtherT &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        this->numtor += static_cast<T>(other) * this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    /**
     * @brief Перегрузка оператора сложения с комплексным числом
     *
     * @param other слагаемое
     * @return [Complex_number<OtherT, OtherU>] - новый объект, являющийся суммой слагаемых
     */
    template <typename OtherT = double, typename OtherU = OtherT>
    Complex_number<OtherT, OtherU> operator+(const Complex_number<OtherT, OtherU> &other) const
    {
        return Complex_number<OtherT, OtherU>(static_cast<OtherT>(static_cast<double>(this->numtor) / this->dentor)) + other;
    }

    /**
     * @brief Оператор префиксного инкримента
     *
     * @return Rational_number<T>&
     */
    Rational_number<T> &operator++()
    {
        this->numtor += this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    /**
     * @brief Оператор постфиксный инкримента
     *
     * @return Rational_number<T>&
     */
    Rational_number<T> &operator++(int val)
    {
        this->numtor += this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    /**
     * @brief Перегрузка оператора вычитания с рациональным числом
     *
     * @param other вычитаемое
     * @return [Rational_number<T>] - новый объект, являющийся суммой слагаемых
     */
    Rational_number<T> operator-(const Rational_number<T> &other) const
    {
        T numerator = this->numtor * other.getDentor() - other.getNumtor() * this->dentor;
        T denominator = this->dentor * other.getDentor();
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, denominator);
    }

    /**
     * @brief Перегрузка вычитания -= с рациональным числом
     *
     * @param other вычитаемое
     * @return [Rational_number<T>&] - ссылка на измененный элемент
     */
    Rational_number<T> &operator-=(const Rational_number<T> &other)
    {
        this->numtor = this->numtor * other.getDentor() - other.getNumtor() * this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        else
            this->dentor *= other.getDentor();
        return *this;
    }

    /**
     * @brief Перегрузка оператора вычитания со стандартными типами
     *
     * @param other вычитаемое
     * @return [Rational_number<T>] - новый объект, являющийся разностью
     */
    template <typename OtherT>
    Rational_number<T> operator-(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        T numerator = this->numtor - this->dentor * static_cast<T>(other);
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, this->dentor);
    }

    /**
     * @brief Перегрузка вычитания -= со стандартными типами
     *
     * @param other вычитаемое
     * @return [Rational_number<T>&] - ссылка на измененный элемент
     */
    template <typename OtherT>
    Rational_number<T> &operator-=(const OtherT &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        this->numtor -= static_cast<T>(other) * this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    /**
     * @brief Перегрузка оператора вычитания с комплексным числом
     *
     * @param other вычитаемое
     * @return [Complex_number<OtherT, OtherU>] - новый объект, являющийся разностью
     */
    template <typename OtherT = double, typename OtherU = OtherT>
    Complex_number<OtherT, OtherU> operator-(const Complex_number<OtherT, OtherU> &other) const
    {
        return Complex_number<OtherT, OtherU>(static_cast<OtherT>(double(this))) - other;
    }

    /**
     * @brief Оператор унарного минуса
     *
     * @return [Rational_number<T>] число со знаком минус
     */
    Rational_number<T> operator-() const
    {
        return Rational_number<T>(-this->numtor, this->dentor);
    }

    /**
     * @brief Перегрузка умножения на рациональное число
     *
     * @param other множитель
     * @return [Rational_number<T>] - новый объект, являющийся результатом умножния
     */
    Rational_number<T> operator*(const Rational_number<T> &other) const
    {
        T numerator = this->numtor * other.getNumtor();
        T denominator = this->dentor * other.getDentor();
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, denominator);
    }

    /**
     * @brief Перегрузка умножения *= на рациональное число
     *
     * @param other множитель
     * @return [Rational_number<T>&] - ссылка на измененный элемент
     */
    Rational_number<T> &operator*=(const Rational_number<T> &other)
    {
        this->numtor *= other.getNumtor();
        if (this->numtor == 0)
            this->dentor = 1;
        else
            this->dentor *= other.getDentor();
        return *this;
    }

    /**
     * @brief Перегрузка умножения на стандартный тип
     *
     * @param other множитель
     * @return [Rational_number<T>] - новый объект, являющийся результатом умножния
     */
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

    /**
     * @brief Перегрузка умножения *= на стандартный тип
     *
     * @param other множитель
     * @return [Rational_number<T>&] - ссылка на измененный элемент
     */
    template <typename OtherT>
    Rational_number<T> &operator*=(const OtherT &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        this->numtor *= static_cast<T>(other);
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    /**
     * @brief Перегрузка умножения на комлпексное число
     *
     * @param other множитель
     * @return [Complex_number<OtherT, OtherU>] - новый объект, являющийся результатом умножния
     */
    template <typename OtherT = double, typename OtherU = OtherT>
    Complex_number<OtherT, OtherU> operator*(const Complex_number<OtherT, OtherU> &other) const
    {
        OtherT re = static_cast<OtherT>(static_cast<double>(this->numtor) / this->dentor * other.getReal());
        OtherU im = static_cast<OtherU>(static_cast<double>(this->numtor) / this->dentor * other.getImag());
        return Complex_number<OtherT, OtherU>(re, im);
    }

    /**
     * @brief Перегрузка деления на рациональное число
     *
     * @param other делитель
     * @return [Rational_number<T>] - новый объект, являющийся результатом деления
     */
    Rational_number<T> operator/(const Rational_number<T> &other) const
    {
        T numerator = this->numtor * other.getDentor();
        T denominator = this->dentor * other.getNumtor();
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>((denominator > 0 ? 1 : -1) * numerator, (denominator > 0 ? 1 : -1) * denominator);
    }

    /**
     * @brief Перегрузка деления /= на рациональное число
     *
     * @param other делитель
     * @return [Rational_number<T>&] - ссылка на измененный элемент
     */
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

    /**
     * @brief Перегрузка деления на стандартный тип
     *
     * @param other делитель
     * @return [Rational_number<T>] - новый объект, являющийся результатом деления
     */
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

    /**
     * @brief Перегрузка деления /= на стандартный тип
     *
     * @param other делитель
     * @return [Rational_number<T>&] - ссылка на измененный элемент
     */
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

    /**
     * @brief Перегрузка деления на комплексное число
     *
     * @param other делитель
     * @return [Complex_number<OtherT, OtherU>] - новый объект, являющийся результатом деления
     */
    template <typename OtherT = double, typename OtherU = OtherT>
    Complex_number<OtherT, OtherU> operator/(const Complex_number<OtherT, OtherU> &other) const
    {
        Complex_number<OtherT, OtherU> tmp(static_cast<double>(this->numtor) / this->dentor);
        return tmp / other;
    }

    /**
     * @brief Перегрузка оператора < для сравнения двух рациональных числе
     *
     * @param other Сравнимое число
     * @return true
     * @return false
     */
    bool operator<(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) < (other.getNumtor() * this->dentor);
    }

    /**
     * @brief Перегрузка оператора < для сравнения со стандартными типами
     *
     * @param other Сравнимое число
     * @return true
     * @return false
     */
    template <typename OtherT>
    bool operator<(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        return (this->numtor) < (static_cast<T>(other) * this->dentor);
    }

    /**
     * @brief Перегрузка оператора <= для сравнения двух рациональных числе
     *
     * @param other Сравнимое число
     * @return true
     * @return false
     */
    bool operator<=(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) <= (other.getNumtor() * this->dentor);
    }

    /**
     * @brief Перегрузка оператора <= для сравнения со стандартными типами
     *
     * @param other Сравнимое число
     * @return true
     * @return false
     */
    template <typename OtherT>
    bool operator<=(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        return (this->numtor) <= (static_cast<T>(other) * this->dentor);
    }

    /**
     * @brief Перегрузка оператора > для сравнения двух рациональных числе
     *
     * @param other Сравнимое число
     * @return true
     * @return false
     */
    bool operator>(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) > (other.getNumtor() * this->dentor);
    }

    /**
     * @brief Перегрузка оператора > для сравнения со стандартными типами
     *
     * @param other Сравнимое число
     * @return true
     * @return false
     */
    template <typename OtherT>
    bool operator>(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        return (this->numtor) > (static_cast<T>(other) * this->dentor);
    }

    /**
     * @brief Перегрузка оператора >= для сравнения двух рациональных числе
     *
     * @param other Сравнимое число
     * @return true
     * @return false
     */
    bool operator>=(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) >= (other.getNumtor() * this->dentor);
    }

    /**
     * @brief Перегрузка оператора >= для сравнения со стандартными типами
     *
     * @param other Сравнимое число
     * @return true
     * @return false
     */
    template <typename OtherT>
    bool operator>=(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        return (this->numtor) >= (static_cast<T>(other) * this->dentor);
    }

    /**
     * @brief Перегрузка оператора == для сравнения двух рациональных числе
     *
     * @param other Сравнимое число
     * @return true
     * @return false
     */
    bool operator==(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) == (other.getNumtor() * this->dentor);
    }

    /**
     * @brief Перегрузка оператора == для сравнения со стандартными типами
     *
     * @param other Сравнимое число
     * @return true
     * @return false
     */
    template <typename OtherT>
    bool operator==(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        return (this->numtor) == (static_cast<T>(other) * this->dentor);
    }

    /**
     * @brief Перегрузка оператора != для сравнения двух рациональных числе
     *
     * @param other Сравнимое число
     * @return true
     * @return false
     */
    bool operator!=(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) != (other.getNumtor() * this->dentor);
    }

    /**
     * @brief Перегрузка оператора != для сравнения со стандартными типами
     *
     * @param other Сравнимое число
     * @return true
     * @return false
     */
    template <typename OtherT>
    bool operator!=(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        return (this->numtor) != (static_cast<T>(other) * this->dentor);
    }

    /**
     * @brief перезрузка оператора вывода << для печати числа
     *
     * @param out поток для вывода
     * @param other число
     * @return [std::ostream&] - поток
     */
    friend std::ostream &operator<<(std::ostream &out, const Rational_number<T> &other)
    {
        out << other.getNumtor() << "/" << other.getDentor() << std::endl;
        return out;
    }

    /**
     * @brief Приведение дроби к несократимой
     *
     */
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

    /**
     * @brief Получение значения по модулю типа double
     *
     * @return double
     */
    double abs() const
    {
        return std::abs(static_cast<double>(this->numtor) / (this->dentor));
    }

    /**
     * @brief Преобразование числа к строке
     *
     * @return std::string
     */
    std::string to_string() const
    {
        return std::to_string(this->numtor) + '/' + std::to_string(this->dentor);
    }
};
