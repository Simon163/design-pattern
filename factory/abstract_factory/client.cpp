#include <iostream>
#include <memory>
#include "abstract_factory.h"

/*
 * The client code works with factories and products only through
 *  abstract types: AbstractFactory and AbstractProduct.
 */

void ClientCode(AbstractFactory* factory) {
  auto product_a = factory->CreateProductA();
  auto product_b = factory->CreateProductB();
  std::cout << product_a->functionA() << "\n";
  std::cout << product_b->functionB() << "\n";
}

int main() {

  std::cout << "1st factory:\n";
  auto factory1 = new ConcreteFactory1();
  ClientCode(factory1);

  std::cout << "2nd factory:\n";
  auto factory2 = new ConcreteFactory2();
  ClientCode(factory2);

  delete factory1;
  delete factory2;

  return 0;
}