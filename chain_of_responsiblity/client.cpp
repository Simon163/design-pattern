
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "./chain_of_responsiblity.h"

void ClientCode(IHandler* handler) {
  std::vector<std::string> actions = {"Pick", "Pack", "Wrap", "Ship", "Load"};
  for (const std::string& action : actions) {
    std::cout << "Client: I want to " << action << "." << std::endl;
    std::string result = handler->Handle(action);
    if (!result.empty()) {
      std::cout << "  " << result;
    } else {
      std::cout << "  " << action << " is not defined." << std::endl;
    }
  }
}

int main() {
  std::unique_ptr<PickHandler> pick = std::make_unique<PickHandler>();
  std::unique_ptr<PackHandler> pack = std::make_unique<PackHandler>();
  std::unique_ptr<WrapHandler> wrap = std::make_unique<WrapHandler>();
  std::unique_ptr<ShipHandler> ship = std::make_unique<ShipHandler>();

  // create the chain in a warehouse
  pick.get()->SetNext(pack.get())->SetNext(wrap.get())->SetNext(ship.get());

  std::cout << "Chain: Pick -> Pack -> Wrap -> Ship" << std::endl;
  ClientCode(pick.get());
  std::cout << std::endl;
  std::cout << "Subchain: Wrap -> Ship" << std::endl;
  ClientCode(wrap.get());

  return 0;
}
