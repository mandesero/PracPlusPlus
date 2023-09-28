#pragma once

#include "Rational.h"
#include "Matrix.h"

#include <iostream>

#include <type_traits>
#include <cmath>
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>

/**
 * @brief Шаблонный класс для хранения разреженных векторов
 * 
 * @tparam T - тип элементов вектора
 */
template <typename T>
class Vector
{
protected:
    std::map<int, T> data; /**< Словарь для хранения элементов вектора */
    double eps;            /**< Пороговое значение для признания числа нулевым */
    int len;               /**< Длина вектора */

public:
    Vector() {}

    /**
     * Конструктор класса Vector.
     * @param len длина вектора
     * @param epsilon Пороговое значение для признания числа нулевым. По умолчанию равно 0.
     */
    Vector(int len, double epsilon = 0) : eps(epsilon), len(len) {}

    /**
     * Получение значения элемента вектора по заданным индексам.
     * Если элемент не найден, возвращается нулевое значение типа T.
     * @param index Индекс элемента.
     * @return Значение элемента вектора.
     */
    const T &at(int index) const
    {
        auto it = data.find(index);
        if (it == data.end())
        {
            static const T zero;
            return zero;
        }
        else
        {
            return it->second;
        }
    }

    /**
     * Установка значения элемента вектора по заданному индексу.
     * Если значение меньше epsilon, элемент не добавляется в словарь.
     * @param row Индекс элемента.
     * @param value Значение элемента вектора.
     */
    void set(int index, const T &value)
    {
        if (value.abs() >= eps)
            data[index] = value;
    }

    /**
     * @brief Возвращает длину вектора
     *
     * @return Длина вектора
     */
    const int getLen() const
    {
        return len;
    }

    /**
     * @brief Возвращает eps
     *
     * @return eps
     */
    const double getEps() const
    {
        return eps;
    }

    /**
     * @brief Возвращает словарь, где храняться числа вектора
     *
     * @return const std::map<int, T>
     */
    const std::map<int, T> getData() const
    {
        return data;
    }

    /**
     * Возвращает строковое представление вектора.
     * @return Строковое представление вектора.
     */
    std::string to_string() const
    {
        std::string result;
        for (int i = 1; i < len + 1; ++i)
        {
            result += at(i).to_string() + " ";
        }
        return result;
    }

    /**
     * Оператор () для доступа к элементу вектора по индексу.
     * @param row Индекс элемента.
     * @return Ссылка на элемент вектора в позиции index.
     * @throws std::out_of_range Если индекс выходит за пределы размеров вектора.
     */
    const T &operator()(int index) const
    {
        if (index < 1 || index > len + 1)
        {
            throw std::out_of_range("Vector indices out of range");
        }
        return this->at(index);
    }

    /**
     * Перегрузка оператора сложения для векторов с проверкой совпадения размеров и возможности приведения типов чисел.
     * @tparam OtherT Тип чисел во втором векторе.
     * @param other Вектор для сложения.
     * @return Новый вектор, являющаяся результатом сложения.
     */
    Vector<T> operator+(const Vector<T> &other) const
    {
        if (len != other.getLen())
            throw std::logic_error("Cannot add vectors of different sizes");

        Vector<T> result(len);
        for (int i = 1; i < len + 1; ++i)
        {
            T value = at(i) + other.at(i);
            result.set(i, value);
        }
        return result;
    }

    /**
     * Перегрузка оператора сложения для векторов с проверкой совпадения размеров и возможности приведения типов чисел.
     * @tparam OtherU Тип мнимой части.
     * @param other Множитель.
     * @param other Вектор для сложения.
     * @return Новый вектор, являющаяся результатом сложения.
     */
    template <typename OtherT = double, typename OtherU = OtherT>
    Vector<Complex_number<OtherT, OtherU>> operator+(const Vector<Complex_number<OtherT, OtherU>> &other) const
    {
        if (len != other.getLen())
            throw std::logic_error("Cannot add vectors of different sizes");

        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        Vector<Complex_number<OtherT, OtherU>> result(len);
        for (int i = 1; i < len + 1; ++i)
        {
            T value = at(i) + static_cast<T>(other.at(i));
            result.set(i, value);
        }
        return result;
    }

    /**
     * Перегрузка оператора вычитания для векторов с проверкой совпадения размеров и возможности приведения типов чисел.
     * @tparam OtherT Тип чисел во втором векторе.
     * @param other Вычитаемый вектор.
     * @return Новый вектор, являющаяся разностью двух вектров.
     */
    template <typename OtherT>
    Vector<T> operator-(const Vector<OtherT> &other) const
    {
        if (len != other.getLen())
            throw std::logic_error("Cannot add vectors of different sizes");

        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        Vector<T> result(len);
        for (int i = 1; i < len + 1; ++i)
        {
            T value = at(i) - static_cast<T>(other.at(i));
            result.set(i, value);
        }
        return result;
    }

    /**
     * Перегрузка оператора вычитания для векторов с проверкой совпадения размеров и возможности приведения типов чисел.
     * @tparam OtherU Тип мнимой части.
     * @param other Множитель.
     * @param other Вычитаемый вектор.
     * @return Новый вектор, являющаяся разностью двух вектров.
     */
    template <typename OtherT = double, typename OtherU = OtherT>
    Vector<Complex_number<OtherT, OtherU>> operator-(const Vector<Complex_number<OtherT, OtherU>> &other) const
    {
        if (len != other.getLen())
            throw std::logic_error("Cannot add vectors of different sizes");
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        Vector<Complex_number<OtherT, OtherU>> result(len);
        for (int i = 1; i < len + 1; ++i)
        {
            T value = at(i) - static_cast<T>(other.at(i));
            result.set(i, value);
        }
        return result;
    }

    /**
     * Перегрузка оператора умножения вектора на число(не комплексное) с проверкой совпадения размеров и возможности приведения типов чисел.
     * @tparam OtherT Тип чисел во втором векторе.
     * @param other Множитель.
     * @return Новый вектор, являющийся произведением числа на вектор.
     */
    template <typename OtherT>
    Vector<T> operator*(const OtherT &other) const
    {
        Vector<T> result(len);
        for (int i = 1; i < len + 1; ++i)
        {
            T value = at(i) * other;
            result.set(i, value);
        }
        return result;
    }

    /**
     * Перегрузка оператора умножения вектора на комлексное число проверкой совпадения размеров векторов.
     * @tparam OtherT Тип действительной части.
     * @tparam OtherU Тип мнимой части.
     * @param other Множитель.
     * @return Новый вектор, являющийся произведением числа на вектор.
     */
    template <typename OtherT = double, typename OtherU = OtherT>
    Vector<Complex_number<OtherT, OtherU>> operator*(const Complex_number<OtherT, OtherU> &other) const
    {
        Vector<Complex_number<OtherT, OtherU>> result(len);
        for (int i = 1; i < len + 1; ++i)
        {
            Complex_number<OtherT, OtherU> value = at(i) * other;
            result.set(i, value);
        }
        return result;
    }

    /**
     * Перегрузка оператора умножения вектора на комлексное число проверкой совпадения размеров векторов.
     * @tparam OtherT Тип действительной части.
     * @tparam OtherU Тип мнимой части.
     * @param other Множитель.
     * @return Новый вектор, являющийся произведением числа на вектор.
     */
    template <typename OtherT>
    Vector<T> operator/(const OtherT &other) const
    {
        Vector<T> result(len);
        for (int i = 1; i < len + 1; ++i)
        {
            T value = at(i) / other;
            result.set(i, value);
        }
        return result;
    }

    /**
     * Перегрузка оператора умножения вектора на комлексное число проверкой совпадения размеров векторов.
     * @tparam OtherT Тип действительной части.
     * @tparam OtherU Тип мнимой части.
     * @param other Множитель.
     * @return Новый вектор, являющийся произведением числа на вектор.
     */
    template <typename OtherT = double, typename OtherU = OtherT>
    Vector<Complex_number<OtherT, OtherU>> operator/(const Complex_number<OtherT, OtherU> &other) const
    {
        Vector<Complex_number<OtherT, OtherU>> result(len);
        for (int i = 1; i < len + 1; ++i)
        {
            Complex_number<OtherT, OtherU> value = at(i) / other;
            result.set(i, value);
        }
        return result;
    }

    /**
     * @brief Перегрузка оператора [], позволяет получать доступ к элементу вектора по индексу
     *
     * @param index индекс элемента
     * @return ссылка на элемент
     */
    T &operator[](int index)
    {
        if (index < 1 || index > len)
            throw std::logic_error("Out of range");
        return data[index];
    }

    /**
     * @brief Перегрузка оператора умножения для умножения вектора (размера n) на матрицу (размера n x m)
     *
     * @param other Матрица размера (n x m)
     * @return Вектор, являющийся результатом умножения вектора на матрицу
     */
    // Vector<T> operator*(const Matrix<T> &other)
    // {
    //     if (len != other.getRows())
    //         throw std::logic_error("Invalid operands");
    //     Vector<T> result(other.getColumns());

    //     for (int j = 1; j < other.getColumns() + 1; ++j)
    //     {
    //         T sum = T();
    //         for (int k = 1; k < len + 1; ++k)
    //         {
    //             sum += at(k) * other.at(k, j);
    //         }
    //         result.set(j, sum);
    //     }

    //     return result;
    // }

    /**
     * @brief Перегрузка оператора ==, для проверки векторов на равенство
     *
     * @param other
     * @return true если векторы равны
     * @return false если векторы различны
     */
    bool operator==(const Vector<T> &other) const
    {
        return data == other.getData() && eps == other.getEps() && len == other.getLen();
    }
};