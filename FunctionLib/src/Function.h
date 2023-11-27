#pragma once

#include <vector>
#include <string>
#include <map>
#include <math.h>
#include <iostream>
#include <memory>
#include <stdexcept>

#define EPS 1e-5

class BaseFunction;
using BaseFunctionPtr = std::shared_ptr<BaseFunction>;

class BaseFunction
{
public:
    BaseFunction(){};
    ~BaseFunction() = default;

    virtual std::string ToString() const = 0;
    virtual double operator()(double value) const = 0;
    virtual double GetDeriv(double value) const = 0;
    virtual BaseFunctionPtr copy() const = 0;
};

class Compose : public BaseFunction
{
protected:
    BaseFunctionPtr left;
    BaseFunctionPtr right;
    std::string operation;

public:
    Compose(const BaseFunction &left_op, const BaseFunction &right_op, const std::string &oper);

    double operator()(double value) const override;
    double GetDeriv(double value) const override;
    std::string ToString() const override
    {
        return this->left->ToString() + " " + this->operation + " " + this->right->ToString();
    }
    BaseFunctionPtr copy() const override
    {
        return std::make_shared<Compose>(*this);
    }
};

template <typename TFunction>
Compose operator+(const BaseFunction &left, const TFunction &right)
{
    if constexpr (std::is_base_of_v<BaseFunction, TFunction>)
        return Compose(left, right, "+");
    else
        throw std::logic_error("Wrong type\n");
}

template <typename TFunction>
Compose operator-(const BaseFunction &left, const TFunction &right)
{
    if constexpr (std::is_base_of_v<BaseFunction, TFunction>)
        return Compose(left, right, "-");
    else
        throw std::logic_error("Wrong type\n");
}

template <typename TFunction>
Compose operator*(const BaseFunction &left, const TFunction &right)
{
    if constexpr (std::is_base_of_v<BaseFunction, TFunction>)
        return Compose(left, right, "*");
    else
        throw std::logic_error("Wrong type\n");
}

template <typename TFunction>
Compose operator/(const BaseFunction &left, const TFunction &right)
{
    if constexpr (std::is_base_of_v<BaseFunction, TFunction>)
        return Compose(left, right, "/");
    else
        throw std::logic_error("Wrong type\n");
}

/* ========================================================================================== */

class Exponent : public BaseFunction
{
protected:
    double power;

public:
    Exponent() : power(0.0){};
    explicit Exponent(double pow) : power(pow){};
    explicit Exponent(const std::vector<double> &pows)
    {
        if (!pows.empty())
            power = pows[0];
        else
            power = 0;
    };

    std::string ToString() const override
    {
        if (abs(this->power) < EPS)
            return std::to_string((double)1);
        else
            return "exp(" + std::to_string(this->power) + "x)";
    }
    double operator()(double value) const override
    {
        return exp(this->power * value);
    }
    double GetDeriv(double value) const override
    {
        return this->power * exp(this->power * value);
    }
    BaseFunctionPtr copy() const override
    {
        return std::make_shared<Exponent>(*this);
    }
};

class Polynom : public BaseFunction
{
public:
    explicit Polynom(double coef = 0)
    {
        this->coefs[0] = coef;
    }

    explicit Polynom(const std::vector<double> &cfs);

    std::string ToString() const override;
    double operator()(double value) const override;
    double GetDeriv(double value) const override;
    BaseFunctionPtr copy() const override
    {
        return std::make_shared<Polynom>(*this);
    }

protected:
    std::map<int, double> coefs;
};

class Identical : public Polynom
{
public:
    explicit Identical(double cf = 0) { this->coefs[1] = cf; };
    explicit Identical(const std::vector<double> &cfs)
    {
        if (!cfs.empty())
            this->coefs[1] = cfs[0];
        else
            this->coefs[1] = 0;
    };
};

class Constant : public Polynom
{
public:
    explicit Constant(double coef = 0) : Polynom(coef){};
    explicit Constant(const std::vector<double> &cfs)
    {
        if (!cfs.empty())
            this->coefs[0] = cfs[0];
        else
            this->coefs[0] = 0;
    };
};

class Power : public Polynom
{
public:
    Power() { this->coefs[0] = 1; };
    explicit Power(double pow) { this->coefs[pow] = 1; };
    explicit Power(const std::vector<double> pows)
    {
        if (!pows.empty())
            this->coefs[pows[0]] = 1;
        else
            this->coefs[0] = 1;
    };
};

/* ========================================================================================== */

double GetRoot(BaseFunctionPtr f, uint64_t iters, double start = 0, double eps = EPS);

Compose::Compose(const BaseFunction &left_op, const BaseFunction &right_op, const std::string &oper)
{
    if (oper == "+" || oper == "-" || oper == "*" || oper == "/")
    {
        this->left = left_op.copy();
        this->right = right_op.copy();
        this->operation = oper;
        return;
    }
    throw std::logic_error("Unknown operation\n");
}

double Compose::operator()(double value) const
{
    auto u = left->operator()(value);
    auto v = right->operator()(value);

    if (operation == "+" || operation == "-")
        return operation == "+" ? u + v : u - v;
    return operation == "*" ? u * v : u / v;
}

double Compose::GetDeriv(double value) const
{
    auto u = left->operator()(value);
    auto left_deriv = left->GetDeriv(value);
    auto v = right->operator()(value);
    auto right_deriv = right->GetDeriv(value);

    if (operation == "+" || operation == "-")
        return operation == "+" ? (left_deriv + right_deriv) : (left_deriv - right_deriv);
    return operation == "*" ? (left_deriv * v + right_deriv * u) : (left_deriv * v - right_deriv * u) / (pow(v, 2));
}

std::string Polynom::ToString() const
{
    if (coefs.size() == 1 && coefs.count(0) > 0)
    {
        return std::to_string(coefs.at(0));
    }
    bool isFirst = true;
    std::string res = "";
    for (auto &elem : coefs)
    {
        bool isNull = std::abs(elem.second) < EPS;
        if (isNull)
        {
            continue;
        }
        if (isFirst && !isNull)
        {
            res += std::to_string(elem.second);
            if (elem.first != 0 && elem.first != 1)
                res += "x^" + std::to_string(elem.first);
            else if (elem.first == 1)
                res += "x";
            isFirst = false;
            continue;
        }
        if (elem.second > 0.0)
        {
            res += " + ";
        }
        else
        {
            res += " - ";
        }
        if (elem.first != 1)
            res += std::to_string(std::abs(elem.second)) + "x^" + std::to_string(elem.first);
        else
            res += std::to_string(std::abs(elem.second)) + "x";
    }
    if (res.empty())
    {
        res = std::to_string((double)0);
    }
    return res;
}

double Polynom::operator()(double value) const
{
    double result = 0.0;
    for (const auto &[power, coef] : this->coefs)
    {
        result += coef * pow(value, power);
    }
    return result;
}

double Polynom::GetDeriv(double value) const
{
    double result = 0.0;
    for (auto it = std::next(coefs.begin()); it != coefs.end(); ++it)
    {
        result += it->second * it->first * pow(value, it->first - 1);
    }
    return result;
}

Polynom::Polynom(const std::vector<double> &cfs)
{
    coefs[0] = cfs.empty() ? 0 : cfs[0];

    for (size_t i = 1; i < cfs.size(); ++i)
        if (cfs[i] != 0)
            coefs[i] = cfs[i];
}

class GradientDescent
{
public:
    static double FindRoot(const BaseFunctionPtr f, double initialGuess, double learningRate, int maxIterations)
    {
        double cur_x = initialGuess;
        for (int i = 0; i < maxIterations; ++i)
        {
            double gradient = f->GetDeriv(cur_x);
            cur_x -= learningRate * f->operator()(cur_x) / gradient;
            if (std::abs(f->operator()(cur_x)) < EPS)
                return cur_x;
        }
        return cur_x;
    }
};