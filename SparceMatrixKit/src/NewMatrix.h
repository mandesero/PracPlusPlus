#include <iostream>
#include "stdint.h"
#include "Rational.h"
#include "Complex.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <type_traits>
#include <cmath>
#include <map>
#include <unordered_map>
#include "Exceptions.h"
#include "Vector.h"

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

/**
 * @brief Структрура среза для матрицы
 *
 */
struct Matrix_coords
{
    uint64_t r1 = 0; /**< Левая граница среза (строка). Если -1, то с начала матрицы. */
    uint64_t c1 = 0; /**< Левая граница среза (столбец). Если -1, то с начала матрицы. */
    uint64_t r2 = 0; /**< Правая граница среза (строка). Если -1, то до конца матрицы. */
    uint64_t c2 = 0; /**< Правая граница среза (столбец). Если -1, то до конца матрицы. */

    /**
     * @brief Конструктор по умолчанию
     *
     */
    Matrix_coords() {}

    /**
     * @brief Конструктор
     *
     * @param[in] r1 Левая граница среза (строка).
     * @param[in] c1 Левая граница среза (столбец).
     * @param[in] r2 Правая граница среза (строка).
     * @param[in] c2 Правая граница среза (столбец).
     */
    explicit Matrix_coords(uint64_t r1, uint64_t c1, uint64_t r2, uint64_t c2) : r1(r1), c1(c1), r2(r2), c2(c2) {}

    /**
     * @brief Конструктор
     *
     * @param[in] r1 Левая граница среза (строка).
     * @param[in] c1 Левая граница среза (столбец).
     */
    explicit Matrix_coords(uint64_t r1, uint64_t c1) : r1(r1), c1(c1), r2(r1), c2(c1) {}
};

/**
 * @brief Структура для proxy строки.
 *
 */
struct Matrix_row_coord
{
    uint64_t row; /**< Индекс строки */

    /**
     * @brief Конструктор
     *
     * @param[in] row номер строки
     */
    explicit Matrix_row_coord(uint64_t row) : row(row) {}
};

/**
 * @brief Структура для proxy столбца.
 *
 */
struct Matrix_column_coord
{
    uint64_t column; /**< Индекс столбца */

    /**
     * @brief Конструктор
     *
     * @param[in] column номер столбца
     */
    explicit Matrix_column_coord(uint64_t column) : column(column) {}
};

template <template <class, class...> class Container, class T>
class Matrix_proxy;

template <template <class, class...> class Container, class T>
class Matrix
{
protected:
    Container<std::pair<uint64_t, uint64_t>, T> data;
    double eps;
    std::pair<uint64_t, uint64_t> size;

    std::vector<Matrix_proxy<Container, T> *> proxies;

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
    Matrix(uint64_t rows, uint64_t columns, double epsilon = 0) : eps(epsilon), size(rows, columns) {}

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
    static Matrix<Container, T> zeros(uint64_t rows, uint64_t columns)
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
    static Matrix<Container, T> ones(uint64_t rows, uint64_t columns)
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
    static Matrix<Container, T> eye(uint64_t rows, uint64_t columns)
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

    /**
     * @brief Получение элемента по заданным координатам
     *
     * @param[in] row номер строки
     * @param[in] column номер столбца
     * @return константная ссылка на элемент по заданным координатам
     */
    const T &at(uint64_t row, uint64_t column) const
    {
        auto it = data.find(std::make_pair(row, column));
        if (it == data.end())
        {
            static const T zero;
            return zero;
        }
        else
            return it->second;
    }

    /**
     * @brief Получение элемента по заданным координатам
     *
     * @param[in] coord координаты элемента
     * @return ссылка на элемент по заданным координатам
     */
    T &operator[](const std::pair<uint64_t, uint64_t> &coord)
    {
        return data[coord];
    }

    /**
     * @brief Оператор () для доступа к элементу матрицы по индексам.
     * @param row Номер строки.
     * @param column Номер столбца.
     * @return Ссылка на элемент матрицы в позиции (row, column).
     * @throws MatrixIndexError Если индексы выходят за пределы размеров матрицы.
     */
    const T &operator()(uint64_t row, uint64_t column) const
    {
        if (row < 1 || row > size.first + 1 || column < 1 || column > size.second + 1)
        {
            throw MatrixIndexError("", __FILE__, __LINE__, "operator ()", size, {row, column});
        }
        return this->at(row, column);
    }

    /*
        =========================== Арифметические операции с матрицами, оператор транспонирования ===========================
    */

    /**
     * @brief Перегрузка оператора сложения для матриц.
     * @param[in] other Матрица.
     * @return Новая матрица, являющаяся результатом сложения.
     */
    Matrix<Container, T> operator+(const Matrix<Container, T> &other)
    {
        if (size.first != other.shape().first || size.second != other.shape().second)
            throw MatrixShapeError("", __FILE__, __LINE__, "operator +", size, other.shape());

        Matrix<Container, T> result(size.first, size.second, eps);

        for (int i = 1; i < size.first + 1; ++i)
        {
            for (int j = 1; j < size.second + 1; ++j)
            {
                T value = at(i, j) + other.at(i, j);
                result.set(i, j, value);
            }
        }
        return result;
    }

    /**
     * @brief Перегрузка оператора сложения для матриц.
     * @param[in] other Матрица.
     * @return Новая матрица, являющаяся результатом сложения.
     */
    Matrix<Container, T> operator-(const Matrix<Container, T> &other)
    {
        if (size.first != other.shape().first || size.second != other.shape().second)
            throw MatrixShapeError("", __FILE__, __LINE__, "operator -", size, other.shape());

        Matrix<Container, T> result(size.first, size.second, eps);

        for (int i = 1; i < size.first + 1; ++i)
        {
            for (int j = 1; j < size.second + 1; ++j)
            {
                T value = at(i, j) - other.at(i, j);
                result.set(i, j, value);
            }
        }
        return result;
    }

    /**
     * @brief Перегрузка оператора умножения для матриц.
     * @param[in] other Матрица.
     * @return Новая матрица, являющаяся результатом умножения.
     */
    Matrix<Container, T> operator*(const Matrix<Container, T> &other)
    {
        if (size.second != other.shape().first)
            throw MatrixShapeError("", __FILE__, __LINE__, "operator *", size, other.shape());

        Matrix<Container, T> result(size.first, size.second, eps);

        for (int i = 1; i < size.first + 1; ++i)
        {
            for (int k = 1; k < other.shape().second + 1; ++k)
            {
                T sum = T();
                for (int j = 1; j < size.second + 1; ++j)
                {
                    sum += at(i, j) * other.at(j, k);
                }
                result.set(i, k, sum);
            }
        }
        return result;
    }

    /**
     * @brief Перегрузка оператора унарного минуса.
     * @return Новая матрица, являющаяся результатом инверсии знака всех элементов текущей матрицы.
     */
    Matrix<Container, T> operator-() const
    {
        Matrix<Container, T> result(*this);
        for (auto &pair : result.data)
        {
            pair.second = -pair.second;
        }
        return result;
    }

    /**
     * @brief Перегрузка оператора транспонирования.
     * @return Транспонированная матрица.
     */
    Matrix<Container, T> operator~() const
    {
        Matrix<Container, T> result(size.second, size.first, eps);

        for (int i = 1; i < size.second + 1; ++i)
        {
            for (int j = 1; j < size.first + 1; ++j)
            {
                result.set(i, j, at(j, i));
            }
        }
        return result;
    }

    /*
        =========================== Умножение на вектор ===========================
    */
    // TODO
    /*
        =========================== Прочее ===========================
    */

    /**
     * @brief Преобразование матрицы к строке
     *
     * @return Матрица приведенная к строке.
     */
    std::string to_string() const
    {
        std::string result;
        for (int i = 1; i < size.first + 1; ++i)
        {
            for (int j = 1; j < size.second + 1; ++j)
                result += at(i, j).to_string() + " ";
            result += "\n";
        }
        return result;
    }

    /**
     * @brief Конструктор перемещения матрицы.
     * @param[in] other R-value ссылка на другой объект класса Matrix.
     */
    Matrix(Matrix &&other) noexcept : data(std::move(other.data)), eps(std::move(other.eps)) {}

    /**
     * @brief Конструктор копирования матрицы.
     * @param[in] other Константная ссылка на другой объект класса Matrix.
     */
    Matrix(const Matrix &other) : data(other.data), eps(other.eps) {}

    /**
     * @brief Оператор присваивания.
     * @param[in] other Константная ссылка на другой объект класса Matrix.
     * @return Ссылка на скопированный объект.
     */
    Matrix &operator=(const Matrix &other)
    {
        if (this == &other)
            return *this;

        data = other.getData();
        eps = other.getEps();
        size = other.shape();
        return *this;
    }

    /**
     * @brief Оператор перемещения.
     * @param[in] other R-value ссылка на другой объект класса Matrix.
     * @return Ссылка на текущий объект после перемещения.
     */
    Matrix &operator=(Matrix &&other) noexcept
    {
        if (this == &other)
            return *this;

        data = std::move(other.getData());
        eps = std::move(other.getEps());
        size = std::move(other.shape());
        return *this;
    }

    /**
     * @brief Деструктор
     *
     */
    ~Matrix()
    {
        for (auto &proxy : proxies)
            proxy->delete_ptr();
    }

    /*
        =========================== Срезы и proxy ===========================
    */

    /**
     * @brief Перегрузка оператора [] для получения среза
     *
     * @param[in] coords срез
     * @return Прокси объект
     */
    Matrix_proxy<Container, T> operator[](const Matrix_coords &coords)
    {
        uint64_t c1 = coords.c1;
        uint64_t c2 = coords.c2;
        uint64_t r1 = coords.r1;
        uint64_t r2 = coords.r2;

        if (c1 == -1 || r1 == -1)
        {
            c1 = 1;
            r1 = 1;
        }
        if (c2 == -1 || r2 == -1)
        {
            c2 = size.second;
            r2 = size.first;
        }
        Matrix_proxy<Container, T> tmp(this, Matrix_coords(r1, c1, r2, c2), Matrix_row_coord(-1), Matrix_column_coord(-1));
        proxies.push_back(&tmp);
        return tmp;
    }

    /**
     * @brief Перегрузка оператора [] для получения proxy строки
     *
     * @param[in] row номер строки
     * @return Прокси объект
     */
    Matrix_proxy<Container, T> operator[](const Matrix_row_coord &row)
    {
        Matrix_proxy<Container, T> tmp(this, Matrix_coords(), row, Matrix_column_coord(-1));
        proxies.push_back(&tmp);
        return tmp;
    }

    /**
     * @brief Перегрузка оператора [] для получения proxy столбца
     *
     * @param[in] column номер столбца
     * @return Прокси объект
     */
    Matrix_proxy<Container, T> operator[](const Matrix_column_coord &column)
    {
        Matrix_proxy<Container, T> tmp(this, Matrix_coords(), Matrix_row_coord(-1), column);
        proxies.push_back(&tmp);
        return tmp;
    }
};

template <template <class, class...> class Container, class T>
class Matrix_proxy
{
protected:
    Matrix<Container, T> *matrix;
    Matrix_coords slice;
    uint64_t idx_row = -1;
    uint64_t idx_column = -1;

public:
    /**
     * @brief Конструктор
     *
     * @param[in] matrix указатель на исходную матрицу
     * @param[in] coords срез
     * @param[in] row номер строки
     * @param[in] column номер столбца
     */
    Matrix_proxy(Matrix<Container, T> *matrix, Matrix_coords coords, Matrix_row_coord row, Matrix_column_coord column)
        : matrix(matrix), slice(coords), idx_row(row.row), idx_column(column.column) {}

    /**
     * @brief Обнуление указателя на исходную матрицу, при удалении объекта матрицы
     *
     */
    void delete_ptr()
    {
        matrix = nullptr;
    }

    /**
     * @brief Оператор [] для обращения к элементу proxy
     *
     * @param index индекс элемента
     * @return auto& элемент по индексу index
     */
    auto &operator[](const int index)
    {
        if (matrix == nullptr)
            throw ProxyPointerError("Basic matrix was deleted.", __FILE__, __LINE__);

        if (idx_row != -1 && !(1 <= idx_row && idx_row <= matrix->shape().first))
            throw ProxyIndexError("", __FILE__, __LINE__, "operator []", matrix->shape().first, index);

        if (idx_column != -1 && !(1 <= idx_column && idx_column <= matrix->shape().second))
            throw ProxyIndexError("", __FILE__, __LINE__, "operator []", matrix->shape().second, index);

        return idx_column == -1 ? matrix->at(idx_row, index) : matrix->at(index, idx_column);
    }

    /**
     * @brief Оператор для доступа к элементу матрицы
     *
     * @param[in] coords координаты
     * @return элемент по заданным координатам
     */
    auto &operator[](const std::pair<uint64_t, uint64_t> &coords)
    {
        if (matrix == nullptr)
            throw ProxyPointerError("Basic matrix was deleted.", __FILE__, __LINE__);
        return matrix->operator[](coords);
    }

    /**
     * @brief Оператор для мульти-slice
     *
     * @param[in] coords новый срез
     * @return обновленный срез
     */
    auto &operator[](const Matrix_coords &coords)
    {
        if (matrix == nullptr)
            throw ProxyPointerError("Basic matrix was deleted.", __FILE__, __LINE__);
        bool firstRectCondition = (slice.r1 >= coords.r1 && slice.c1 >= coords.r1) && (slice.r2 <= coords.r2 && slice.c2 <= coords.c2);
        bool secondRectCondition = (slice.r1 <= coords.r1 && slice.c1 <= coords.r1) && (slice.r2 >= coords.r2 && slice.c2 >= coords.c2);
        if (!firstRectCondition && !secondRectCondition)
            throw MatrixSliceError("", __FILE__, __LINE__);

        if (firstRectCondition)
            slice = coords;

        return *this;
    }

    /**
     * @brief Приведение proxy объекта к строке
     *
     * @return строка
     */
    std::string to_string() const
    {
        if (matrix == nullptr)
            throw ProxyPointerError("Basic matrix was deleted.", __FILE__, __LINE__);

        std::string result;
        if (idx_column != -1)
        {
            for (int i = 1; i <= matrix->shape().first; ++i)
                result += matrix->at(i, idx_column).to_string() + '\n';
        }
        else if (idx_row != -1)
        {
            for (int i = 1; i <= matrix->shape().second; ++i)
                result += matrix->at(idx_row, i).to_string() + ' ';
        }
        else
        {
            for (int j = slice.r1; j <= slice.r2; ++j)
            {
                for (int i = slice.c1; i <= slice.c2; ++i)
                    result += matrix->at(i, j).to_string() + " ";
                result += "\n";
            }
        }
        return result;
    }

    /**
     * @brief Преобразование прокси к вектору
     * 
     * @return вектор 
     */
    auto create_vector()
    {
        if (matrix == nullptr)
            throw ProxyPointerError("Basic matrix was deleted.", __FILE__, __LINE__);

        if (idx_column == -1 && idx_row == -1)
            throw ProxyPointerError("Not a vector.", __FILE__, __LINE__);

        if (idx_column != -1)
        {
            Vector<T> result(matrix->shape().first);
            for (int i = 1; i <= matrix->shape().first; ++i)
                result[i] += matrix->at(i, idx_column);
            return result;
        }
        else
        {
            Vector<T> result(matrix->shape().second);
            for (int i = 1; i <= matrix->shape().second; ++i)
                result[i] = matrix->at(idx_row, i);
            return result;
        }
    }
};


template <typename T>
class Matrix<std::unordered_map, T>
{
protected:
    using MyHash = PairHash;
    double eps;
    std::pair<uint64_t, uint64_t> size;

    std::unordered_map<std::pair<uint64_t, uint64_t>, T, MyHash> data;
    std::vector<Matrix_proxy<std::unordered_map, T> *> proxies;

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
    Matrix(uint64_t rows, uint64_t columns, double epsilon = 0) : eps(epsilon), size(rows, columns) {}

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
    static Matrix<std::unordered_map, T> zeros(uint64_t rows, uint64_t columns)
    {
        Matrix<std::unordered_map, T> result(rows, columns);
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
    static Matrix<std::unordered_map, T> ones(uint64_t rows, uint64_t columns)
    {
        Matrix<std::unordered_map, T> result(rows, columns);
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
    static Matrix<std::unordered_map, T> eye(uint64_t rows, uint64_t columns)
    {
        Matrix<std::unordered_map, T> result(rows, columns);
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
    const std::unordered_map<std::pair<uint64_t, uint64_t>, T> &getData() const
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

    /**
     * @brief Получение элемента по заданным координатам
     *
     * @param[in] row номер строки
     * @param[in] column номер столбца
     * @return константная ссылка на элемент по заданным координатам
     */
    const T &at(uint64_t row, uint64_t column) const
    {
        auto it = data.find(std::make_pair(row, column));
        if (it == data.end())
        {
            static const T zero;
            return zero;
        }
        else
            return it->second;
    }

    /**
     * @brief Получение элемента по заданным координатам
     *
     * @param[in] coord координаты элемента
     * @return ссылка на элемент по заданным координатам
     */
    T &operator[](const std::pair<uint64_t, uint64_t> &coord)
    {
        return data[coord];
    }

    /**
     * @brief Оператор () для доступа к элементу матрицы по индексам.
     * @param row Номер строки.
     * @param column Номер столбца.
     * @return Ссылка на элемент матрицы в позиции (row, column).
     * @throws MatrixIndexError Если индексы выходят за пределы размеров матрицы.
     */
    const T &operator()(uint64_t row, uint64_t column) const
    {
        if (row < 1 || row > size.first + 1 || column < 1 || column > size.second + 1)
        {
            throw MatrixIndexError("", __FILE__, __LINE__, "operator ()", size, {row, column});
        }
        return this->at(row, column);
    }

    /*
        =========================== Арифметические операции с матрицами, оператор транспонирования ===========================
    */

    /**
     * @brief Перегрузка оператора сложения для матриц.
     * @param[in] other Матрица.
     * @return Новая матрица, являющаяся результатом сложения.
     */
    Matrix<std::unordered_map, T> operator+(const Matrix<std::unordered_map, T> &other)
    {
        if (size.first != other.shape().first || size.second != other.shape().second)
            throw MatrixShapeError("", __FILE__, __LINE__, "operator +", size, other.shape());

        Matrix<std::unordered_map, T> result(size.first, size.second, eps);

        for (int i = 1; i < size.first + 1; ++i)
        {
            for (int j = 1; j < size.second + 1; ++j)
            {
                T value = at(i, j) + other.at(i, j);
                result.set(i, j, value);
            }
        }
        return result;
    }

    /**
     * @brief Перегрузка оператора сложения для матриц.
     * @param[in] other Матрица.
     * @return Новая матрица, являющаяся результатом сложения.
     */
    Matrix<std::unordered_map, T> operator-(const Matrix<std::unordered_map, T> &other)
    {
        if (size.first != other.shape().first || size.second != other.shape().second)
            throw MatrixShapeError("", __FILE__, __LINE__, "operator -", size, other.shape());

        Matrix<std::unordered_map, T> result(size.first, size.second, eps);

        for (int i = 1; i < size.first + 1; ++i)
        {
            for (int j = 1; j < size.second + 1; ++j)
            {
                T value = at(i, j) - other.at(i, j);
                result.set(i, j, value);
            }
        }
        return result;
    }

    /**
     * @brief Перегрузка оператора умножения для матриц.
     * @param[in] other Матрица.
     * @return Новая матрица, являющаяся результатом умножения.
     */
    Matrix<std::unordered_map, T> operator*(const Matrix<std::unordered_map, T> &other)
    {
        if (size.second != other.shape().first)
            throw MatrixShapeError("", __FILE__, __LINE__, "operator *", size, other.shape());

        Matrix<std::unordered_map, T> result(size.first, size.second, eps);

        for (int i = 1; i < size.first + 1; ++i)
        {
            for (int k = 1; k < other.shape().second + 1; ++k)
            {
                T sum = T();
                for (int j = 1; j < size.second + 1; ++j)
                {
                    sum += at(i, j) * other.at(j, k);
                }
                result.set(i, k, sum);
            }
        }
        return result;
    }

    /**
     * @brief Перегрузка оператора унарного минуса.
     * @return Новая матрица, являющаяся результатом инверсии знака всех элементов текущей матрицы.
     */
    Matrix<std::unordered_map, T> operator-() const
    {
        Matrix<std::unordered_map, T> result(*this);
        for (auto &pair : result.data)
        {
            pair.second = -pair.second;
        }
        return result;
    }

    /**
     * @brief Перегрузка оператора транспонирования.
     * @return Транспонированная матрица.
     */
    Matrix<std::unordered_map, T> operator~() const
    {
        Matrix<std::unordered_map, T> result(size.second, size.first, eps);

        for (int i = 1; i < size.second + 1; ++i)
        {
            for (int j = 1; j < size.first + 1; ++j)
            {
                result.set(i, j, at(j, i));
            }
        }
        return result;
    }

    /*
        =========================== Умножение на вектор ===========================
    */
    // TODO
    /*
        =========================== Прочее ===========================
    */

    /**
     * @brief Преобразование матрицы к строке
     *
     * @return Матрица приведенная к строке.
     */
    std::string to_string() const
    {
        std::string result;
        for (int i = 1; i < size.first + 1; ++i)
        {
            for (int j = 1; j < size.second + 1; ++j)
                result += at(i, j).to_string() + " ";
            result += "\n";
        }
        return result;
    }

    /**
     * @brief Конструктор перемещения матрицы.
     * @param[in] other R-value ссылка на другой объект класса Matrix.
     */
    Matrix(Matrix &&other) noexcept : data(std::move(other.data)), eps(std::move(other.eps)) {}

    /**
     * @brief Конструктор копирования матрицы.
     * @param[in] other Константная ссылка на другой объект класса Matrix.
     */
    Matrix(const Matrix &other) : data(other.data), eps(other.eps) {}

    /**
     * @brief Оператор присваивания.
     * @param[in] other Константная ссылка на другой объект класса Matrix.
     * @return Ссылка на скопированный объект.
     */
    Matrix &operator=(const Matrix &other)
    {
        if (this == &other)
            return *this;

        data = other.getData();
        eps = other.getEps();
        size = other.shape();
        return *this;
    }

    /**
     * @brief Оператор перемещения.
     * @param[in] other R-value ссылка на другой объект класса Matrix.
     * @return Ссылка на текущий объект после перемещения.
     */
    Matrix &operator=(Matrix &&other) noexcept
    {
        if (this == &other)
            return *this;

        data = std::move(other.getData());
        eps = std::move(other.getEps());
        size = std::move(other.shape());
        return *this;
    }

    /**
     * @brief Деструктор
     *
     */
    ~Matrix()
    {
        for (auto &proxy : proxies)
            proxy->delete_ptr();
    }

    /*
        =========================== Срезы и proxy ===========================
    */

    /**
     * @brief Перегрузка оператора [] для получения среза
     *
     * @param[in] coords срез
     * @return Прокси объект
     */
    Matrix_proxy<std::unordered_map, T> operator[](const Matrix_coords &coords)
    {
        uint64_t c1 = coords.c1;
        uint64_t c2 = coords.c2;
        uint64_t r1 = coords.r1;
        uint64_t r2 = coords.r2;

        if (c1 == -1 || r1 == -1)
        {
            c1 = 1;
            r1 = 1;
        }
        if (c2 == -1 || r2 == -1)
        {
            c2 = size.second;
            r2 = size.first;
        }
        Matrix_proxy<std::unordered_map, T> tmp(this, Matrix_coords(r1, c1, r2, c2), Matrix_row_coord(-1), Matrix_column_coord(-1));
        proxies.push_back(&tmp);
        return tmp;
    }

    /**
     * @brief Перегрузка оператора [] для получения proxy строки
     *
     * @param[in] row номер строки
     * @return Прокси объект
     */
    Matrix_proxy<std::unordered_map, T> operator[](const Matrix_row_coord &row)
    {
        Matrix_proxy<std::unordered_map, T> tmp(this, Matrix_coords(), row, Matrix_column_coord(-1));
        proxies.push_back(&tmp);
        return tmp;
    }

    /**
     * @brief Перегрузка оператора [] для получения proxy столбца
     *
     * @param[in] column номер столбца
     * @return Прокси объект
     */
    Matrix_proxy<std::unordered_map, T> operator[](const Matrix_column_coord &column)
    {
        Matrix_proxy<std::unordered_map, T> tmp(this, Matrix_coords(), Matrix_row_coord(-1), column);
        proxies.push_back(&tmp);
        return tmp;
    }
};