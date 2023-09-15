#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>

template <int size_1, int size_2, typename T>
class Matrix
{
protected:
    double eps;
    std::map<std::pair<int, int>, T> data;
    int rows = size_1;
    int colomns = size_2;

public:
    Matrix(double eps = 0) : eps(eps), data() {}

    void setValue(std::pair<int, int> coords, T &val)
    {
        if (val.abs() < this->eps)
            return;
        data[coords] = val;
    }

    std::string to_string() const
    {
        std::string result;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < colomns; j++)
            {
                std::pair<int, int> key = std::make_pair(i + 1, j + 1);
                if (data.count(key) > 0)
                {
                    result += data.at(key).to_string();
                }
                else
                {
                    result += "0";
                }
                if (j < colomns - 1)
                {
                    result += " ";
                }
            }
            result += "\n";
        }
        return result;
    }

    T getValue(std::pair<int, int> coords) {
        return data[coords];
    }

    template <int s_1, int s_2, typename U>
    Matrix<size_1, size_2, T> operator+(const Matrix<s_1, s_2, U> &other)
    {
        if (size_1 != s_1 || size_2 != s_2)
            throw std::logic_error("cant sum matrix with diffsize");

        Matrix<size_1, size_2, T> result(this->eps);

        for (int i = 0; i < size_1; i++)
        {
            for (int j = 0; j < size_2; j++)
            {
                std::pair<int, int> key = std::make_pair(i + 1, j + 1);

                T value1 = data.count(key) > 0 ? data.at(key) : T();
                T value2 = static_cast<T>(other.getValue(key));

                T tmp = value1 + value2;
                result.setValue(key, tmp);
            }
        }

        return result;
    }
};

template <int size_1, int size_2>
class Matrix<size_1, size_2, bool>
{
protected:
public:
};