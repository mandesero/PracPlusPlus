#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>
#include <stdexcept>

template <typename T>
class RationalOverflowError : public std::exception
{
public:
    RationalOverflowError(const std::string &message, const char *file, int line, const char *object, T value)
        : m_message(message), m_file(file), m_line(line), m_object(object), m_value_1(value) {}

    RationalOverflowError(const std::string &message, const char *file, int line, const char *object, T value_1, T value_2)
        : m_message(message), m_file(file), m_line(line), m_object(object), m_value_1(value_1), m_value_2(value_2) {}

    const char *
    what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override
    {
        std::ostringstream oss;
        oss << "Overflow error occurred in " << m_file << " at line " << m_line << ": " << m_message << '\n'
            << "Error occurred from: " << m_object << '\n';
        if (m_value_1 != 0)
            oss << "numerator: " << m_value_1 << '\n';
        if (m_value_2 != 0)
            oss << "denominator: " << m_value_2 << '\n';
        errorMessage = oss.str();
        return errorMessage.c_str();
    }

private:
    std::string m_message;
    const char *m_file;
    int m_line;
    const char *m_object;
    T m_value_1 = 0;
    T m_value_2 = 0;
    mutable std::string errorMessage;
};

template <typename T>
class RationalZeroDivisionError : public std::exception
{
public:
    RationalZeroDivisionError(const std::string &message, const char *file, int line, const char *object, std::string val_1, std::string val_2 = "")
        : m_message(message), m_file(file), m_line(line), m_object(object), val_1(val_1), val_2(val_2) {}

    RationalZeroDivisionError(const std::string &message, const char *file, int line, const char *object, T value)
        : m_message(message), m_file(file), m_line(line), m_object(object), m_value(value) {}

    const char *
    what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override
    {
        std::ostringstream oss;
        oss << "Zero division error occurred in " << m_file << " at line " << m_line << ": " << m_message << '\n'
            << "Error occurred from: " << m_object << '\n';
        if (m_value != 0)
            oss << "numerator: " << m_value << '\n'
                << "denumerator: 0\n";
        else
            oss << "value 1: " << val_1 << '\n'
                << "value 2: " << val_2 << '\n';

        errorMessage = oss.str();
        return errorMessage.c_str();
    }

private:
    std::string m_message;
    const char *m_file;
    int m_line;
    const char *m_object;
    T m_value = 0;
    mutable std::string errorMessage;

    std::string val_1;
    std::string val_2;
};

class MatrixShapeError : public std::exception
{
public:
    MatrixShapeError(
        const std::string &message,
        const char *file,
        int line,
        const char *object,
        std::pair<int64_t, int64_t> shape_1,
        std::pair<int64_t, int64_t> shape_2) : m_message(message), m_file(file), m_line(line), m_object(object), shape_1(shape_1), shape_2(shape_2) {}

    const char *
    what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override
    {
        std::ostringstream oss;
        oss << "Shape error" << m_file << " at line " << m_line << ": " << m_message << '\n'
            << "Cannot work with matrix of different size, error ocured from: " << m_object << '\n'
            << "First matrix size: " << shape_1.first << " x " << shape_1.second << '\n'
            << "Second matrix size: " << shape_2.first << " x " << shape_2.second << '\n';

        errorMessage = oss.str();
        return errorMessage.c_str();
    }

private:
    std::string m_message;
    const char *m_file;
    int m_line;
    const char *m_object;
    mutable std::string errorMessage;

    std::pair<int64_t, int64_t> shape_1;
    std::pair<int64_t, int64_t> shape_2;
};

class MatrixIndexError : public std::exception
{
public:
    MatrixIndexError(
        const std::string &message,
        const char *file,
        int line,
        const char *object,
        std::pair<int64_t, int64_t> shape,
        std::pair<int64_t, int64_t> coords) : m_message(message), m_file(file), m_line(line), m_object(object), shape(shape), coords(coords) {}

    const char *
    what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override
    {
        std::ostringstream oss;
        oss << "Index error" << m_file << " at line " << m_line << ": " << m_message << '\n'
            << "In " << m_object << '\n'
            << "Row index must be: 1 to " << shape.first << "\n"
            << "Column index must be: 1 to " << shape.second << "\n"
            << "But given: Row = " << coords.first << ", "
            << "Column = " << coords.second << '\n';

        errorMessage = oss.str();
        return errorMessage.c_str();
    }

private:
    std::string m_message;
    const char *m_file;
    int m_line;
    const char *m_object;
    mutable std::string errorMessage;

    std::pair<int64_t, int64_t> shape;
    std::pair<int64_t, int64_t> coords;
};

class ProxyIndexError : public std::exception
{
public:
    ProxyIndexError(
        const std::string &message,
        const char *file,
        int line,
        const char *object,
        uint64_t size,
        uint64_t idx) : m_message(message), m_file(file), m_line(line), m_object(object), size(size), idx(idx) {}

    const char *
    what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override
    {
        std::ostringstream oss;
        oss << "Index error" << m_file << " at line " << m_line << ": " << m_message << '\n'
            << "In " << m_object << '\n'
            << "Index must be: 1 to " << size << "\n"
            << "But given: ind = " << idx << '\n';

        errorMessage = oss.str();
        return errorMessage.c_str();
    }

private:
    std::string m_message;
    const char *m_file;
    int m_line;
    const char *m_object;
    mutable std::string errorMessage;

    uint64_t size;
    uint64_t idx;
};

class ProxyPointerError : public std::exception
{
public:
    ProxyPointerError(
        const std::string &message,
        const char *file,
        int line) : m_message(message), m_file(file), m_line(line) {}

    const char *
    what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override
    {
        std::ostringstream oss;
        oss << "Pointer error" << m_file << " at line " << m_line << ": " << m_message << '\n';

        errorMessage = oss.str();
        return errorMessage.c_str();
    }

private:
    std::string m_message;
    const char *m_file;
    int m_line;
    mutable std::string errorMessage;
};

class MatrixSliceError : public std::exception
{
public:
    MatrixSliceError(
        const std::string &message,
        const char *file,
        int line) : m_message(message), m_file(file), m_line(line) {}

    const char *
    what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override
    {
        std::ostringstream oss;
        oss << "Slice error " << m_file << " at line " << m_line << ": " << m_message << '\n';

        errorMessage = oss.str();
        return errorMessage.c_str();
    }

private:
    std::string m_message;
    const char *m_file;
    int m_line;
    mutable std::string errorMessage;
};