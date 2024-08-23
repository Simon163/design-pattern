
#include "adaptor.h"

int main() {
  Adaptee* adaptee = new Adaptee();
  Target*  target  = new Adapter(adaptee);
  target->request();

  delete adaptee;
  delete target;

  return 0;
}
