#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>
#include <map>
#include <utility>
#include <memory>
#include <vector>

#include "Vector.h"
template <typename T>
class Vector;

struct Matrix_coords
{
    int r1; /**< Начальная строка среза. Если -1, то с начала матрицы. */
    int c1; /**< Начальный столбец среза. Если -1, то с начала матрицы. */
    int r2; /**< Конечная строка среза. Если -1, то до конца матрицы. */
    int c2; /**< Конечный столбец среза. Если -1, то до конца матрицы. */

    Matrix_coords(int r1, int c1, int r2, int c2) : r1(r1), c1(c1), r2(r2), c2(c2) {}

    Matrix_coords(int r1, int c1) : r1(r1), c1(c1), r2(r1), c2(c1) {}
};

struct Matrix_row_coord
{
    int row;
    Matrix_row_coord(int row) : row(row) {}
};

struct Matrix_column_coord
{
    int column;
    Matrix_column_coord(int column) : column(column) {}
};

template <typename T>
class Matrix;

template <typename T>
class Matrix_proxy;

template <typename T>
class Matrix_proxy
{
private:
    Matrix<T> *matrix;
    int row;
    int column;
    Matrix_coords coords;
    int columns;
    int rows;

public:
    Matrix_proxy(Matrix<T> *matrix, int rows, int columns, int row, int column, Matrix_coords coords) : matrix(matrix), columns(columns), row(row), rows(rows), column(column), coords(coords) {}

    auto &operator[](int index)
    {
        if (column != -1 && (index < 1 || index > rows))
            throw std::logic_error("Index out of range");
        if (row != -1 && (index < 1 || index > columns))
            throw std::logic_error("Index out of range");
        return column == -1 ? matrix->at(row, index) : matrix->at(index, column);
    }

    auto &operator[](std::pair<int, int> idxs)
    {
        if (idxs.first < 1 || idxs.first > coords.c2 - 1 || idxs.second < 1 || idxs.second > coords.r2 - 1)
            throw std::logic_error("Index out of range");

        return matrix->at(idxs.first + coords.r1 - 1, idxs.second + coords.c1 - 1);
    }

    std::string to_string() const
    {
        std::string result;
        if (column != -1)
        {
            for (int i = 1; i <= rows; ++i)
                result += matrix->at(i, column).to_string() + '\n';
        }
        else if (row != -1)
        {
            for (int i = 1; i <= columns; ++i)
                result += matrix->at(row, i).to_string() + ' ';
        }
        else
        {
            int c1 = coords.c1;
            int c2 = coords.c2;
            int r1 = coords.r1;
            int r2 = coords.r2;

            for (int i = c1; i <= c2; ++i)
            {
                for (int j = r1; j <= r2; ++j)
                    result += matrix->at(i, j).to_string() + " ";
                result += "\n";
            }
        }
        return result;
    }

    void delete_ptr()
    {
        matrix = nullptr;
    }

    auto create_vector()
    {
        if (column == -1 && row == -1)
            throw std::logic_error("Not a vector");

        if (column != -1)
        {
            Vector<T> result(columns);
            for (int i = 1; i <= rows; ++i)
                result[i] += matrix->at(i, column);
            return result;
        }
        else
        {
            Vector<T> result(rows);
            for (int i = 1; i <= columns; ++i)
                result[i] = matrix->at(row, i);
            return result;
        }
    }

    Matrix_proxy<T> operator[](Matrix_coords &&new_coords)
    {
        int c1 = new_coords.c1;
        int c2 = new_coords.c2;
        int r1 = new_coords.r1;
        int r2 = new_coords.r2;

        if (c1 == -1 || r1 == -1)
        {
            c1 = 1;
            r1 = 1;
        }
        if (r2 == -1 || c2 == -1)
        {
            r2 = rows;
            c2 = columns;
        }

        Matrix_coords tmp(
            std::min(r1, coords.r1), std::min(c1, coords.c1),
            std::max(r2, coords.r2), std::max(c2, coords.c2));

        auto new_proxy = Matrix_proxy<T>(matrix, rows, columns, -1, -1, tmp);
        matrix->add_proxy(new_proxy);
        return new_proxy;
    }
};

/**
 * @brief Класс для представления матрицы.
 * @tparam rows Количество строк в матрице.
 * @tparam columns Количество столбцов в матрице.
 * @tparam T Тип элементов матрицы.
 */
template <typename T>
class Matrix
{
protected:
    std::map<std::pair<int, int>, T> data; /**< Словарь для хранения элементов матрицы */
    double eps;                            /**< Пороговое значение для признания числа нулевым */

    std::vector<Matrix_proxy<T>> proxies;

    int rows;
    int columns;

public:
    void add_proxy(Matrix_proxy<T> &other)
    {
        proxies.push_back(other);
    }

    ~Matrix()
    {
        for (auto &proxy : proxies)
            proxy.delete_ptr();
    }

    const int getRows() const
    {
        return rows;
    }

    const int getColumns() const
    {
        return columns;
    }

    /**
     * @brief Конструктор класса Matrix.
     * @param epsilon Пороговое значение для признания числа нулевым. По умолчанию равно 0.
     */
    Matrix(int rows, int columns, double epsilon = 0) : eps(epsilon), rows(rows), columns(columns) {}

    /**
     * @brief Конструктор, создающий матрицу из нулей.
     */
    static Matrix<T> zeros(int size_1, int size_2)
    {
        Matrix<T> result(size_1, size_2);
        for (int i = 1; i < size_1 + 1; ++i)
        {
            for (int j = 1; j < size_2 + 1; ++j)
            {
                result.set(i, j, T(0, 1));
            }
        }
        return result;
    }

    /**
     * @brief Конструктор, создающий матрицу из единиц.
     */
    static Matrix<T> ones(int size_1, int size_2)
    {
        Matrix<T> result(size_1, size_2);
        for (int i = 1; i < size_1 + 1; ++i)
        {
            for (int j = 1; j < size_2 + 1; ++j)
            {
                result.set(i, j, T(1));
            }
        }
        return result;
    }

    /**
     * @brief Конструктор, создающий единичную матрицу.
     */
    static Matrix<T> eye(int size_1, int size_2)
    {
        Matrix<T> result(size_1, size_2);
        int size = std::min(size_1, size_2);
        for (int i = 1; i < size + 1; ++i)
        {
            result.set(i, i, T(1));
        }
        return result;
    }

    /**
     * @brief Получение значения элемента матрицы по заданным индексам. Если элемент не найден, возвращается нулевое значение типа T.
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
     * @brief Установка значения элемента матрицы по заданным индексам. Если значение меньше epsilon, элемент не добавляется в словарь.
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
     * @brief Возвращает строковое представление матрицы.
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
     * @brief Перегрузка оператора сложения для матриц с проверкой совпадения размеров и возможности приведения типов чисел.
     * @tparam OtherT Тип чисел во второй матрице.
     * @param other Матрица для сложения.
     * @return Новая матрица, являющаяся результатом сложения.
     */
    Matrix<T> operator+(const Matrix<T> &other)
    {
        if (rows != other.getRows() && columns != other.getColumns())
            throw std::logic_error("Cannot add matrix with different sizes");
        Matrix<T> result(rows, columns);

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
     * @brief Перегрузка оператора вычитания для матриц с проверкой совпадения размеров и возможности приведения типов чисел.
     * @tparam OtherT Тип чисел во второй матрице.
     * @param other Вычитаемая матрица.
     * @return Новая матрица, являющаяся результатом вычитания.
     */
    Matrix<T> operator-(const Matrix<T> &other)
    {
        if (rows != other.getRows() && columns != other.getColumns())
            throw std::logic_error("Cannot sub matrix with different sizes");
        Matrix<T> result(rows, columns);
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
     * @brief Перегрузка оператора умножения для матриц с проверкой совпадения размеров и возможности приведения типов чисел.
     * @tparam OtherColumns Количество столбцов во второй матрице.
     * @tparam OtherT Тип чисел во второй матрице.
     * @param other Матрица для умножения.
     * @return Новая матрица, являющаяся результатом умножения.
     */
    Matrix<T> operator*(const Matrix<T> &other)
    {
        if (rows != other.getRows() && columns != other.getColumns())
            throw std::logic_error("Cannot mult matrix with different sizes");
        Matrix<T> result(rows, other.getColumns());

        for (int i = 1; i < rows + 1; ++i)
        {
            for (int k = 1; k < other.getColumns() + 1; ++k)
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
     * @brief Перегрузка оператора унарного минуса для инверсии знака всех элементов матрицы.
     * @return Новая матрица, являющаяся результатом инверсии знака всех элементов текущей матрицы.
     */
    Matrix<T> operator-() const
    {
        Matrix<T> result(*this);
        for (auto &pair : result.data)
        {
            pair.second = -pair.second;
        }
        return result;
    }

    /**
     * @brief Перегрузка оператора транспонирования для возврата транспонированной матрицы.
     * @return Новая матрица, являющаяся транспонированной текущей матрицей.
     */
    Matrix<T> operator~() const
    {
        Matrix<T> result(columns, rows);
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
     * @brief Оператор () для доступа к элементу матрицы по индексам.
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

    /**
     * @brief Конструктор перемещения матрицы.
     * @param other R-value ссылка на другой объект класса Matrix.
     */
    Matrix(Matrix &&other) noexcept : data(std::move(other.data)), eps(std::move(other.eps)) {}

    /**
     * @brief Конструктор копирования матрицы.
     * @param other Константная ссылка на другой объект класса Matrix.
     */
    Matrix(const Matrix &other) : data(other.data), eps(other.eps) {}

    /**
     * @brief Оператор присваивания.
     * @param other Константная ссылка на другой объект класса Matrix.
     * @return Ссылка на текущий объект после присваивания.
     */
    Matrix &operator=(const Matrix &other)
    {
        if (this == &other)
            return *this;

        data = other.data;
        eps = other.eps;
        return *this;
    }

    /**
     * @brief Оператор перемещения.
     * @param other R-value ссылка на другой объект класса Matrix.
     * @return Ссылка на текущий объект после перемещения.
     */
    Matrix &operator=(Matrix &&other) noexcept
    {
        if (this == &other)
            return *this;

        data = std::move(other.data);
        eps = std::move(other.eps);
        return *this;
    }

    auto &operator[](std::pair<int, int> coords)
    {
        return this->data[coords];
    }

    Matrix_proxy<T> operator[](Matrix_coords &&coords)
    {
        proxies.push_back(Matrix_proxy<T>(this, rows, columns, -1, -1, coords));
        return proxies.back();
    }

    Matrix_proxy<T> operator[](Matrix_column_coord &&c)
    {
        Matrix_coords tmp(-1, -1);
        proxies.push_back(Matrix_proxy<T>(this, rows, columns, -1, c.column, tmp));
        return proxies.back();
    }

    Matrix_proxy<T> operator[](Matrix_row_coord &&r)
    {
        Matrix_coords tmp(-1, -1);
        proxies.push_back(Matrix_proxy<T>(this, rows, columns, r.row, -1, tmp));
        return proxies.back();
    }

    Vector<T> operator*(const Vector<T> &other)
    {
        if (other.getLen() != columns)
            throw std::logic_error("Matrix and vector sizes must be (n x m) * (m x 1)");
        Vector<T> result(rows);
        for (int i = 1; i < rows + 1; ++i)
        {
            T sum = T();
            for (int j = 1; j < rows + 1; ++j)
            {
                sum += at(i, j) * other.at(j);
            }
            result.set(i, sum);
        }
        return result;
    }
};
