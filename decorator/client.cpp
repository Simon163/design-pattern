
#include "decorator.h"

int main() {
    TextPrinter* printer = new SimpleTextPrinter("This is an sample of the decorator pattern!");
    std::cout << printer->print() << std::endl;

    TextPrinter* boldPrinter = new BoldDecorator(printer);
    std::cout << boldPrinter->print() << std::endl;

    TextPrinter* italicBoldPrinter = new ItalicDecorator(boldPrinter);
    std::cout << italicBoldPrinter->print() << std::endl;

    TextPrinter* coloredItalicBoldPrinter = new ColorDecorator(italicBoldPrinter, "blue");
    std::cout << coloredItalicBoldPrinter->print() << std::endl;

    // Clean up
    delete coloredItalicBoldPrinter;

    return 0;
}