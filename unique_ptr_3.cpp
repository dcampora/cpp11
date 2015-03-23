
#include <iostream>   // cout, endl
#include <vector>     // vector
#include <memory>     // shared_ptr

using std::cout; using std::endl;

struct Foo {
  Foo(int n) :n(n)  { cout << "Constructing Foo " << n << endl; }
  ~Foo()            { cout << "Destructing  Foo " << n << endl; n = 666; }
  int n;
  void id() { cout << n << endl;}
};

struct Owner {
  std::shared_ptr<Foo> f;
  Owner(std::shared_ptr<Foo> f) : f(f) {}
  ~Owner() { cout << "Destructing Owner" << endl; }
};



int main() {

  Foo* bare;
  // Anonymous scope
  {
    std::vector<Owner> v;
    v.reserve(10);

    {
      auto f = std::make_shared<Foo>(1);
      // Foo object is "gotten", but doesn't count for
      // pointer count.
      bare = f.get();
      for (int i=0; i<10; ++i)
        v.emplace_back(f);
    }

    for (int i=0; i<5; ++i)
      v.erase(begin(v) + v.size()/2);

    bare->id();
  }

  // The Foo object is gone
  bare->id();
}
