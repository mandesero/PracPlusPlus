#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>
#include <map>

template <int len, typename T>
class Vector
{
protected:
    std::map<int, T> data; /**< Словарь для хранения элементов вектора */
    double eps;            /**< Пороговое значение для признания числа нулевым */

public:
    /**
     * Конструктор класса Vector.
     * @param epsilon Пороговое значение для признания числа нулевым. По умолчанию равно 0.
     */
    Vector(double epsilon = 0) : eps(epsilon) {}

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
     * @return Новая вектор, являющаяся результатом сложения.
     */

    Vector<len, T> operator+(const Vector<len, T> &other) const
    {
        Vector<len, T> result;
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
     * @return Новая вектор, являющаяся результатом сложения.
     */
    template <typename OtherT = double, typename OtherU = OtherT>
    Vector<len, Complex_number<OtherT, OtherU>> operator+(const Vector<len, Complex_number<OtherT, OtherU>> &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        Vector<len, Complex_number<OtherT, OtherU>> result;
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
     * @return Новая вектор, являющаяся разностью двух вектров.
     */
    template <typename OtherT>
    Vector<len, T> operator-(const Vector<len, OtherT> &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        Vector<len, T> result;
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
     * @return Новая вектор, являющаяся разностью двух вектров.
     */
    template <typename OtherT = double, typename OtherU = OtherT>
    Vector<len, Complex_number<OtherT, OtherU>> operator-(const Vector<len, Complex_number<OtherT, OtherU>> &other) const
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        Vector<len, Complex_number<OtherT, OtherU>> result;
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
    Vector<len, T> operator*(const OtherT &other) const
    {
        Vector<len, T> result;
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
    Vector<len, Complex_number<OtherT, OtherU>> operator*(const Complex_number<OtherT, OtherU> &other) const
    {
        Vector<len, Complex_number<OtherT, OtherU>> result;
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
    Vector<len, T> operator/(const OtherT &other) const
    {
        Vector<len, T> result;
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
    Vector<len, Complex_number<OtherT, OtherU>> operator/(const Complex_number<OtherT, OtherU> &other) const
    {
        Vector<len, Complex_number<OtherT, OtherU>> result;
        for (int i = 1; i < len + 1; ++i)
        {
            Complex_number<OtherT, OtherU> value = at(i) / other;
            result.set(i, value);
        }
        return result;
    }
};