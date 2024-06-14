
#include "simple_factory.h"

int main() {    
    auto productA = SimpleFactory::CreateProduct("A");
    if (productA) {
        productA->Operation();
    }
    else {
        std::cout << "This product doesn't exist!" << std::endl;
    }


    auto productB = SimpleFactory::CreateProduct("B");
    if (productB) {
        productB->Operation();
    }
    else {
        std::cout << "This product doesn't exist!" << std::endl;
    }

    auto productC = SimpleFactory::CreateProduct("C");
    if (productC) {
        productC->Operation();
    }
    else {
        std::cout << "This product doesn't exist!" << std::endl;
    }

    return 0;
}