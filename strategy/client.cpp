
#include <memory>

#include "strategy.h"

int main() {
  auto stragyA = std::make_unique<ConcreteStrategyA>();
  auto stragyB = std::make_unique<ConcreteStrategyB>();

  Context context{stragyA.get()};
  context.executeStrategy();

  context.setStrategy(stragyB.get());
  context.executeStrategy();
  return 0;
}
