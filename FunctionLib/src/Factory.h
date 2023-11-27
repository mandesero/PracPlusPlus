#pragma once
#include <string>
#include "Function.h"

class FunctionFactory {
public:
    FunctionFactory(){
        RegisterAll();
    }

    class ICreator {
    public:
        virtual ~ICreator() {};
        virtual BaseFunctionPtr Create() const = 0;
        virtual BaseFunctionPtr Create(double param) const = 0;
        virtual BaseFunctionPtr Create(std::vector<double> params) const = 0;
    };

    template <class TFunction>
    class FunctionCreator : public ICreator {
    public:
        BaseFunctionPtr Create() const override {
            return std::make_shared<TFunction>(TFunction());
        }

        BaseFunctionPtr Create(double param) const override {
            return std::make_shared<TFunction>(TFunction(param));
        }

        BaseFunctionPtr Create(std::vector<double> params) const override {
            return std::make_shared<TFunction>(TFunction(params));
        }
    };

    BaseFunctionPtr Create(const std::string& name) const {
        return RegisteredCreators.at(name)->Create();
    }

    BaseFunctionPtr Create(const std::string& name, double param) const {
        return RegisteredCreators.at(name)->Create(param);
    }
    
    BaseFunctionPtr Create(const std::string& name, const std::vector<double>& params) const {
        return RegisteredCreators.at(name)->Create(params);
    }

    std::vector<std::string> GetAvailableObjects() const {
        std::vector<std::string> RegisteredCrs;
        for (const auto& [key, val]: RegisteredCreators)
            RegisteredCrs.push_back(key);
        return RegisteredCrs;
    }

private:
    using TCreatorPtr = std::shared_ptr<ICreator>;
    using TRegisteredCreators = std::map<std::string, TCreatorPtr>;
    TRegisteredCreators RegisteredCreators;

    void RegisterAll() {
        RegisteredCreators["ident"] = std::make_shared<FunctionCreator<Identical>>();
        RegisteredCreators["const"] = std::make_shared<FunctionCreator<Constant>>();
        RegisteredCreators["power"] = std::make_shared<FunctionCreator<Power>>();
        RegisteredCreators["exp"] = std::make_shared<FunctionCreator<Exponent>>();
        RegisteredCreators["polynomial"] = std::make_shared<FunctionCreator<Polynom>>();
    }
};