
#pragma once

#include <iostream>

// target interface
class Target {
 public:
  virtual void request() = 0;
};

// source interface
class Adaptee {
 public:
  void specificRequest() {
    std::cout << "specific request for Adaptee" << std::endl;
  }
};

// adapted source interface
class Adapter : public Target {
 public:
  Adapter(Adaptee* adaptee) : adaptee(adaptee) {}

  void request() override { adaptee->specificRequest(); }

 private:
  Adaptee* adaptee;
};
