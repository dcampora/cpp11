
#include <iostream> // cout, endl

using std::cout; using std::endl;

class A {
public:
  A(int m) : member(m) {}
  void doit(int n) {
    // int m = this->member;
    // [&m, n] { cout << n + m << endl; }();

    // [&this, &] { cout << n + this->member << endl; }(); // Doesn't work ?
    // ambda_7.cpp:12:7: error: 'this' cannot be captured by reference
    [&] { cout << n + this->member << endl; }(); // Works ... ?
  }

private:
  int member;
};

int main() {
  A(2).doit(3);
}
