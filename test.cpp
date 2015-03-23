
#include <iostream>
#include <vector>

struct X {
    X() { std::cout << "standard constructor" << std::endl; }
    // X(int a) { std::cout << "int constructor" << std::endl; }
    // X(const X&) { std::cout << "copy constructor" << std::endl; }
};

struct ImplicitConversion {
  void take_double(double) {}
  //void take_double(int) = delete; // Uncomment this to generate a compiler error on line 9
};

int main() {
  ImplicitConversion i;
  int a = 2;

  i.take_double(2.3);
  i.take_double(a); // This implicit overload can be suppressed with delete
}
