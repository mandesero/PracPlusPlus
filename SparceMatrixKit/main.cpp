#include <iostream>
#include "stdint.h"
#include "Rational.h"
#include "Complex.h"
#include "Vector.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <sstream>

void readFromStream(const std::string &filename);
Vector<Rational_number<int64_t>> getRationalVectorFromStream(std::ifstream &file);
Vector<Complex_number<double>> getComplexVectorFromStream(std::ifstream &file);
Matrix<Rational_number<int64_t>> getRationalMatrixFromStream(std::ifstream &file);
Matrix<Complex_number<double>> getComplexMatrixFromStream(std::ifstream &file);

struct StreamNumber
{
    std::string objType;
    std::string numberType;
    std::string _T1;
    std::string _T2;
    int size_1;
    int size_2;
    std::ifstream &file;
};

StreamNumber readFromFile(std::ifstream &file)
{
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file.");
    }

    std::string type;
    std::string paramType;
    int size_1 = -1;
    int size_2 = -1;
    std::string _T1;
    std::string _T2;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line.find("#") == 0)
        {
            continue;
        }

        std::istringstream iss(line);
        iss >> type;
        if (type == "vector")
        {
            iss >> paramType;
            if (paramType != "complex" && paramType != "rational")
                throw std::logic_error("Bad type");

            if (paramType == "complex")
            {
                iss >> _T1 >> _T2;
                if ((_T1 != "integer" && _T1 != "float") || (_T2 != "integer" && _T2 != "float"))
                    throw std::logic_error("Bad type");
            }
            iss >> size_1;
            break;
        }
        else if (type == "matrix")
        {
            iss >> paramType;
            if (paramType != "complex" && paramType != "rational")
                throw std::logic_error("Bad type");

            if (paramType == "complex")
            {
                iss >> _T1 >> _T2;
                if ((_T1 != "integer" && _T1 != "float") || (_T2 != "integer" && _T2 != "float"))
                    throw std::logic_error("Bad type");
            }
            iss >> size_1 >> size_2;
            break;
        }
    }
    return StreamNumber{type, paramType, _T1, _T2, size_1, size_2, file};
}

// Rational Vector
Vector<Rational_number<int64_t>> getRV(StreamNumber &meta, std::ifstream &file)
{
    Vector<Rational_number<int64_t>> result(meta.size_1);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        int idx;
        std::string valueString;

        iss >> idx;
        auto left = line.find('<');
        auto right = line.find('>');

        valueString = line.substr(left + 1, right - left - 1);
        Rational_number<int64_t> tmp(valueString.c_str());
        result.set(idx, tmp);
    }
    file.close();
    return result;
}

// Complex Vector
Vector<Complex_number<double, double>> getCV_ff(StreamNumber &meta, std::ifstream &file)
{
    Vector<Complex_number<double, double>> result(meta.size_1);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        int idx;
        std::string valueString;

        iss >> idx;
        auto left = line.find('(');
        auto right = line.find(')');

        valueString = line.substr(left + 1, right - left - 1);
        Complex_number<double, double> tmp(valueString.c_str());
        result.set(idx, tmp);
    }
    file.close();
    return result;
}

Vector<Complex_number<double, int64_t>> getCV_fi(StreamNumber &meta, std::ifstream &file)
{
    Vector<Complex_number<double, int64_t>> result(meta.size_1);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        int idx;
        std::string valueString;

        iss >> idx;
        auto left = line.find('(');
        auto right = line.find(')');

        valueString = line.substr(left + 1, right - left - 1);
        Complex_number<double, int64_t> tmp(valueString.c_str());
        result.set(idx, tmp);
    }
    file.close();
    return result;
}

Vector<Complex_number<int64_t, double>> getCV_if(StreamNumber &meta, std::ifstream &file)
{
    Vector<Complex_number<int64_t, double>> result(meta.size_1);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        int idx;
        std::string valueString;

        iss >> idx;
        auto left = line.find('(');
        auto right = line.find(')');

        valueString = line.substr(left + 1, right - left - 1);
        Complex_number<int64_t, double> tmp(valueString.c_str());
        result.set(idx, tmp);
    }
    file.close();
    return result;
}

Vector<Complex_number<int64_t, int64_t>> getCV_ii(StreamNumber &meta, std::ifstream &file)
{
    Vector<Complex_number<int64_t, int64_t>> result(meta.size_1);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        int idx;
        std::string valueString;

        iss >> idx;
        auto left = line.find('(');
        auto right = line.find(')');

        valueString = line.substr(left + 1, right - left - 1);
        Complex_number<int64_t, int64_t> tmp(valueString.c_str());
        result.set(idx, tmp);
    }
    file.close();
    return result;
}

// Rational matrix

Matrix<Rational_number<int64_t>> getRM(StreamNumber &meta, std::ifstream &file)
{
    Matrix<Rational_number<int64_t>> result(meta.size_1, meta.size_2);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        int idx_1;
        int idx_2;
        std::string valueString;

        iss >> idx_1 >> idx_2;
        auto left = line.find('<');
        auto right = line.find('>');

        valueString = line.substr(left + 1, right - left - 1);
        Rational_number<int64_t> tmp(valueString.c_str());
        result.set(idx_1, idx_2, tmp);
    }
    file.close();
    return result;
}

// Complex matrix
Matrix<Complex_number<double, double>> getCM_ff(StreamNumber &meta, std::ifstream &file)
{
    Matrix<Complex_number<double, double>> result(meta.size_1, meta.size_2);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        int idx_1;
        int idx_2;
        std::string valueString;

        iss >> idx_1 >> idx_2;
        auto left = line.find('(');
        auto right = line.find(')');

        valueString = line.substr(left + 1, right - left - 1);
        Complex_number<double, double> tmp(valueString.c_str());
        result.set(idx_1, idx_2, tmp);
    }
    file.close();
    return result;
}

Matrix<Complex_number<double, int64_t>> getCM_fi(StreamNumber &meta, std::ifstream &file)
{
    Matrix<Complex_number<double, int64_t>> result(meta.size_1, meta.size_2);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        int idx_1;
        int idx_2;
        std::string valueString;

        iss >> idx_1 >> idx_2;
        auto left = line.find('(');
        auto right = line.find(')');

        valueString = line.substr(left + 1, right - left - 1);
        Complex_number<double, int64_t> tmp(valueString.c_str());
        result.set(idx_1, idx_2, tmp);
    }
    file.close();
    return result;
}

Matrix<Complex_number<int64_t, double>> getCM_if(StreamNumber &meta, std::ifstream &file)
{
    Matrix<Complex_number<int64_t, double>> result(meta.size_1, meta.size_2);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        int idx_1;
        int idx_2;
        std::string valueString;

        iss >> idx_1 >> idx_2;
        auto left = line.find('(');
        auto right = line.find(')');

        valueString = line.substr(left + 1, right - left - 1);
        Complex_number<int64_t, double> tmp(valueString.c_str());
        result.set(idx_1, idx_2, tmp);
    }
    file.close();
    return result;
}

Matrix<Complex_number<int64_t, int64_t>> getCM_ii(StreamNumber &meta, std::ifstream &file)
{
    Matrix<Complex_number<int64_t, int64_t>> result(meta.size_1, meta.size_2);
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        int idx_1;
        int idx_2;
        std::string valueString;

        iss >> idx_1 >> idx_2;
        auto left = line.find('(');
        auto right = line.find(')');

        valueString = line.substr(left + 1, right - left - 1);
        Complex_number<int64_t, int64_t> tmp(valueString.c_str());
        result.set(idx_1, idx_2, tmp);
    }
    file.close();
    return result;
}

int main()
{
    std::string filename = "in.txt";
    std::ifstream file(filename);
    StreamNumber meta = readFromFile(file);
    if (meta.objType == "vector")
    {
        if (meta.numberType == "rational")
        {
            auto v = getRV(meta, file);
            std::cout << v.to_string() << std::endl;
        }
        else if (meta.numberType == "complex")
        {
            if (meta._T1 == "integer" && meta._T2 == "integer")
            {
                auto v = getCV_ii(meta, file);
                std::cout << v.to_string() << std::endl;
            }
            if (meta._T1 == "integer" && meta._T2 == "float")
            {
                auto v = getCV_if(meta, file);
                std::cout << v.to_string() << std::endl;
            }
            if (meta._T1 == "float" && meta._T2 == "integer")
            {
                auto v = getCV_fi(meta, file);
                std::cout << v.to_string() << std::endl;
            }
            if (meta._T1 == "float" && meta._T2 == "float")
            {
                auto v = getCV_ff(meta, file);
                std::cout << v.to_string() << std::endl;
            }
        }
    }
    else if (meta.objType == "matrix")
    {
        if (meta.numberType == "rational")
        {
            auto m = getRM(meta, file);
            Vector<Rational_number<int64_t>> v(5);
            Rational_number<int64_t> a(1);
            Rational_number<int64_t> b(-1);
            v[1] = a;
            v[2] = a;
            v[3] = b;
            v[4] = b;
            std::cout << m.to_string() << std::endl;
            std::cout << v.to_string() << std::endl;
            std::cout << (v * m).to_string() << std::endl;
        }
        else if (meta.numberType == "complex")
        {
            if (meta._T1 == "integer" && meta._T2 == "integer")
            {
                auto m = getCM_ii(meta, file);
                std::cout << m.to_string() << std::endl;
            }
            if (meta._T1 == "integer" && meta._T2 == "float")
            {
                auto m = getCM_if(meta, file);
                std::cout << m.to_string() << std::endl;
            }
            if (meta._T1 == "float" && meta._T2 == "integer")
            {
                auto m = getCM_fi(meta, file);
                std::cout << m.to_string() << std::endl;
            }
            if (meta._T1 == "float" && meta._T2 == "float")
            {
                auto m = getCM_ff(meta, file);
                std::cout << m.to_string() << std::endl;
            }
        }
    }

    return 0;
}
