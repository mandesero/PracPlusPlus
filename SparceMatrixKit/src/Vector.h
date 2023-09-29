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

template <template <class, class...> class Container, class T>
class Matrix;

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
     * @brief Перегрузка оператора умножения вектора на матрицу
     *
     * @param[in] other Матрица
     * @return Вектор, являющийся результатом умножения вектора на матрицу
     */
    template <template <class, class...> class Container, class U>
    Vector<T> operator*(const Matrix<Container, U> &other)
    {
        if (len != other.shape().first)
            throw MatrixShapeError("", __FILE__, __LINE__, "operator * vector", std::make_pair(len, 1), other.shape());

        Vector<T> result(other.shape().second);

        for (int j = 1; j < other.shape().second + 1; ++j)
        {
            T sum = T();
            for (int k = 1; k < len + 1; ++k)
            {
                sum += at(k) * other.at(k, j);
            }
            result.set(j, sum);
        }

        return result;
    }

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

    /**
     * @brief Метод для чтения матрицы с файла
     *
     * @param[in] file файловый поток
     * @return Прочитанная матрица
     */
    static Vector<T> readFromFile(std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
            throw VectorReadFromFileError("", __FILE__, __LINE__);

        std::string line, _T1, _T2;
        uint64_t len;
        std::vector<std::string> params;
        while (std::getline(file, line))
        {
            if (line.empty() || startsWithHash(line))
                continue;

            std::istringstream iss(line);
            params = std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

            if (params[0] != "vector")
                throw VectorReadFromFileError("File not contains vector.", __FILE__, __LINE__);

            if (T::type() != params[1])
                throw MatrixReadFromFileError("Incorrect type of input vector.", __FILE__, __LINE__);

            if (params[1] == "rational")
            {
                if (params.size() != 3)
                    throw MatrixReadFromFileError("To many params. Expected 3. But given " + std::to_string(params.size()), __FILE__, __LINE__);

                len = std::stoll(params[2]);
            }
            else if (params[1] == "complex")
            {
                if (params.size() != 5)
                    throw MatrixReadFromFileError("To many params. Expected 5. But given " + std::to_string(params.size()), __FILE__, __LINE__);

                std::map<std::string, std::string> in_types;
                in_types["a"] = "integer";
                in_types["s"] = "integer";
                in_types["i"] = "integer";
                in_types["l"] = "integer";
                in_types["f"] = "float";
                in_types["d"] = "float";

                _T1 = T::getTypeNames().first;
                _T2 = T::getTypeNames().second;

                if (params[2] != in_types[_T1] || params[3] != in_types[_T2])
                    throw MatrixReadFromFileError("Incorrect complex im and real field types. ", __FILE__, __LINE__);

                len = std::stoll(params[4]);
            }
            break;
        }

        auto new_vector = Vector<T>(len);

        uint64_t idx;
        while (std::getline(file, line))
        {
            if (line.empty() || startsWithHash(line))
                continue;

            std::istringstream iss(line);
            iss >> idx;
            if (params[1] == "complex")
            {
                auto left = line.find('(');
                auto right = line.find(')');
                auto valueString = line.substr(left + 1, right - left - 1);
                auto value = T(valueString.c_str());
                new_vector.set(idx, value);
            }
            else if (params[1] == "rational")
            {
                auto left = line.find('<');
                auto right = line.find('>');
                auto valueString = line.substr(left + 1, right - left - 1);
                auto value = T(valueString.c_str());
                new_vector.set(idx, value);
            }
        }
        return new_vector;
    }
};