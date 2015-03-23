
#include <iostream>   // cout, endl
#include <vector>     // vector
#include <memory>     // unique_ptr
#include <utility>    // move
#include <algorithm>  // move, copy

using std::cout; using std::endl;

struct Foo {
  Foo(int n=0) :n(n) { cout << "Constructing Foo " << n << endl; }
  ~Foo()             { cout << "Destructing  Foo " << n << endl; n = 666; }
  int n;
  void id() { cout << n << endl;}
};

int main() {

  std::unique_ptr<Foo> t{new Foo{100}};
  std::unique_ptr<Foo> s{new Foo{200}};

  std::unique_ptr<Foo[]> ts{ new Foo [2] {{1}, {2}}};
  std::unique_ptr<Foo[]> ss{ new Foo [2] {{3}, {4}}};

  ss[0].id();

  cout << "------- moving in loop ------" << endl;
  // Why does this not delete the target ...
  for (int i=0; i<2; ++i)
    ts[i] = std::move(ss[i]);


  cout << "------- moving single ------" << endl;
  // ... when this does delete the target?
  t = std::move(s);
  cout << "------- moving with move-----" << endl;
  //std::move(std::begin(ss), std::end(ss), std::begin(ts)); // Error: nonmember begin seems not to be implemented for unique_ptr
  std::copy(&ss[0], &ss[2], &ts[0]); // Why does this work? Why isn't move required.
  //std::move(&ss[0], &ss[5], &ts[0]); // This is the move *algorithm*: brother of copy. What happens if you use it?

} // Why are 3 & 4 deleted twice, and 1 & 2 not at all?

