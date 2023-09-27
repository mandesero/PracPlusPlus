#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>

#include "Complex.h"
#include "Exceptions.h"
#include "Other.h"

/**
 * @brief Шаблонный класс для хранения рационльного числа
 *
 * @tparam тип числителя и знаменателя (знаковый целый тип int8_t, int16_t, ...)
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
     * @brief Конструктор, принимающий числитель и знаменатель, как знаковые типы
     *
     * @param[in] numerator числитель
     * @param[in] denominator знаменатель
     */
    explicit Rational_number(int64_t numerator, int64_t denominator = 1)
    {
        if (denominator == 0)
            throw RationalZeroDivisionError<int64_t>("", __FILE__, __LINE__, "Rational_number(int64_t numerator, int64_t denominator)", numerator);

        if (checkOverFlow<T>(numerator) || checkOverFlow<T>(denominator))
            throw RationalOverflowError<int64_t>("", __FILE__, __LINE__, "Rational_number(int64_t numerator, int64_t denominator)", numerator, denominator);

        this->numtor = (denominator > 0 ? 1 : -1) * static_cast<T>(numerator);
        this->dentor = (denominator > 0 ? 1 : -1) * static_cast<T>(denominator);
    }

    /**
     * @brief Конструктор примающий рациональное число в формате строки
     *
     * @param[in] str указатель на с-строку вида 'n / m' или 'k'
     */
    Rational_number(const char *str)
    {
        std::string s(str);
        size_t i = s.find('/');
        int64_t numerator, denominator;
        if (i != std::string::npos)
        {
            try
            {
                numerator = std::stol(s.substr(0, i));
                denominator = std::stol(s.substr(i + 1));
            }
            catch (std::exception &ex)
            {
                throw RationalOverflowError<int64_t>("", __FILE__, __LINE__, "Rational_number(const char *str)", numerator, denominator);
            }
        }
        else
        {
            try
            {
                numerator = std::stol(s);
                denominator = 1;
            }
            catch (std::exception &ex)
            {
                throw RationalOverflowError<int64_t>("", __FILE__, __LINE__, "Rational_number(const char *str)", numerator, denominator);
            }
        }
        if (checkOverFlow<T>(numerator) || checkOverFlow<T>(denominator))
            throw RationalOverflowError<int64_t>("", __FILE__, __LINE__, "Rational_number(const char *str)", numerator, denominator);

        if (denominator == 0)
            throw RationalZeroDivisionError("", __FILE__, __LINE__, "Rational_number(const char *str)", numerator);

        if (numerator == 0)
        {
            this->numtor = 0;
            this->dentor = 1;
        }
        else
        {
            this->numtor = (denominator > 0 ? 1 : -1) * static_cast<T>(numerator);
            this->dentor = (denominator > 0 ? 1 : -1) * static_cast<T>(denominator);
        }
    }

    /**
     * @brief Конструктор принимающий числитель и знаменатель в виде строк
     *
     * @param[in] num указатель на с-строку - числитель
     * @param[in] denom указатель на с-строку - знаменатель
     */
    Rational_number(const char *num, const char *denom)
    {
        int64_t numerator;
        int64_t denominator;
        try
        {
            numerator = std::atol(num);
            denominator = std::atol(denom);
        }
        catch (std::exception &ex)
        {
            throw RationalOverflowError<int64_t>("", __FILE__, __LINE__, "Rational_number(const char *num, const char *denom)", numerator, denominator);
        }

        if (checkOverFlow<T>(numerator) || checkOverFlow<T>(denominator))
            throw RationalOverflowError<int64_t>("", __FILE__, __LINE__, "Rational_number(const char *num, const char *denom)", numerator, denominator);

        if (denominator == 0)
            throw RationalZeroDivisionError("", __FILE__, __LINE__, "RRational_number(const char *num, const char *denom)", numerator);

        if (numerator == 0)
        {
            this->numtor = 0;
            this->dentor = 1;
        }
        else
        {
            this->numtor = (denominator > 0 ? 1 : -1) * static_cast<T>(numerator);
            this->dentor = (denominator > 0 ? 1 : -1) * static_cast<T>(denominator);
        }
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
     * @brief Вычисление целой части
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
     * @brief Преобразование рационального числа к double
     *
     * @return double
     */
    explicit operator double() const
    {
        return static_cast<double>(this->numtor) / this->dentor;
    }

    /**
     * @brief Преобразование рационального числа к int
     *
     * @return int
     */
    explicit operator int() const
    {
        T rat_to_int = this->numtor / this->dentor;
        if (checkOverFlow<int>(rat_to_int))
            throw RationalOverflowError<int64_t>("Overflow occurred during conversion to int", __FILE__, __LINE__, "operator int() const", 0);
        return static_cast<int>(rat_to_int);
    }

    /**
     * @brief Оператор присваивания к рациональному числу
     *
     * @param[in] other рациональное число
     * @return ссылка на измененный элемент
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
     * @brief Оператор присваивания к стандартным типам
     *
     * @param[in] other знаковое целочисленное значение
     * @return ссылка на измененный элемент
     */
    Rational_number<T> &operator=(T num)
    {
        if (checkOverFlow<int>(num))
            throw RationalOverflowError<int64_t>("", __FILE__, __LINE__, "Rational_number<T> &operator=(T num)", num);
        this->numtor = num;
        this->dentor = 1;
        return *this;
    }

    /*
        Сложение с рациональными числами
    */

    /**
     * @brief Перегрузка оператора сложения с рациональным числом
     *
     * @param[in] other рационально число
     * @return новый объект, являющийся суммой двух рациональных чисел
     */
    Rational_number<T> operator+(const Rational_number<T> &other) const
    {
        uint64_t numerator = this->numtor * other.getDentor() + other.getNumtor() * this->dentor;
        uint64_t denominator = this->dentor * other.getDentor();

        if (checkOverFlow<T>(numerator) || checkOverFlow<T>(denominator))
            throw RationalOverflowError<int64_t>("", __FILE__, __LINE__, "Rational_number<T> operator+(const Rational_number<T> &other) const", numerator, denominator);

        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, denominator);
    }

    /**
     * @brief Перегрузка оператора += с рациональным числом
     *
     * @param[in] other рационально число
     * @return ссылка на измененный элемент
     */
    Rational_number<T> &operator+=(const Rational_number<T> &other)
    {
        uint64_t numerator = this->numtor * other.getDentor() + other.getNumtor() * this->dentor;
        uint64_t denominator = this->dentor * other.getDentor();

        if (checkOverFlow<T>(numerator) || checkOverFlow<T>(denominator))
            throw RationalOverflowError<int64_t>("", __FILE__, __LINE__, "Rational_number<T> &operator+=(const Rational_number<T> &other)", numerator, denominator);

        this->numtor = static_cast<T>(numerator);
        if (this->numtor == 0)
            this->dentor = 1;
        else
            this->dentor = static_cast<T>(denominator);
        return *this;
    }

    /*
        Сложение со стандратными типами
    */

    /**
     * @brief Перегрузка оператора сложения со стандартными типами
     *
     * @param[in] other знаковое целочисленное значение
     * @return новый объект, являющийся суммой рационального числа и числа стандартного типа
     */
    template <typename OtherT>
    Rational_number<T> operator+(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        int64_t numerator = this->numtor + this->dentor * other;

        if (checkOverFlow<T>(numerator))
            throw RationalOverflowError<int64_t>("", __FILE__, __LINE__, "Rational_number<T> operator+(const OtherT &other) const", numerator);

        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>(numerator, this->dentor);
    }

    /**
     * @brief Перегрузка оператора += со стандартными типами
     *
     * @param[in] other знаковое целочисленное значение
     * @return ссылка на измененный элемент
     */
    template <typename OtherT>
    Rational_number<T> &operator+=(const OtherT &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        int64_t numerator = this->numtor + this->dentor * other;

        if (checkOverFlow<T>(numerator))
            throw RationalOverflowError<int64_t>("", __FILE__, __LINE__, "Rational_number<T> operator+(const OtherT &other) const", numerator);

        this->numtor = static_cast<T>(numerator);
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    /**
     * @brief Двуместный оператор для сложения целочисленных знаковых типов с рациональными числами
     *
     * @param[in] num целочисленное знаковое значение
     * @param[in] other рациональное число
     * @return рациональное число, являющееся суммой двух поступивших значений
     */
    friend Rational_number<T> operator+(const int64_t &num, const Rational_number<T> &other)
    {
        return Rational_number<T>(num) + other;
    }

    /*
        Сложение с комплексными числами и др. операции с +
    */

    /**
     * @brief Перегрузка оператора сложения с комплексным числом
     *
     * @param[in] other комплексное число
     * @return новый объект, являющийся суммой рационального и комплексного чисел
     */
    template <typename OtherT = double, typename OtherU = OtherT>
    Complex_number<OtherT, OtherU> operator+(const Complex_number<OtherT, OtherU> &other) const
    {
        return Complex_number<OtherT, OtherU>(static_cast<OtherT>(static_cast<double>(this->numtor) / this->dentor)) + other;
    }

    /**
     * @brief Оператор префиксного инкримента
     *
     * @return ссылка на измененный элемент
     */
    Rational_number<T> &operator++()
    {
        this->numtor += this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    /**
     * @brief Оператор постфиксного инкримента
     *
     * @return ссылка на измененный элемент
     */
    Rational_number<T> &operator++(int val)
    {
        this->numtor += this->dentor;
        if (this->numtor == 0)
            this->dentor = 1;
        return *this;
    }

    /*
        Вычитание рациональных чисел
    */

    /**
     * @brief Перегрузка оператора вычитания с рациональным числом
     *
     * @param[in] other рациональное число
     * @return новый объект, являющийся разностью двух рациональных чисел
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
     * @param[in] other рациональное число
     * @return ссылка на измененный элемент
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

    /*
        Вычитание стандартных типов
    */

    /**
     * @brief Перегрузка оператора вычитания со стандартными типами
     *
     * @param[in] other знаковое целочисленное значение
     * @return новый объект, являющийся разностью рационального числа и числа стандартного типа
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
     * @param[in] other знаковое целочисленное значение
     * @return ссылка на измененный элемент
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
     * @brief Двуместный оператор для вычитания целочисленных знаковых типов с рациональными числами
     *
     * @param[in] num целочисленное знаковое значение
     * @param[in] other рациональное число
     * @return рациональное число, являющееся разностью двух поступивших значений
     */
    friend Rational_number<T> operator-(const int64_t &num, const Rational_number<T> &other)
    {
        return Rational_number<T>(num) - other;
    }

    /*
        Вычитание комплексных чисел, и др. операции с -
    */

    /**
     * @brief Перегрузка оператора вычитания с комплексным числом
     *
     * @param[in] other комплексное число
     * @return новый объект, являющийся разностью рационального и комплексного числа
     */
    template <typename OtherT = double, typename OtherU = OtherT>
    Complex_number<OtherT, OtherU> operator-(const Complex_number<OtherT, OtherU> &other) const
    {
        return Complex_number<OtherT, OtherU>(static_cast<OtherT>(double(this))) - other;
    }

    /**
     * @brief Оператор унарного минуса
     *
     * @return число со знаком минус
     */
    Rational_number<T> operator-() const
    {
        return Rational_number<T>(-this->numtor, this->dentor);
    }

    /*
        Умножение на рациональные числа
    */

    /**
     * @brief Перегрузка умножения на рациональное число
     *
     * @param[in] other рациональное число
     * @return новый объект, являющийся результатом умножния
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
     * @param[in] other рациональное число
     * @return ссылка на измененный элемент
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

    /*
        Умножение на стандартный тип
    */

    /**
     * @brief Перегрузка оператора умножения на стандартный тип
     *
     * @param[in] other знаковое целочисленное значение
     * @return новый объект, являющийся результатом умножния рационального и знакового целочисленного значения
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
     * @param[in] other знаковое целочисленное значение
     * @return ссылка на измененный элемент
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
     * @brief Двуместный оператор для умножения целочисленных знаковых типов с рациональными числами
     *
     * @param[in] num целочисленное знаковое значение
     * @param[in] other рациональное число
     * @return рациональное число, являющееся разностью двух поступивших значений
     */
    friend Rational_number<T> operator*(const int64_t &num, const Rational_number<T> &other)
    {
        return Rational_number<T>(num) * other;
    }

    /*
        Умножение на комплексное число
    */

    /**
     * @brief Перегрузка оператора умножения на комплексное число
     *
     * @param[in] other комплексное число
     * @return новый объект, являющийся результатом умножния рационального и комплексного числа
     */
    template <typename OtherT = double, typename OtherU = OtherT>
    Complex_number<OtherT, OtherU> operator*(const Complex_number<OtherT, OtherU> &other) const
    {
        OtherT re = static_cast<OtherT>(static_cast<double>(this->numtor) / this->dentor * other.getReal());
        OtherU im = static_cast<OtherU>(static_cast<double>(this->numtor) / this->dentor * other.getImag());
        return Complex_number<OtherT, OtherU>(re, im);
    }

    /*
        Деление на рациональные числа
    */

    /**
     * @brief Перегрузка оператора деления на рациональное число
     *
     * @param[in] other рациональное число
     * @return рациональное число, являющееся частным двух поступивших значений
     */
    Rational_number<T> operator/(const Rational_number<T> &other) const
    {
        if (other.getNumtor() == 0)
            throw RationalZeroDivisionError<int64_t>("", __FILE__, __LINE__, "Rational_number<T> operator/(const Rational_number<T> &other) const", this->to_string(), other.to_string());
        T numerator = this->numtor * other.getDentor();
        T denominator = this->dentor * other.getNumtor();
        if (numerator == 0)
            return Rational_number<T>(0, 1);
        return Rational_number<T>((denominator > 0 ? 1 : -1) * numerator, (denominator > 0 ? 1 : -1) * denominator);
    }

    /**
     * @brief Перегрузка оператора /= на рациональное число
     *
     * @param[in] other рациональное число
     * @return [Rational_number<T>&] - ссылка на измененный элемент
     */
    Rational_number<T> &operator/=(const Rational_number<T> &other)
    {
        if (other.getNumtor() == 0)
            throw RationalZeroDivisionError<int64_t>("", __FILE__, __LINE__, "Rational_number<T> &operator/=(const Rational_number<T> &other)", this->to_string(), other.to_string());

        this->numtor *= other.getDentor();
        this->dentor *= other.getNumtor();
        this->numtor *= (dentor > 0 ? 1 : -1);
        this->dentor *= (dentor > 0 ? 1 : -1);
        return *this;
    }

    /*
        Деление на стандартный тип
    */

    /**
     * @brief Перегрузка оператора деления на стандартный тип
     *
     * @param[in] other знаковое целочисленное значение
     * @return новый объект, являющийся результатом деления рационального числа и знакового целочисленного значения
     */
    template <typename OtherT>
    Rational_number<T> operator/(const OtherT &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");

        if (other == 0)
            throw RationalZeroDivisionError<int64_t>("", __FILE__, __LINE__, "Rational_number<T> operator/(const OtherT &other) const", this->to_string(), std::to_string(other));

        T numerator = this->numtor;
        T denominator = this->dentor * static_cast<T>(other);
        return Rational_number<T>((denominator > 0 ? 1 : -1) * numerator, (denominator > 0 ? 1 : -1) * denominator);
    }

    /**
     * @brief Перегрузка оператора /= на стандартный тип
     *
     * @param[in] other знаковое целочисленное значение
     * @return ссылка на измененный элемент
     */
    template <typename OtherT>
    Rational_number<T> &operator/=(const OtherT &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        if (other == 0)
            throw RationalZeroDivisionError<int64_t>("", __FILE__, __LINE__, "Rational_number<T> &operator/=(const OtherT &other)", this->to_string(), std::to_string(other));

        if (other == 0)
            throw std::logic_error("Cant devide by zero");

        this->dentor *= static_cast<T>(other);
        this->dentor *= (dentor > 0 ? 1 : -1);
        return *this;
    }

    /**
     * @brief Двуместный оператор для деления целочисленных знаковых типов с рациональными числами
     *
     * @param[in] num целочисленное знаковое значение
     * @param[in] other рациональное число
     * @return рациональное число, являющееся частным двух поступивших значений
     */
    friend Rational_number<T> operator/(const int64_t &num, const Rational_number<T> &other)
    {
        return Rational_number<T>(num) / other;
    }

    /*
        Деление на комплексное число
    */

    /**
     * @brief Перегрузка оператора деления на комплексное число
     *
     * @param[in] other комплексное число
     * @return новый объект, являющийся результатом деления рационального и комплексного числа
     */
    template <typename OtherT = double, typename OtherU = OtherT>
    Complex_number<OtherT, OtherU> operator/(const Complex_number<OtherT, OtherU> &other) const
    {
        Complex_number<OtherT, OtherU> tmp(static_cast<double>(this->numtor) / this->dentor);
        return tmp / other;
    }

    /*
        Операторы сравнения
    */

    /**
     * @brief Перегрузка оператора < для сравнения двух рациональных чисел
     *
     * @param[in] other Рациональное число
     * @return true
     * @return false
     */
    bool operator<(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) < (other.getNumtor() * this->dentor);
    }

    /**
     * @brief Перегрузка оператора < для сравнения рационального числа и числа целочисленного знакового типа
     *
     * @param[in] other Рациональное число
     * @param[in] num Целочисленное знаковое значение
     * @return true
     * @return false
     */
    friend bool operator<(const Rational_number<T> &other, const int64_t &num)
    {
        return other < Rational_number<T>(num);
    }

    /**
     * @brief Перегрузка оператора < для сравнения рационального числа и числа целочисленного знакового типа
     *
     * @param[in] num Целочисленное знаковое значение
     * @param[in] other Рациональное число
     * @return true
     * @return false
     */
    friend bool operator<(const int64_t &num, const Rational_number<T> &other)
    {
        return other < Rational_number<T>(num);
    }

    // =========================================

    /**
     * @brief Перегрузка оператора <= для сравнения двух рациональных чисел
     *
     * @param[in] other Рациональное число
     * @return true
     * @return false
     */
    bool operator<=(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) <= (other.getNumtor() * this->dentor);
    }

    /**
     * @brief Перегрузка оператора <= для сравнения рационального числа и числа целочисленного знакового типа
     *
     * @param[in] other Рациональное число
     * @param[in] num Целочисленное знаковое значение
     * @return true
     * @return false
     */
    friend bool operator<=(const Rational_number<T> &other, const int64_t &num)
    {
        return other <= Rational_number<T>(num);
    }

    /**
     * @brief Перегрузка оператора <= для сравнения рационального числа и числа целочисленного знакового типа
     *
     * @param[in] num Целочисленное знаковое значение
     * @param[in] other Рациональное число
     * @return true
     * @return false
     */
    friend bool operator<=(const int64_t &num, const Rational_number<T> &other)
    {
        return other <= Rational_number<T>(num);
    }

    // =========================================

    /**
     * @brief Перегрузка оператора > для сравнения двух рациональных чисел
     *
     * @param[in] other Рациональное число
     * @return true
     * @return false
     */
    bool operator>(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) > (other.getNumtor() * this->dentor);
    }

    /**
     * @brief Перегрузка оператора > для сравнения рационального числа и числа целочисленного знакового типа
     *
     * @param[in] other Рациональное число
     * @param[in] num Целочисленное знаковое значение
     * @return true
     * @return false
     */
    friend bool operator>(const Rational_number<T> &other, const int64_t &num)
    {
        return other > Rational_number<T>(num);
    }

    /**
     * @brief Перегрузка оператора > для сравнения рационального числа и числа целочисленного знакового типа
     *
     * @param[in] num Целочисленное знаковое значение
     * @param[in] other Рациональное число
     * @return true
     * @return false
     */
    friend bool operator>(const int64_t &num, const Rational_number<T> &other)
    {
        return other > Rational_number<T>(num);
    }

    // =========================================

    /**
     * @brief Перегрузка оператора >= для сравнения двух рациональных чисел
     *
     * @param[in] other Рациональное число
     * @return true
     * @return false
     */
    bool operator>=(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) >= (other.getNumtor() * this->dentor);
    }

    /**
     * @brief Перегрузка оператора >= для сравнения рационального числа и числа целочисленного знакового типа
     *
     * @param[in] other Рациональное число
     * @param[in] num Целочисленное знаковое значение
     * @return true
     * @return false
     */
    friend bool operator>=(const Rational_number<T> &other, const int64_t &num)
    {
        return other >= Rational_number<T>(num);
    }

    /**
     * @brief Перегрузка оператора >= для сравнения рационального числа и числа целочисленного знакового типа
     *
     * @param[in] num Целочисленное знаковое значение
     * @param[in] other Рациональное число
     * @return true
     * @return false
     */
    friend bool operator>=(const int64_t &num, const Rational_number<T> &other)
    {
        return other >= Rational_number<T>(num);
    }

    // =========================================

    /**
     * @brief Перегрузка оператора == для сравнения двух рациональных чисел
     *
     * @param[in] other Рациональное число
     * @return true
     * @return false
     */
    bool operator==(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) == (other.getNumtor() * this->dentor);
    }

    /**
     * @brief Перегрузка оператора == для сравнения рационального числа и числа целочисленного знакового типа
     *
     * @param[in] other Рациональное число
     * @param[in] num Целочисленное знаковое значение
     * @return true
     * @return false
     */
    friend bool operator==(const Rational_number<T> &other, const int64_t &num)
    {
        return other == Rational_number<T>(num);
    }

    /**
     * @brief Перегрузка оператора == для сравнения рационального числа и числа целочисленного знакового типа
     *
     * @param[in] num Целочисленное знаковое значение
     * @param[in] other Рациональное число
     * @return true
     * @return false
     */
    friend bool operator==(const int64_t &num, const Rational_number<T> &other)
    {
        return other == Rational_number<T>(num);
    }

    // =========================================

    /**
     * @brief Перегрузка оператора != для сравнения двух рациональных чисел
     *
     * @param[in] other Рациональное число
     * @return true
     * @return false
     */
    bool operator!=(const Rational_number<T> &other) const
    {
        return (this->numtor * other.getDentor()) != (other.getNumtor() * this->dentor);
    }

    /**
     * @brief Перегрузка оператора != для сравнения рационального числа и числа целочисленного знакового типа
     *
     * @param[in] other Рациональное число
     * @param[in] num Целочисленное знаковое значение
     * @return true
     * @return false
     */
    friend bool operator!=(const Rational_number<T> &other, const int64_t &num)
    {
        return other != Rational_number<T>(num);
    }

    /**
     * @brief Перегрузка оператора != для сравнения рационального числа и числа целочисленного знакового типа
     *
     * @param[in] num Целочисленное знаковое значение
     * @param[in] other Рациональное число
     * @return true
     * @return false
     */
    friend bool operator!=(const int64_t &num, const Rational_number<T> &other)
    {
        return other != Rational_number<T>(num);
    }

    // =========================================

    /**
     * @brief перезрузка оператора вывода << для печати числа
     *
     * @param[in, out] out поток
     * @param[in] other число
     * @return поток
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
     * @brief Получение значения по модулю типа
     *
     * @return модуль числа типа double
     */
    double abs() const
    {
        return std::abs(static_cast<double>(this->numtor) / (this->dentor));
    }

    /**
     * @brief Преобразование числа к строке
     *
     * @return число в виде строки
     */
    std::string to_string() const
    {
        return std::to_string(this->numtor) + '/' + std::to_string(this->dentor);
    }
};
