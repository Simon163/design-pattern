
#pragma once

#include <iostream>

// the abstract state class
class State {
 public:
  virtual void handle() = 0;

  virtual ~State() {}
};

// the concrete state class A
class ConcreteStateA : public State {
 public:
  void handle() override { std::cout << "Handling state A" << std::endl; }
};

// the concrete state class B
class ConcreteStateB : public State {
 public:
  void handle() override { std::cout << "Handling state B" << std::endl; }
};

// the context class, providing the state switch interface
class Context {
 private:
  State* state;

 public:
  Context(State* state) : state(state) {}

  void setState(State* newState) {
    if (newState != nullptr) {
      this->state = newState;
    }
  }

  void request() { this->state->handle(); }
};
