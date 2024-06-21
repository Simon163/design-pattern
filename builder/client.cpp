
#include <iostream>

#include "builder.h"

void ClientCode(Director* director) {
  auto builder = std::make_unique<ConcreteBuilder>();
  director->setBuilder(builder.get());

  std::cout << "Basic computer_:\n";
  director->BuildMinimalComputer("Intel Core i7");
  Computer* computer = builder->GetComputer();
  computer->display();

  std::cout << "Standard full featured computer:\n";
  director->BuildFullFeaturedComputer("Intel Core i7", 32, 4000);
  computer = builder->GetComputer();
  computer->display();

  // Remember, the IBuilder pattern can be used without a Director class.
  std::cout << "Custom computer:\n";
  builder->buildCPU("AMD Ryzen 5");
  builder->buildHDD(2000);
  computer = builder->GetComputer();
  computer->display();
}

int main() {
  auto director = std::make_unique<Director>();
  ClientCode(director.get());
  return 0;
}
