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
    RationalZeroDivisionError(const std::string &message, const char *file, int line, const char *object, T value)
        : m_message(message), m_file(file), m_line(line), m_object(object), m_value(value) {}

    const char *
    what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override
    {
        std::ostringstream oss;
        oss << "Zero division error occurred in " << m_file << " at line " << m_line << ": " << m_message << '\n'
            << "Error occurred from: " << m_object << '\n'
            << "numerator: " << m_value << '\n'
            << "denominator: 0";
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
};