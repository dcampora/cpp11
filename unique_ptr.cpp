
#include <iostream>   // cout, endl
#include <vector>     // vector
#include <memory>     // unique_ptr
#include <string>     // string

using std::cout; using std::endl; using std::string;

struct Base {
  int n;
  Base(int n) : n(n) {}
  void id() { cout << whoami() << " " << n << endl; }
  virtual string whoami() { return "Base"; }
  virtual ~Base() { cout << "Destructing " << n << endl; };
};

struct Sub : Base {
  using Base::Base;
  virtual string whoami() { return "Sub"; }
};


int main() {
  using uniqfoo = std::unique_ptr<Base>;

  std::vector<uniqfoo> v;
  v.reserve(10);
  v.emplace_back(new Base(1));
  v.emplace_back(new Sub (2));
  v.emplace_back(new Base(3));
  v[1] = uniqfoo(new Sub (4)); // Sub(2) deleted here

  for (auto& bp: v)
    bp->id();

  //std::vector<uniqfoo> w = v; // Compiler error
  std::vector<uniqfoo> w = std::move(v);

  //uniqfoo bp = v[1]; // Compiler error
  uniqfoo bp = std::move(w[1]); // Compiles but ...
  // NB if we had used v ^ up there, we would have crashed by now. <- Not necessarily true,
  // It's bad practice, it might crash. We should definitely not do it.

  cout << "Fasten your seatbelt ... " << std::flush;
  v[1]->id(); // Compiles, but you don't want to do this!
  // Comment out the above line, and observe that all objects get deleted
}
