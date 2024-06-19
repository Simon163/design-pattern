
#pragma once

#include <iostream>
#include <string>

// handler interface
class IHandler {
 public:
  virtual IHandler*   SetNext(IHandler* handler)         = 0;
  virtual std::string Handle(const std::string& request) = 0;
};

// abstract handler
class AbstractHandler : public IHandler {
 private:
  IHandler* next_handler_;

 public:
  AbstractHandler() : next_handler_(nullptr) {}

  IHandler* SetNext(IHandler* handler) override {
    this->next_handler_ = handler;
    return handler;
  }

  std::string Handle(const std::string& request) override {
    if (this->next_handler_) {
      return this->next_handler_->Handle(request);
    }

    return "";
  }
};

/*
 * A concrete Handler either handles a request or passes it to the next handler
 * in the chain.
 */
class PickHandler : public AbstractHandler {
 public:
  std::string Handle(const std::string& request) override {
    if (request == "Pick") {
      return "I'm doing " + request + ".\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};

class PackHandler : public AbstractHandler {
 public:
  std::string Handle(const std::string& request) override {
    if (request == "Pack") {
      return "I'm doing " + request + ".\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};

class WrapHandler : public AbstractHandler {
 public:
  std::string Handle(const std::string& request) override {
    if (request == "Wrap") {
      return "I'm doing " + request + ".\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};

class ShipHandler : public AbstractHandler {
 public:
  std::string Handle(const std::string& request) override {
    if (request == "Ship") {
      return "I'm doing " + request + ".\n";
    } else {
      return AbstractHandler::Handle(request);
    }
  }
};
