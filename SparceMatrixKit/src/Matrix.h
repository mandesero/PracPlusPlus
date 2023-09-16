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
     * Конструктор, создающий матрицу из нулей.
     */
    static Matrix<rows, columns, T> zeros()
    {
        Matrix<rows, columns, T> result{};
        for (int i = 1; i < rows + 1; ++i)
        {
            for (int j = 1; j < columns + 1; ++j)
            {
                result.set(i, j, T(0, 1));
            }
        }
        return result;
    }

    /**
     * Конструктор, создающий матрицу из единиц.
     */
    static Matrix<rows, columns, T> ones()
    {
        Matrix<rows, columns, T> result{};
        for (int i = 1; i < rows + 1; ++i)
        {
            for (int j = 1; j < columns + 1; ++j)
            {
                result.set(i, j, T(1));
            }
        }
        return result;
    }

    /**
     * Конструктор, создающий единичную матрицу.
     */
    static Matrix<rows, columns, T> eye()
    {
        Matrix<rows, columns, T> result{};
        int size = std::min(rows, columns);
        for (int i = 1; i < size + 1; ++i)
        {
            result.set(i, i, T(1));
        }
        return result;
    }

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
     * Если значение меньше epsilon, элемент не добавляется в словарь.
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
    Matrix<rows, columns, T> operator+(const Matrix<rows, columns, T> &other)
    {
        Matrix<rows, columns, T> result;
        for (int i = 1; i < rows + 1; ++i)
        {
            for (int j = 1; j < columns + 1; ++j)
            {
                T value = at(i, j) + other.at(i, j);
                result.set(i, j, value);
            }
        }
        return result;
    }

    /**
     * Перегрузка оператора вычитания для матриц с проверкой совпадения размеров и возможности приведения типов чисел.
     * @tparam OtherT Тип чисел во второй матрице.
     * @param other Вычитаемая матрица.
     * @return Новая матрица, являющаяся результатом вычитания.
     */
    Matrix<rows, columns, T> operator-(const Matrix<rows, columns, T> &other)
    {
        Matrix<rows, columns, T> result;
        for (int i = 1; i < rows + 1; ++i)
        {
            for (int j = 1; j < columns + 1; ++j)
            {
                T value = at(i, j) - other.at(i, j);
                result.set(i, j, value);
            }
        }
        return result;
    }

    /**
     * Перегрузка оператора умножения для матриц с проверкой совпадения размеров и возможности приведения типов чисел.
     * @tparam OtherColumns Количество столбцов во второй матрице.
     * @tparam OtherT Тип чисел во второй матрице.
     * @param other Матрица для умножения.
     * @return Новая матрица, являющаяся результатом умножения.
     */
    template <int OtherColumns>
    Matrix<rows, OtherColumns, T> operator*(const Matrix<columns, OtherColumns, T> &other)
    {
        Matrix<rows, OtherColumns, T> result;
        for (int i = 1; i < rows + 1; ++i)
        {
            for (int k = 1; k < OtherColumns + 1; ++k)
            {
                T sum = T();
                for (int j = 1; j < columns + 1; ++j)
                {
                    sum += at(i, j) * other.at(j, k);
                }
                result.set(i, k, sum);
            }
        }
        return result;
    }

    /**
     * Перегрузка оператора унарного минуса для инверсии знака всех элементов матрицы.
     * @return Новая матрица, являющаяся результатом инверсии знака всех элементов текущей матрицы.
     */
    Matrix<rows, columns, T> operator-() const
    {
        Matrix<rows, columns, T> result(*this);
        for (auto &pair : result.data)
        {
            pair.second = -pair.second;
        }
        return result;
    }

    /**
     * Перегрузка оператора транспонирования для возврата транспонированной матрицы.
     * @return Новая матрица, являющаяся транспонированной текущей матрицей.
     */
    Matrix<columns, rows, T> operator~() const
    {
        Matrix<columns, rows, T> result;
        for (int i = 1; i < columns + 1; ++i)
        {
            for (int j = 1; j < rows + 1; ++j)
            {
                result.set(i, j, at(j, i));
            }
        }
        return result;
    }

    /**
     * Оператор () для доступа к элементу матрицы по индексам.
     * @param row Индекс строки.
     * @param column Индекс столбца.
     * @return Ссылка на элемент матрицы в позиции (row, column).
     * @throws std::out_of_range Если индексы выходят за пределы размеров матрицы.
     */
    const T &operator()(int row, int column) const
    {
        if (row < 1 || row > rows + 1 || column < 1 || column > columns + 1)
        {
            throw std::out_of_range("Matrix indices out of range");
        }
        return this->at(row, column);
    }
};
