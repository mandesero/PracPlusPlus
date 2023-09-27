#include <iostream>
#include "stdint.h"
#include "Rational.h"
#include "Complex.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <type_traits>
#include <cmath>
#include "Exceptions.h"

#include <map>
#include <unordered_map>

#include "Other.h"

struct PairHash {
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U>& p) const {
        std::size_t h1 = std::hash<T>{}(p.first);
        std::size_t h2 = std::hash<U>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};


template <template <class, class...> class Container, class T>
class Matrix
{
protected:
    Container<std::pair<uint64_t, uint64_t>, T> data;
    double eps;
    // std::vector<Matrix_proxy<T>> proxies;
    int rows;
    int columns;

public:
    Matrix() : rows(0), columns(0), eps(0) {}
    Matrix(int rows, int columns, double epsilon = 0) : eps(epsilon), rows(rows), columns(columns) {}

    static Matrix<Container, T> eye(int size_1, int size_2)
    {
        Matrix<Container, T> result(size_1, size_2);
        int size = std::min(size_1, size_2);
        for (int i = 1; i < size + 1; ++i)
        {
            result.set(i, i, T(1));
        }
        return result;
    }

    void set(uint64_t row, uint64_t column, const T &value)
    {
        if (value.abs() >= eps)
            data[std::make_pair(row, column)] = value;
    }

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
};

template <typename T>
class Matrix<std::unordered_map, T>
{
protected:
    using MyHash = PairHash;
    double eps;
    // std::vector<Matrix_proxy<T>> proxies;
    int rows;
    int columns;

    std::unordered_map<std::pair<uint64_t, uint64_t>, T, MyHash> data;
public:
        Matrix() : rows(0), columns(0), eps(0) {}
    Matrix(int rows, int columns, double epsilon = 0) : eps(epsilon), rows(rows), columns(columns) {}

    static Matrix<std::unordered_map, T> eye(int size_1, int size_2)
    {
        Matrix<std::unordered_map, T> result(size_1, size_2);
        int size = std::min(size_1, size_2);
        for (int i = 1; i < size + 1; ++i)
        {
            result.set(i, i, T(1));
        }
        return result;
    }

    void set(uint64_t row, uint64_t column, const T &value)
    {
        if (value.abs() >= eps)
            data[std::make_pair(row, column)] = value;
    }

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
};
int main()
{
    auto m = Matrix<std::unordered_map, Rational_number<int64_t>>::eye(3, 4);
    std::cout << m.to_string() << std::endl;
}