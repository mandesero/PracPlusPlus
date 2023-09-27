#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <type_traits>

/**
 * @brief Проверка происходит ли переполнения типа, задаваемого в шаблоне
 *
 * @tparam проверяемый тип
 * @param[in] s указатель на c-строку
 * @return true если произошло переполнение
 * @return false если переполнения не произошло
 */
template <typename T>
bool checkOverFlow(const char *s);

/**
 * @brief Проверка происходит ли переполнения типа, задаваемого в шаблоне
 *
 * @tparam проверяемый тип
 * @param[in] s число
 * @return true если произошло переполнение
 * @return false если переполнения не произошло
 */
template <typename T>
bool checkOverFlow(int64_t s);

/**
 * @brief Get the Min Max object
 *
 * @tparam T
 * @return std::pair<T, T>
 */
template <typename T>
std::pair<const char *, const char *> getMinMax();

template <typename T>
std::pair<const char *, const char *> getMinMax()
{
    if (sizeof(T) == 1)
        return std::make_pair(
            "-128",
            "127");
    if (sizeof(T) == 2)
        return std::make_pair(
            "-32768",
            "32767");
    if (sizeof(T) == 4)
        return std::make_pair(
            "-2147483648",
            "2147483647");
    if (sizeof(T) == 8)
        return std::make_pair(
            "-9223372036854775808",
            "9223372036854775807");

    return std::make_pair(
        "",
        "");
}

template <typename T>
bool checkOverFlow(const char *s)
{
    std::pair<const char *, const char *> minMaxT = getMinMax<T>();
    if (s[0] == '-')
    {
        if (std::strlen(s) < std::strlen(minMaxT.first))
            return false;
        if (std::strlen(s) > std::strlen(minMaxT.first))
            return true;

        return std::strcmp(s, minMaxT.first) > 0;
    }
    else
    {
        if (std::strlen(s) < std::strlen(minMaxT.second))
            return false;
        if (std::strlen(s) > std::strlen(minMaxT.second))
            return true;

        return std::strcmp(s, minMaxT.second) > 0;
    }
}

template <typename T>
bool checkOverFlow(int64_t s)
{
    return checkOverFlow<T>(std::to_string(s).c_str());
}