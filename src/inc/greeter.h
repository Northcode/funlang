#include <iostream>
#include <string>

struct greeter {
  std::string message;

  greeter(std::string message) {
    this->message = message;
  }

  void greet(std::string name) {
    std::cout << message << " " << name << std::endl;
  }
};
