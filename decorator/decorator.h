#pragma once

#include <iostream>
#include <string>

// Define the Component Interface
class TextPrinter {
 public:
    virtual ~TextPrinter() {}
    virtual std::string print() const = 0;
};
// Implement the Concrete Component
class SimpleTextPrinter : public TextPrinter {
 public:
    explicit SimpleTextPrinter(const std::string& text) : text_(text) {}
    std::string print() const override {
        return text_;
    }
private:
    std::string text_;
};

// Define the Decorator Interface
class TextDecorator : public TextPrinter {
 public:
    explicit TextDecorator(TextPrinter* printer) : printer_(printer) {}
    std::string print() const override {
        return printer_->print();
    }
    virtual ~TextDecorator() {}
 protected:
    TextPrinter* printer_;
};

// Implement Concrete Decorators, Bold
class BoldDecorator : public TextDecorator {
 public:
    explicit BoldDecorator(TextPrinter* printer) : TextDecorator(printer) {}
    std::string print() const override {
        return "<b>" + printer_->print() + "</b>";
    }
};

// Implement Concrete Decorators, Italic
class ItalicDecorator : public TextDecorator {
 public:
    explicit ItalicDecorator(TextPrinter* printer) : TextDecorator(printer) {}
    std::string print() const override {
        return "<i>" + printer_->print() + "</i>";
    }
};

// Implement Concrete Decorators, Color
class ColorDecorator : public TextDecorator {
 public:
    ColorDecorator(TextPrinter* printer, const std::string& color)
        : TextDecorator(printer), color_(color) {}
    std::string print() const override {
        return "<style>color:" + color_ + printer_->print() + "</style>";
    }
 private:
    std::string color_;
};