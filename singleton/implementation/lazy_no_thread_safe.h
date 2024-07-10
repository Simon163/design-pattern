#include <iostream>
#include <mutex>

#include "nocopyable.h"

/*
    lazy mode, meaning that the instance of Sinleton is created only when it is
   first needed. thread safety is not guaranteed in this mode in multi-threaded
   environments.
*/
class Singleton : nocopyable {
 public:
  // get the object of singleton instance
  static Singleton*& getInstance();

  // deinitialize
  static void deleteInstance();

  // print address of the object of singleton instance
  void print();

 private:
  static Singleton* instance;
};

// initialize
Singleton* Singleton::instance = nullptr;

Singleton*& Singleton::getInstance() {
  if (instance == nullptr) {
    instance = new (std::nothrow) Singleton;
  }

  return instance;
}

void Singleton::deleteInstance() {
  if (instance) {
    delete instance;
    instance = nullptr;
  }
}

void Singleton::print() {
  std::cout << "The address of the singleton instance:" << this << std::endl;
}
