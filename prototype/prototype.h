
#pragma once

#include <iostream>
#include <memory>

// prototype interface
class IPrototype {
 public:
  virtual ~IPrototype() {}

  virtual std::unique_ptr<IPrototype> clone() const = 0;
  virtual void                        print() const = 0;
};

// concrete prototype class A
class ConcretePrototypeA : public IPrototype {
 public:
  std::unique_ptr<IPrototype> clone() const override {
    return std::make_unique<ConcretePrototypeA>(*this);
  }

  void print() const {
    std::cout << "ConcretePrototypeA instance: " << this << ", " << __FUNCTION__
              << std::endl;
  }
};

// concrete prototype class B
class ConcretePrototypeB : public IPrototype {
 public:
  std::unique_ptr<IPrototype> clone() const override {
    return std::make_unique<ConcretePrototypeB>(*this);
  }

  void print() const {
    std::cout << "ConcretePrototypeB instance: " << this << ", " << __FUNCTION__
              << std::endl;
  }
};
