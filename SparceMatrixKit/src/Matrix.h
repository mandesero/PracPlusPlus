#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>
#include <map>
#include <utility>

template <int rows, int columns, typename T>
class Matrix
{
protected:
    std::map<std::pair<int, int>, T> data; /**< Словарь для хранения элементов матрицы */
    double eps;                            /**< Пороговое значение для признания числа нулевым */

public:
    /**
     * Конструктор класса Matrix.
     * @param epsilon Пороговое значение для признания числа нулевым. По умолчанию равно 0.
     */
    Matrix(double epsilon = 0) : eps(epsilon) {}

    /**
     * Получение значения элемента матрицы по заданным индексам.
     * Если элемент не найден, возвращается нулевое значение типа T.
     * @param row Индекс строки.
     * @param column Индекс столбца.
     * @return Значение элемента матрицы.
     */
    const T &at(int row, int column) const
    {
        auto it = data.find(std::make_pair(row, column));
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
     * Установка значения элемента матрицы по заданным индексам.
     * Если значение меньше epsilon, элемент удаляется из словаря.
     * @param row Индекс строки.
     * @param column Индекс столбца.
     * @param value Значение элемента матрицы.
     */
    void set(int row, int column, const T &value)
    {
        if (value.abs() >= eps)
            data[std::make_pair(row, column)] = value;
    }

    /**
     * Возвращает строковое представление матрицы.
     * @return Строковое представление матрицы.
     */
    std::string to_string() const
    {
        std::string result;
        for (int i = 1; i < rows + 1; ++i)
        {
            for (int j = 1; j < columns + 1; ++j)
                result += at(i, j).to_string() + " ";
            result += "\n";
        }
        return result;
    }

    /**
     * Перегрузка оператора сложения для матриц с проверкой совпадения размеров и возможности приведения типов чисел.
     * @tparam OtherT Тип чисел во второй матрице.
     * @param other Матрица для сложения.
     * @return Новая матрица, являющаяся результатом сложения.
     */
    template <typename OtherT>
    Matrix<rows, columns, T> operator+(const Matrix<rows, columns, OtherT> &other)
    {
        static_assert(std::is_convertible<OtherT, T>::value, "Invalid type conversion");
        Matrix<rows, columns, T> result;
        for (int i = 1; i < rows + 1; ++i)
        {
            for (int j = 1; j < columns + 1; ++j)
            {
                T value = at(i, j) + static_cast<T>(other.at(i, j));
                result.set(i, j, value);
            }
        }
        return result;
    }
};
