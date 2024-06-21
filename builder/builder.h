
#pragma once

#include <iostream>
#include <memory>
#include <string>

// The Product class defines the computer to be built.
class Computer {
 private:
  std::string cpu_ = "Intel Core i5";  // Intel Core i5
  int         ram_ = 16;               // 16GB
  int         hdd_ = 1000;             // 1TB

 public:
  void setCPU(const std::string& cpu) { cpu_ = cpu; }

  void setRAM(const int ram) { ram_ = ram; }

  void setHDD(const int hdd) { hdd_ = hdd; }

  void display() const {
    std::cout << "Computer configuration: \nCPU: " << cpu_ << "\nRAM: " << ram_
              << "GB" << "\nHDD: " << hdd_ << "GB\n";
  }
};

// Abstract builder interface
class IBuilder {
 public:
  virtual ~IBuilder() {}

  virtual void buildCPU(const std::string& cpu) const = 0;
  virtual void buildRAM(const int ram) const          = 0;
  virtual void buildHDD(const int hdd) const          = 0;
};

// concrete builder
class ConcreteBuilder : public IBuilder {
 private:
  Computer* computer_ = nullptr;

 public:
  ConcreteBuilder() { computer_ = new Computer(); }

  ~ConcreteBuilder() override { delete computer_; }

  void buildCPU(const std::string& cpu) const override {
    computer_->setCPU(cpu);
  }

  void buildRAM(const int ram) const override { computer_->setRAM(ram); }

  void buildHDD(const int hdd) const override { computer_->setHDD(hdd); }

  Computer* GetComputer() { return computer_; }

 public:
  ConcreteBuilder(const ConcreteBuilder&)            = delete;
  ConcreteBuilder& operator=(const ConcreteBuilder&) = delete;
};

/* The Director is in charge of executing the building configuration. the
 * Director class is not required, since the client can control builders
 * directly.
 */
class Director {
 private:
  IBuilder* builder_ = nullptr;

 public:
  void setBuilder(IBuilder* builder) { builder_ = builder; }

  void BuildMinimalComputer(const std::string& cpu) { builder_->buildCPU(cpu); }

  void BuildFullFeaturedComputer(const std::string& cpu, const int ram,
                                 const int hdd) {
    builder_->buildCPU(cpu);
    builder_->buildRAM(ram);
    builder_->buildHDD(hdd);
  }
};
