#pragma once

#include <string>
#include <memory>

/*
 * Each of a product family should have a base interface.
 */
//  product family A
class AbstractProductFamilyA {
 public:
  virtual ~AbstractProductFamilyA() {};
  virtual std::string functionA() = 0;
};

/*
 * Concrete product of a product family.
 */
// prodcut A1 of product family A
class ConcreteProductA1 : public AbstractProductFamilyA {
 public:
  std::string functionA() override {
    return "This is the product A1 of the product family A.";
  }
};

// prodcut A2 of product family A
class ConcreteProductA2 : public AbstractProductFamilyA {
  std::string functionA() override {
    return "This is the product A2 of the product family A.";
  }
};

/*
 * Each of a product family should have a base interface.
 */
//  product family B
class AbstractProductFamilyB {
 public:
  virtual ~AbstractProductFamilyB() {};
  virtual std::string functionB() = 0;
};

/*
 * Concrete product of a product family.
 */
// prodcut B1 of product family B
class ConcreteProductB1 : public AbstractProductFamilyB {
 public:
  std::string functionB() override {
    return "This is the product B1 of the product family B.";
  }
};
// prodcut B2 of product family B
class ConcreteProductB2 : public AbstractProductFamilyB {
  std::string functionB() override {
    return "This is the product B2 of the product family B.";
  }
};

/*
 * The abstract factory interface
 */
class AbstractFactory {
 public:
  virtual std::unique_ptr<AbstractProductFamilyA> CreateProductA() = 0;
  virtual std::unique_ptr<AbstractProductFamilyB> CreateProductB() = 0;
};

/*
 * Concrete factory produce a family of products
 */
// concrete factory 1
class ConcreteFactory1 : public AbstractFactory {
 public:
  std::unique_ptr<AbstractProductFamilyA> CreateProductA() override {
    return std::make_unique<ConcreteProductA1>();
  }
  std::unique_ptr<AbstractProductFamilyB> CreateProductB() override {
    return std::make_unique<ConcreteProductB1>();
  }
};

// concrete factory 2
class ConcreteFactory2 : public AbstractFactory {
 public:
  std::unique_ptr<AbstractProductFamilyA> CreateProductA() override {
    return std::make_unique<ConcreteProductA2>();
  }
  std::unique_ptr<AbstractProductFamilyB> CreateProductB() override {
    return std::make_unique<ConcreteProductB2>();
  }
};
