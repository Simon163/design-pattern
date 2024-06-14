#pragma once

#include <iostream>
#include <memory>

// product interface
class IProduct {
public:
    virtual ~IProduct() {}
    virtual void Operation() = 0;
};

// concrete product
class ConcreteProductA : public IProduct {
public:
    void Operation() override {
        std::cout << "ConcreteProductA operation" << std::endl;
    }
};

class ConcreteProductB : public IProduct {
public:
    void Operation() override {
        std::cout << "ConcreteProductB operation" << std::endl;
    }
};

class SimpleFactory {
public:
    static std::unique_ptr<IProduct> CreateProduct(const std::string& type) {
        if (type == "A") {
            return std::make_unique<ConcreteProductA>();
        } else if (type == "B") {
            return std::make_unique<ConcreteProductB>();
        } else {
            return nullptr;
        }
    }
};

