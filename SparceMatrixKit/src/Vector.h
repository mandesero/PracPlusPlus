#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>
#include <map>

template <typename T>
class Vector {
protected:
    double eps;
    std::map<int, T> v{};

public:
    Vector(double eps): eps(eps) {}

};