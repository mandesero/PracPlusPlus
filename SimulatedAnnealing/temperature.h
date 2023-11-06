#pragma once

#include <cmath>

class Temperature
{
public:
    double initT;
    double curT;
    int iter;
    Temperature(double temp = 0): iter(0), initT(temp), curT(temp) {}

    virtual void decrease(){};
};

class Cauchy : public Temperature
{
public:
    Cauchy(double temp = 0): Temperature(temp) {}

    void decrease() override
    {
        this->iter++;
        this->curT = this->initT / (1 + this->iter);
    }
};

class LogDiv : public Temperature
{
public:
    LogDiv(double temp = 0): Temperature(temp) {}

    void decrease() override
    {
        this->iter++;
        this->curT = (this->initT * log(1 + this->iter)) / (1 + this->iter);
    }
};

class Boltzmann : public Temperature
{
public:
    Boltzmann(double temp = 0): Temperature(temp) {}
    
    void decrease() override
    {
        this->iter++;
        this->curT = this->initT / log(1 + this->iter);
    }
};