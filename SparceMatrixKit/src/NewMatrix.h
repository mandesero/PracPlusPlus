#include <iostream>
#include "stdint.h"
#include "Rational.h"
#include "Complex.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <type_traits>
#include <cmath>
#include <map>
#include <unordered_map>
#include "Exceptions.h"

/**
 * @brief Структура для хэширования std::pair<uint64_t, uint64_t>
 *
 */
struct PairHash
{
    /**
     * @brief Перегрузка оператора () для получения хэша пары
     *
     * @param[in] p пара для хэширования (◕‿◕)♡
     * @return std::size_t
     */
    std::size_t operator()(const std::pair<uint64_t, uint64_t> &p) const
    {
        std::size_t h1 = std::hash<uint64_t>{}(p.first);
        std::size_t h2 = std::hash<uint64_t>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

template <template <class, class...> class Container, class T>
class Matrix
{
protected:
    Container<std::pair<uint64_t, uint64_t>, T> data;
    double eps;
    std::pair<uint64_t, uint64_t> size;

public:
    /*
        =========================== Конструкторы ===========================
    */

    /**
     * @brief Конструктор по умолчанию
     *
     */
    Matrix() : size(0, 0), eps(0) {}

    /**
     * @brief Конструктор
     *
     * @param[in] rows количество строк в матрице
     * @param[in] columns количество столбцов в матрице
     * @param[in] epsilon eps (по умолчанию 0)
     */
    Matrix(int rows, int columns, double epsilon = 0) : eps(epsilon), size(rows, columns) {}

    /*
        =========================== Static конструкторы ===========================
    */

    /**
     * @brief Конструктор, создающий матрицу из нулей
     *
     * @param[in] rows количество строк в матрице
     * @param[in] columns количество столбцов в матрице
     * @return Нулевая матрица размера (rows x columns)
     */
    static Matrix<Container, T> zeros(int rows, int columns)
    {
        Matrix<Container, T> result(rows, columns);
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
     * @brief Конструктор, создающий матрицу из единиц
     *
     * @param[in] rows количество строк в матрице
     * @param[in] columns количество столбцов в матрице
     * @return Матрица размера (rows x columns) состоящая из единиц
     */
    static Matrix<Container, T> ones(int rows, int columns)
    {
        Matrix<Container, T> result(rows, columns);
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
     * @brief Конструктор, создающий единичную матрицу
     *
     * @param[in] rows количество строк в матрице
     * @param[in] columns количество столбцов в матрице
     * @return Единичная матрица размера (rows x columns)
     */
    static Matrix<Container, T> eye(int rows, int columns)
    {
        Matrix<Container, T> result(rows, columns);
        for (int i = 1; i < std::min(rows, columns) + 1; ++i)
        {
            result.set(i, i, T(1));
        }
        return result;
    }

    /*
        =========================== Getter, setter ===========================
    */

    /**
     * @brief Получение размера матрицы
     *
     * @return пара (кол-во строк, кол-во столбцов)
     */
    const std::pair<uint64_t, uint64_t> &shape() const
    {
        return size;
    }

    /**
     * @brief Получение контейнера с хранимыми в матрице значениями
     *
     * @return контейнер
     */
    const Container<std::pair<uint64_t, uint64_t>, T> &getData() const
    {
        return data;
    }

    /**
     * @brief Получение значение eps
     *
     * @return eps
     */
    const double &getEps() const
    {
        return eps;
    }

    /**
     * @brief Метод для установки значения в заданную позицию
     * 
     * @param[in] row количество строк
     * @param[in] column количество столбцов
     * @param[in] value устанавливаемое значение
     */
    void set(uint64_t row, uint64_t column, const T &value)
    {
        if (value.abs() >= eps)
            data[std::make_pair(row, column)] = value;
    }

    // std::string to_string() const
    // {
    //     std::string result;
    //     for (int i = 1; i < rows + 1; ++i)
    //     {
    //         for (int j = 1; j < columns + 1; ++j)
    //             result += at(i, j).to_string() + " ";
    //         result += "\n";
    //     }
    //     return result;
    // }

    // const T &at(int row, int column) const
    // {
    //     auto it = data.find(std::make_pair(row, column));
    //     if (it == data.end())
    //     {
    //         static const T zero;
    //         return zero;
    //     }
    //     else
    //     {
    //         return it->second;
    //     }
    // }
};

// template <typename T>
// class Matrix<std::unordered_map, T>
// {
// protected:
//     using MyHash = PairHash;
//     double eps;
//     int rows;
//     int columns;

//     std::unordered_map<std::pair<uint64_t, uint64_t>, T, MyHash> data;

// public:
//     Matrix() : rows(0), columns(0), eps(0) {}
//     Matrix(int rows, int columns, double epsilon = 0) : eps(epsilon), rows(rows), columns(columns) {}

//     static Matrix<std::unordered_map, T> eye(int size_1, int size_2)
//     {
//         Matrix<std::unordered_map, T> result(size_1, size_2);
//         int size = std::min(size_1, size_2);
//         for (int i = 1; i < size + 1; ++i)
//         {
//             result.set(i, i, T(1));
//         }
//         return result;
//     }

//     void set(uint64_t row, uint64_t column, const T &value)
//     {
//         if (value.abs() >= eps)
//             data[std::make_pair(row, column)] = value;
//     }

//     std::string to_string() const
//     {
//         std::string result;
//         for (int i = 1; i < rows + 1; ++i)
//         {
//             for (int j = 1; j < columns + 1; ++j)
//                 result += at(i, j).to_string() + " ";
//             result += "\n";
//         }
//         return result;
//     }

//     const T &at(int row, int column) const
//     {
//         auto it = data.find(std::make_pair(row, column));
//         if (it == data.end())
//         {
//             static const T zero;
//             return zero;
//         }
//         else
//         {
//             return it->second;
//         }
//     }
// };