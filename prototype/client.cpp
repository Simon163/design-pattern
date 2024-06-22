
#include "prototype.h"

int main() {
  std::unique_ptr<IPrototype> prototypeA =
      std::make_unique<ConcretePrototypeA>();
  prototypeA->print();
  std::unique_ptr<IPrototype> cloneA = prototypeA->clone();
  cloneA->print();

  std::unique_ptr<IPrototype> prototypeB =
      std::make_unique<ConcretePrototypeB>();
  prototypeB->print();
  std::unique_ptr<IPrototype> cloneB = prototypeB->clone();
  cloneB->print();
  return 0;
}
