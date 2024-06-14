
#include "factory.h"

int main() {

    IFactory* factoryA = new ConcreteFactoryA;
    auto productA = factoryA->CreateProduct();
    productA->Operation();

    IFactory* factoryB = new ConcreteFactoryA;
    auto productB = factoryB->CreateProduct();
    productB->Operation();

    delete factoryA;
    delete factoryB;
    return 0;
}