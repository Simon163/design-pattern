
#include "state.h"

int main() {
  State* stateA = new ConcreteStateA();
  State* stateB = new ConcreteStateB();

  Context context(stateA);
  context.request();

  context.setState(stateB);
  context.request();

  delete stateA;
  delete stateB;

  return 0;
}
