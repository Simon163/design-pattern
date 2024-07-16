
#pragma once

#include <iostream>

// strategy inteface
class IStrategy {
 public:
  virtual ~IStrategy() {}

  virtual void exectue() = 0;
};

// concrete strategy A
class ConcreteStrategyA : public IStrategy {
 public:
  void exectue() override { std::cout << "Executing strategy A" << std::endl; }
};

// concrete strategy B
class ConcreteStrategyB : public IStrategy {
 public:
  void exectue() override { std::cout << "Executing strategy B" << std::endl; }
};

// context class
class Context {
 private:
  IStrategy* strategy_;

 public:
  explicit Context(IStrategy* strategy) : strategy_(strategy) {}

  // set a strategy
  void setStrategy(IStrategy* strategy) { this->strategy_ = strategy; }

  // execute the strategy
  void executeStrategy() { strategy_->exectue(); }
};
