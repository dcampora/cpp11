#include <iostream>   // cout, endl
#include <thread>     // thread

using std::cout; using std::endl;

struct Foo {
  int n;
  Foo(int n) : n(n) {}
  void one()       { cout << n   << endl; }
  void two(int m)  { cout << n+m << endl; }
  void ovd()       { cout << n*n << endl; }
  void ovd(int m)  { cout << n*m << endl; }
};

int main() {
  // TODO... :)
  Foo f1{1};
  Foo f2{2};
  std::thread(/* f1.one( ) */).join();
  std::thread(/* f2.two(3) */).join();
  std::thread(/* f2.ovd( ) */).join();
  std::thread(/* f2.ovd(3) */).join();
}