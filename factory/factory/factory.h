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

// factory interface
class IFactory {
public:
    virtual ~IFactory() {};
    virtual std::unique_ptr<IProduct> CreateProduct() = 0;
};

// concrete factory
class ConcreteFactoryA : public IFactory {
    std::unique_ptr<IProduct> CreateProduct() override {
        return std::make_unique<ConcreteProductA>();
    }
};

class ConcreteFactoryB : public IFactory {
    std::unique_ptr<IProduct> CreateProduct() override {
        return std::make_unique<ConcreteProductB>();
    }
};


